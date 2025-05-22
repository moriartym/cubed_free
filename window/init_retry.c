#include "../cub3d.h"

void copy_sprites_save(t_var *data)
{
    int i;

    ft_free_ptr((void **) &data->sprites);
    data->sprites = malloc(sizeof(t_sprite) * (data->num_sprites + 1));
    if (!data->sprites)
        handle_error(NULL, "malloc failed", &data->map, data);
    i = 0;
	while (i < data->num_sprites)
	{
        data->sprites[i] = (t_sprite){0};
        data->sprites[i].x = data->save.sprites[i].x;
        data->sprites[i].y = data->save.sprites[i].y;
        data->sprites[i].is_unstucking = 1;
		i++;
	}
}

void re_init(t_var *data)
{
    printf("🕹️ Retry time! 🌟 Reloading assets and 💥 rebooting madness.\n");
    free_all_door(data);
    ft_free_2d(&data->map.arr);
    data->map.arr = ft_copy_arr(data->save.map); // save copy array first
    if (!data->map.arr)
        handle_error(NULL, "malloc failed", &data->map, data);
    init_player(data);
    copy_sprites_save(data);
    init_minimap_offset(data);
    data->state.state = NOSTATE;
}