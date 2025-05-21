#include "../cub3d.h"

void	extract_map(t_map *map)
{
	check_map_name(map->name);
	map->open_fd = open(map->name, O_RDONLY);
	if (map->open_fd == -1)
		return (ft_error_return(map->name));
	if (extract_elements(map) == 1)
		return (clean_map, 1);
	if (extract_content(map) == 1)
		return (1);
	if (check_map(map) == 1)
		return (1);
	clean_map(map);
	map->width = map->max_length - 1;
	return (0);
}

void	check_map_name(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	i -= 4;
	if (ft_strncmp(file + i, ".cub", 4) != 0)
		handle_error("File must be in .cub\n", NULL);
	return (0);
}
