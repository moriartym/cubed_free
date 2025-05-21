#include "../cub3d.h"

void mouse_state(t_var *data)
{
    if (!data->mouse_state)
    data->mouse_state = 1;
    else
    {
        data->last_mouse_x = -1;
        data->mouse_state = 0;
    }
}

int get_front_tile_x(t_var *data)
{
    int curr_tile_x;
    int dir_x;
    int tile_in_front_x;

    curr_tile_x = data->player.px / TILE_SIZE;
    dir_x = (int)roundf(cosf(data->player.pa));
    tile_in_front_x = curr_tile_x + dir_x;
    return (tile_in_front_x);
}

int get_front_tile_y(t_var *data)
{
    int curr_tile_y ;
    int dir_y;
    int tile_in_front_y ;

    curr_tile_y = data->player.py / TILE_SIZE;
    dir_y = (int)roundf(sinf(data->player.pa));
    tile_in_front_y = curr_tile_y + dir_y;
    return (tile_in_front_y);
}
