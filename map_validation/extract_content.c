#include "../cub3d.h"

void	extract_content(t_map *map)
{
	get_map_height(map);
	safe_close(&map->open_fd);
	fill_map_arr(map);
}

void	get_map_height(t_map *map)
{
	char	*line;
	int		space;

	space = 1;
	while (1)
	{
		line = get_next_line(map->open_fd);
		if (!line)
			break ;
		if (line[0] == '\n' && space == 1)
		{
			free(line);
			map->content_start++;
			continue ;
		}
		free(line);
		map->height++;
		space = 0;
	}
}

void	fill_map_arr(t_map *map)
{
	char	**buff;
	char	*str;
	int		i;

	map->open_fd = open(map->name, O_RDONLY);
	if (map->open_fd == -1)
		handle_error(NULL, map->name, map, NULL);
	buff = malloc ((map->height + 1) * sizeof(char *));
	if (!buff)
		handle_error(NULL, "malloc failed", map, NULL);
	skip_to_content(map);
	i = 0;
	while (1)
	{
		str = get_next_line(map->open_fd);
		if (!str)
			break;
		buff[i] = str;
		i++;
	}
	buff[i] = NULL;
	map->arr = buff;
	safe_close(&map->open_fd);
}

void	skip_to_content(t_map *map)
{
	char	*line;
	int		i;

	i = 0;
	while (i < map->content_start)
	{
		line = get_next_line(map->open_fd);
		free(line);
		i++;
	}
	return ;
}
