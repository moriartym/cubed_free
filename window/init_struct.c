#include "../cub3d.h"

void init_minimap_offset(t_var *data)
{
    int player_tile_x;
    int player_tile_y;

    player_tile_x = (int)(data->player.px / TILE_SIZE);
    player_tile_y = (int)(data->player.py / TILE_SIZE);
    data->minimap_offset_x = player_tile_x - MINIMAP_TILE / 2;
    data->minimap_offset_y = player_tile_y - MINIMAP_TILE / 2;
    clamp_map(data);
}

void init_player(t_var *data)
{
    player_start(data, data->map.ypos, data->map.xpos);
    data->player.pa = P2;
    data->player.pdy = sinf(data->player.pa);
    data->player.pdx = cosf(data->player.pa);
}

void load_state(t_var *data)
{
    if (MAC)
    {
        load_single_image(data, &data->state.win,  "textures/state/win_mac.xpm");
        load_single_image(data, &data->state.lose,   "textures/state/lose_mac.xpm");
    }
    else
    {
        load_single_image(data, &data->state.win,  "textures/state/win_window.xpm");
        load_single_image(data, &data->state.lose,   "textures/state/lose_window.xpm");
    }
}

void init_all(t_var *data)
{
    data->move = (t_move) {0};
    data->minimap = (t_minimap) {0};
    data->state.state = NOSTATE;
    data->last_mouse_x = -1;
    data->mlx = mlx_init();
    if (!data->mlx)
        handle_error(NULL, "mlx_init failed", &data->map, data);        
    data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
    if (!data->win)
        handle_error(NULL, "mlx_new_window failed", &data->map, data);
    load_enemy_gifs(data);
    load_state(data); 
    init_player(data);
    init_minimap_offset(data);
    init_sprites(data);
    place_winning_tiles(data);
    data->save.map = ft_copy_arr(data->map.arr);
    if (!data->save.map)
        handle_error(NULL, "malloc failed", &data->map, data);
}





