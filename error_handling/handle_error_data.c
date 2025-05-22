#include "../cub3d.h"

void free_state_images(t_var *data)
{
	free_single_img((void **)&data->state.win.img, data);
	free_single_img((void **)&data->state.lose.img, data);
}

void free_enemy_gifs(t_var *data)
{
	free_single_img((void **)&data->gif.zero.img, data);
	free_single_img((void **)&data->gif.one.img, data);
	free_single_img((void **)&data->gif.two.img, data);
	free_single_img((void **)&data->gif.three.img, data);
	free_single_img((void **)&data->gif.four.img, data);
	free_single_img((void **)&data->gif.five.img, data);
	free_single_img((void **)&data->gif.six.img, data);
	free_single_img((void **)&data->gif.seven.img, data);
	free_single_img((void **)&data->gif.eight.img, data);
}
void clean_data_texture(t_map *map, t_var *data)
{
    free_single_img((void **)&map->textures[NORTH].attr, data);
    free_single_img((void **)&map->textures[EAST].attr, data);
    free_single_img((void **)&map->textures[SOUTH].attr, data);
    free_single_img((void **)&map->textures[WEST].attr, data);
    free_single_img((void **)&map->textures[FLOOR].attr, data);
    free_single_img((void **)&map->textures[CEILING].attr, data);
    free_single_img((void **)&map->textures[DOOR_O].attr, data);
    free_single_img((void **)&map->textures[DOOR_C].attr, data);
    free_single_img((void **)&map->textures[DOOR_S].attr, data);
}
void close_mlx(t_var *data)
{
	if (data->mlx && data->win)
	{
        mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
    if (data->mlx)
    {
		/* uncomment upon submission */
        // mlx_destroy_display(data->mlx);
        free(data->mlx);
		data->mlx = NULL;
    }
}
void clean_data(t_var *data)
{
	free_enemy_gifs(data);
	free_state_images(data);
	ft_free_ptr((void **)&data->sprites);
	free_single_img(&data->image.img, data);
	clean_data_texture(&data->map, data);
	free_all_door(data);
	close_mlx(data);
}