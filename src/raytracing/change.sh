files="trace.c diffuse.c transparency.c"

for file in $files; do
    sed -i 's/t_sphere/t_obj/g' $file
done
