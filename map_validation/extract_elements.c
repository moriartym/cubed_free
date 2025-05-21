#include "../cub3d.h"

int	extract_elements(t_map *map)
{
	char	*line;
	char	**arr;
	int		i;
	
	i = 1;
	while (1)
	{
		line = get_next_line(map->open_fd);
		if (!line)
			break ;
		arr = ft_split(line, ' ');
		if (!arr)
			return (free(line), ft_error_return("malloc failed"));
		if (verify_id(map, arr, i) == 1)
			return (ft_free_2d(&arr), free(line), 1);
		ft_free_2d(&arr);
		free(line);
		if (map->elements_set == 6)
			break ;
		i++;
	}
	if (map->elements_set != 6)
		return (ft_error_return("Element error"));
	map->content_start = i;
	return (0);
}

int	verify_id(t_map *map, char **arr, int line)
{
	t_id	*id;

	if (ft_arrlen(arr) == 1 && ft_strcmp(arr[0], "\n") == 0)
		return (0);
	else if (ft_arrlen(arr) != 2)
		return (element_err(line), 1);
	else if (ft_strcmp(arr[0], "NO") == 0 && !map->textures[NORTH].filename)
		id = set_id(&map->textures[NORTH], NORTH);
	else if (ft_strcmp(arr[0], "EA") == 0 && !map->textures[EAST].filename)
		id = set_id(&map->textures[EAST], EAST);
	else if (ft_strcmp(arr[0], "SO") == 0 && !map->textures[SOUTH].filename)
		id = set_id(&map->textures[SOUTH], SOUTH);
	else if (ft_strcmp(arr[0], "WE") == 0 && !map->textures[WEST].filename)
		id = set_id(&map->textures[WEST], WEST);
	else if (ft_strcmp(arr[0], "F") == 0 && !map->textures[FLOOR].filename && verify_rgb(arr[1]) == 0)
		id = set_id(&map->textures[FLOOR], FLOOR);
	else if (ft_strcmp(arr[0], "C") == 0 && !map->textures[CEILING].filename && verify_rgb(arr[1]) == 0)
		id = set_id(&map->textures[CEILING], CEILING);
	else
		return (element_err(line), 1);
	id->filename = ft_substr(arr[1], 0, ft_strlen(arr[1]) - (arr[1][ft_strlen(arr[1]) - 1] == '\n'));
	if (!id->filename)
		return (ft_error_return("malloc failed"), 1);
	map->elements_set++;
	return (0);
}

int	verify_rgb(char *value)
{
	char	**arr;
	int		i;

	arr = ft_split(value, ',');
	if (!arr)
		return (ft_error_return("malloc failed"));
	if (ft_arrlen(arr) != 3)
		return (ft_free_2d(&arr), 1);
	i = 0;
	while (i < 3)
	{
		if (!ft_range(ft_atoi(arr[i]), 0, 255))
			return (ft_free_2d(&arr), 1);
		i++;
	}
	return (ft_free_2d(&arr),0);
}

t_id	*set_id(t_id *id, textures value)
{
	id->direction = value;
	return (id);
}
