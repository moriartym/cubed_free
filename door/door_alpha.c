#include "../cub3d.h"

int check_door_alpha(t_var *data, t_ray ray, int side)
{
    char    c;
    t_tex   tile;
    t_img   *tex;
    int color;
    int y;
    int w;
    int x;

    c = data->map.arr[ray.my][ray.mx];
    if (((c == DOORH_CLOSE || c == DOORH_OPEN) && side == 1 && ray.hitTypeH == 'S') ||
        ((c == DOORV_CLOSE || c == DOORV_OPEN) && side == 0 && ray.hitTypeV == 'S'))
        return (1);
    ray.hitTypeH = c;
    ray.disH = sqrt(pow(ray.rx - data->player.px, 2) + pow(ray.ry - data->player.py, 2));
    if (side == 0)
        ray.sideH = ray.sideV;
    tile = (t_tex){0};
    init_tile(data, &ray, &tile);
    tex = get_texture(data, &ray);
    return (check_alpha(ray, tile, tex));
}

int check_alpha(t_ray ray, t_tex tile, t_img *tex)
{
    int x;
    int y;
    int w;

    x = ray.r * STRIP_WIDTH;
    y = 0;
    while (y < WINDOW_HEIGHT)
    {
        if (y >= tile.lineOff && y < tile.lineH + tile.lineOff)
        {
            if (get_color((int)tile.tx, (int)tile.ty, tex) != -1)
                return (1);
            tile.ty += tile.ty_step;
        }
        y++;
    }
    return (0);
}
