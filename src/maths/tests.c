
int	main()
{
  t_vec3f equation = (t_vec3f){1, -3, -4};
  float	solution = 0;
  
  if(resolveQuadratic(equation, &solution))
    printf("%g", solution);
  else
    printf("pas de solution");
}
