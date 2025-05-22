#include "../cub3d.h"

int get_lineH(float dist, float pa, float ra)
{
    int lineH;

    dist *= cos(normalize_radians(pa - ra));
    lineH = (TILE_SIZE * WINDOW_HEIGHT) / dist;
    return (lineH);
}

void    init_tile(t_var *data, t_ray *ray, t_tex *tile)
{
    tile->lineH = get_lineH(ray->disH, data->player.pa, ray->ra);
    tile->ty_step = (float)TILE_SIZE_TEXTURE /(float)tile->lineH;
    if (tile->lineH > WINDOW_HEIGHT)
    {
        tile->ty_off = (tile->lineH - WINDOW_HEIGHT)/2.0;
        tile->lineH = WINDOW_HEIGHT;
    }
    tile->lineOff = (WINDOW_HEIGHT/2) - (tile->lineH >> 1);
    tile->ty = tile->ty_off * tile->ty_step;

    if (ray->sideH == 1)
    {
        tile->tx = (int)(ray->rx) % TILE_SIZE;
        if (ray->ra > PI)
            tile->tx = TILE_SIZE - tile->tx - 1;
        if (ray->ra <= PI && ray->hitTypeH != '1')
            tile->tx = TILE_SIZE - tile->tx - 1;
    }
    else
    {
        tile->tx = (int)(ray->ry) % TILE_SIZE;
        if (ray->ra > PI/2 && ray->ra < 1.5 * PI && ray->hitTypeH == '1')
            tile->tx = TILE_SIZE - tile->tx - 1;
    }
    tile->tx = tile->tx * TILE_SIZE_TEXTURE / TILE_SIZE;
}

void draw_3d(t_var *data, t_ray *ray)
{
    t_tex tile;

    tile = (t_tex){0};
    init_tile(data, ray, &tile);
    draw_3d_helper(data, ray, &tile);
}

void draw_3d_helper(t_var *data, t_ray *ray, t_tex *tile)
{
    t_img *tex;
    int color;
    int y;
    int w;
    int x;
    
    tex = get_texture(data, ray);
    x = ray->r * STRIP_WIDTH;
    y = 0;
    while (y < WINDOW_HEIGHT)
    {
        if (y < tile->lineOff)
        color = data->map.textures[CEILING].color;
        else if (y < tile->lineH + tile->lineOff)
        {
            color = get_color((int)tile->tx, (int)tile->ty, tex);
            if (ray->hitTypeH == 'S')
                color = data->map.textures[DOOR_S].color;
            tile->ty += tile->ty_step;
        }
        else
            color = data->map.textures[FLOOR].color;
        draw_wall_strip(&data->image, x, y, color);
        y++;
    }
}

void    draw_wall_strip(t_img *img, int x, int y, int color)
{
    int w;

    w = 0;
    while (w < STRIP_WIDTH)
    {
        if (x + w >= WINDOW_WIDTH)
            return ;
        else if (x + w < MINIMAP_SIZE && y < MINIMAP_SIZE)
            return ;
        my_mlx_pixel_put(img, x + w, y, color);
        w++;   
    }
}
