#include "../cub3d.h"

void clean_temp(t_map *map)
{
	ft_free_2d(&map->temp_arr);
	ft_free_ptr((void **)&map->temp_str);
}
void clean_map(t_map *map)
{
	safe_close(&map->open_fd);
	clean_texture(map);
	clean_temp(map);
	ft_free_2d(&map->arr);
}
int	element_err(int line)
{
	char	*str;

	str = ft_itoa(line);
	if (!line)
		return (ft_error_return("malloc failed"));
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("Invalid configuration of map elements in line ", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	free(str);
	return (0);
}

void clean_texture(t_map *map)
{
    ft_free_ptr((void **)&map->textures[NORTH].filename);
    ft_free_ptr((void **)&map->textures[EAST].filename);
    ft_free_ptr((void **)&map->textures[SOUTH].filename);
    ft_free_ptr((void **)&map->textures[WEST].filename);
    ft_free_ptr((void **)&map->textures[FLOOR].filename);
    ft_free_ptr((void **)&map->textures[CEILING].filename);
}
