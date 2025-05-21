#include "../cub3d.h"

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
    if (data->state.state == INIT)
    {
        data->mlx = mlx_init();
        if (!data->mlx)
            return;
        data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
        if (!data->win)
            return;
        load_enemy_gifs(data);
        load_state(data); 
        data->map_save = ft_copy_arr(data->cube->map.arr); 
    }
    // retry stilll faulty
    data->state.state = NOSTATE;
    data->map =  data->cube->map;
    data->map.arr = data->map_save;
    data->move = (t_move) {0};
    data->minimap = (t_minimap) {0};
    init_player(data);
    init_sprites(data);
    data->last_mouse_x = -1;
    place_winning_tiles(data);
}





