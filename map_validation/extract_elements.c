#include "../cub3d.h"

void	extract_elements(t_map *map)
{
	int		i;
	
	i = 1;
	while (1)
	{
		map->temp_str = get_next_line(map->open_fd);
		if (!map->temp_str)
			break ;
		map->temp_arr = ft_split(map->temp_str, ' ');
		if (!map->temp_arr)
			handle_error(NULL, "malloc failed", map, NULL);
		if (verify_id(map, map->temp_arr, i) == 1)
			handle_error(NULL, NULL, map, NULL);
		ft_free_2d(&map->temp_arr);
		ft_free_ptr((void **)&map->temp_str);
		if (map->elements_set == 6)
			break ;
		i++;
	}
	if (map->elements_set != 6)
		handle_error("Error when opening file\n", map->name, map, NULL);
	map->content_start = i;
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
		handle_error(NULL, "malloc failed", map, NULL);
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
