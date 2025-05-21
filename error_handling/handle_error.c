#include "../cub3d.h"
void clean_texture_helper(t_map *map)
{
	if (map->textures[FLOOR].filename)
	{
		free(map->textures[FLOOR].filename);
		map->textures[FLOOR].filename = NULL;
	}
	if (map->textures[CEILING].filename)
	{
		free(map->textures[CEILING].filename);
		map->textures[CEILING].filename = NULL;
	}
}

void clean_texture(t_map *map)
{
	if (map->textures[NORTH].filename)
	{
		free(map->textures[NORTH].filename);
		map->textures[NORTH].filename = NULL;
	}
	if (map->textures[EAST].filename)
	{
		free(map->textures[EAST].filename);
		map->textures[EAST].filename = NULL;
	}
	if (map->textures[SOUTH].filename)
	{
		free(map->textures[SOUTH].filename);
		map->textures[SOUTH].filename = NULL;
	}
	if (map->textures[WEST].filename)
	{
		free(map->textures[WEST].filename);
		map->textures[WEST].filename = NULL;
	}
	clean_texture_helper(map);
}

void safe_close(int *fd)
{
	if (*fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}

void clean_map(t_map *map)
{
	printf("CLEANING_MAP\n");
	safe_close(&map->open_fd);
	clean_texture(map);
	if (map->arr)
		ft_free_2d(&map->arr);
	exit (1);
}

void	handle_error(char *err, t_map *map)
{
	if (!err)
		return ;
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd("\n", 2);
	if (map)
		clean_map(map);
	exit (1);
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
