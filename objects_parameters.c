#include "rtv1.h"

char *get_coordinates(char *description)
{
    char *coordinates;
    int i;
    int len;

    i = 0;
    len = ft_strlen(description);
    while (!(ft_isdigit(description[i])) && description[i] != '-')
        i++;
    coordinates = ft_strsub(description, i, len - i);
    return (coordinates);
}

t_color get_color(char *description)
{
    char *coord_buf;
    char **coordinates;
    t_color color;

    coord_buf = get_coordinates(description);
    coordinates = ft_strsplit(coord_buf, ',');
    color.red = ft_atoi(coordinates[0]);
    color.green = ft_atoi(coordinates[1]);
    color.blue = ft_atoi(coordinates[2]);
    color.alpha = ft_atoi(coordinates[3]);
    return (color);
}

t_point get_points(char *description)
{
    char *coord_buf;
    char **coordinates;
    t_point points;

    coord_buf = get_coordinates(description);
    coordinates = ft_strsplit(coord_buf, ',');
    points.x = ftoi(ft_strtrim(coordinates[0]));
    printf("x = %f\n", points.x);
    points.y = ftoi(ft_strtrim(coordinates[1]));
    printf("y = %f\n", points.y);
    points.z = ftoi(ft_strtrim(coordinates[2]));
    printf("z = %f\n", points.z);
    return (points);
}

t_object *get_sphere(char **description)
{
    t_object *sphere;
    t_point center;
    float radius;
    float specular;
    t_color color;

    sphere = malloc(sizeof(t_object));
    center = get_points(description[0]);
    radius = ftoi(get_coordinates(description[1]));
    color = get_color(description[2]);
    specular = ftoi(get_coordinates(description[3]));
    sphere = new_sphere(center, radius, specular, color);
    return (sphere);
}

t_object *get_cylinder(char **description)
{
    t_object *cylinder;
    t_point position;
    float radius;
    float specular;
    t_color color;

    cylinder = malloc(sizeof(t_object));
    position = get_points(description[0]);
    radius = ftoi(get_coordinates(description[1]));
    color = get_color(description[2]);
    specular = ftoi(get_coordinates(description[3]));
    cylinder = new_cylinder(position, radius, specular, color);
    return (cylinder);
}

t_object *get_cone(char **description)
{
    t_object *cone;
    t_point position;
    float specular;
    t_color color;

    cone = malloc(sizeof(t_object));
    position = get_points(description[0]);
    color = get_color(description[1]);
    specular = ftoi(get_coordinates(description[2]));
    cone = new_cone(position, specular, color);
    return (cone);
}

t_object *get_triangle(char **description)
{
    t_object *triangle;
    t_point *vertex;
    float specular;
    t_color color;

    triangle = malloc(sizeof(t_object));
    vertex = malloc(sizeof(t_point) * 3);
    vertex[0] = get_points(description[0]);
    vertex[1] = get_points(description[1]);
    vertex[2] = get_points(description[2]);
    color = get_color(description[3]);
    specular = ftoi(get_coordinates(description[4]));
    triangle = new_triangle(vertex, specular, color);
    return (triangle);
}

t_object *get_plane(char **description)
{
    t_object *plane;
    t_point point;
    t_point normal;
    float specular;
    t_color color;

    plane = malloc(sizeof(t_object));
    point = get_points(description[0]);
    normal = get_points(description[1]);
    color = get_color(description[2]);
    specular = ftoi(get_coordinates(description[3]));
    plane = new_plane(point, normal, specular, color);
    return (plane);
}

char *get_light_type(char *description)
{
    char *type;
    int i;
    int len;

    i = 0;
    len = ft_strlen(description);
    while (description[i] != ':')
        i++;
    i++;
    type = ft_strsub(description, i, len - i);
    return (ft_strtrim(type));
}

t_object *get_light(char **description)
{
    t_object *light;
    t_point position;
    t_point direction;
    char *type;

    light = malloc(sizeof(t_object));
    type = get_light_type(description[0]);
    printf("light type = |%s|\n", type);
    position.x = 0.0;
    position.y = 0.0;
    position.z = 0.0;
    direction.x = 0.0;
    direction.y = 0.0;
    direction.z = 0.0;
    if (!ft_strcmp(type, "point"))
        position = get_points(description[1]);
    else if (!ft_strcmp(type, "directional"))
        direction = get_points(description[1]);
    light->data = (void *)new_light(position, direction, (const char *)type);
    light->tag = ft_strdup("light");
    return (light);
}
