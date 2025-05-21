#include "cub3d.h"

int main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		return (ft_putstr_fd("./cub3d map.cub\n", 1), 1);
	map = (t_map){0};
	map.name = argv[1];
	map.name = "map/valid.cub";
	// cub.map.name = "map/test.cub";
	extract_map(&map);
	create_visual(&map);
}