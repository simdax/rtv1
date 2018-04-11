/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:02:20 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/11 15:29:26 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "object.h"
#include "globals.h"

static t_array	*arg(char **tokens, char *arg_rules)
{
    t_array	*array;
    int		ivalue;
    float	fvalue;
    int		i;

    i = 0;
    array = array_new(1, 8);
    while (arg_rules[i])
    {
        if (!tokens[i])
            return (0) ;
        else if (arg_rules[i] == 'i')
        {
            ivalue = ft_atoi(tokens[i]);
            array_add(array, &ivalue, sizeof(int));
        }
        else if (arg_rules[i] == 'f')
        {
            fvalue = ft_atof(tokens[i]);
            array_add(array, &fvalue, sizeof(float));
        }
        ++i;
    }
    ft_free_strsplit(tokens);
    return (array);
}

static void		factory(int new, t_envir *envir, t_array *props)
{
    t_obj obj;
        
    if (new)
    {
        obj = object_new(envir->namespace, envir->parent);
        ft_lstadd(envir->objects, ft_lstnew(&obj, sizeof(t_obj)));
    }
    else
    {
        if (envir->current == 1)
            object_set((*envir->objects)->content, envir->namespace,
                       envir->parent, props->mem);
        if (envir->current == 2)
            globals_set(envir->globals, envir->namespace,
                        envir->parent, props->mem);
        array_free(props);
    }
}

static void		write_mem(t_list *r, t_list *c,
                        t_list **match, t_envir envir)
{
    t_data	*rules;
    t_data	*config;

    config = c->content;
    if (!c->next && *(envir.objects))
    {
        rules = r->content;
        factory(0, &envir, arg(ft_strsplit(config->data.string, ' '),
                               rules->data.string));
    }
    else
    {
        if ((*match = (ft_lstfind(r, is_keyword,
                                  config->data.string))))
        {
            if (ft_strequ(envir.namespace, "objects"))
            {
                envir.namespace = config->data.string;
                factory(1, &envir, 0);
            }
        }
        else
            error(config, envir.namespace, envir.bug);
    }
}

static void		branching(t_list *rules, t_data *config, t_envir envir)
{
    envir.parent = envir.namespace;
    envir.namespace = ((t_data*)rules->content)->data.string;
    envir.rules = ((t_data*)rules->next->content)->data.list;
    envir.config = config->data.list;
    if (ft_strequ(envir.namespace, "objects"))
        envir.current = 1;
    else if (ft_strequ(envir.namespace, "global"))
        envir.current = 2;
    parse(envir);
}

void			parse(t_envir envir)
{
    t_data	*content_config;
    t_list	*match;

    match = 0;
    while (envir.config)
    {
        content_config = envir.config->content;
        if (content_config)
        {
            if (content_config->type == 's')
                write_mem(envir.rules, envir.config, &match, envir);
            else if (match && content_config->type == 'l')
                branching(match, content_config, envir);
        }
        envir.config = envir.config->next;
    }
}
