#include "../cub3d.h"

void	extract_map(t_map *map)
{
	check_map_name(map->name);
	map->open_fd = open(map->name, O_RDONLY);
	if (map->open_fd == -1)
		handle_error("Error when opening file\n", map->name, map, NULL);
	extract_elements(map);
	extract_content(map);
	check_map(map);
	map->width = map->max_length - 1;
}

void	check_map_name(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	i -= 4;
	if (ft_strncmp(file + i, ".cub", 4) != 0)
		handle_error("File must be in .cub\n", file , NULL, NULL);
}
