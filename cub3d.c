#include "cub3d.h"

void print_map_and_enemies(t_var *data)
{
	int y;
	int i;

	y = 0;
	while (data->map.arr[y])
	{
		printf("%s", data->map.arr[y]);
		y++;
	}
    printf("\n");

	i = 0;
	while (i < data->num_sprites)
	{
		printf("Enemy %d: x = %f, y = %f\n",
			i, data->sprites[i].x, data->sprites[i].y);
		i++;
	}
}

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