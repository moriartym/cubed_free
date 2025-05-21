#include "../cub3d.h"

bool is_wall(t_map *map, int x, int y)
{
    if (y < 0 || y >= map->height || map->arr[y] == NULL)
        return false;
    if (x < 0 || x >= (int)ft_strlen(map->arr[y]))
        return false;
    char c = map->arr[y][x];
    return (c == '1' || c == '8');
}

void cast_vertical(t_var* data, t_ray* ray)
{
    ray->disV = 100000;
    ray->dof = 0;
    ray->tan = - tan(ray->ra);
    if (cos(ray->ra) > 0.001)
    {
        ray->rx = ((int)(data->player.px) / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
        ray->ry = (data->player.px - ray->rx) * ray->tan + data->player.py;
        ray->xo = TILE_SIZE;
        ray->yo = -ray->xo * ray->tan;
    }
    else if (cos(ray->ra) < -0.001)
    {
        ray->rx = ((int)(data->player.px) / TILE_SIZE) * TILE_SIZE - 0.0001;
        ray->ry = (data->player.px - ray->rx) * ray->tan + data->player.py;
        ray->xo = -TILE_SIZE;
        ray->yo = -ray->xo * ray->tan;
    }
    else
    {
        ray->rx = data->player.px;
        ray->ry = data->player.py;
        ray->dof = 8;
    }
    vertical_dof(data, ray);
}

void vertical_dof(t_var* data, t_ray* ray)
{
    if (data->map.arr[(int)data->player.py / TILE_SIZE][(int)data->player.px / TILE_SIZE] == DOORH_CLOSE)
    {
        if (data->player.py - ((int)data->player.py / TILE_SIZE * TILE_SIZE) > (TILE_SIZE - DOORWIDTH) / 2 && ray->ra > M_PI)
        {
            ray->rx -= ray->xo;
            ray->ry -= ray->yo;
            ray->dof -= 1;
        }
        else if (data->player.py - ((int)data->player.py / TILE_SIZE * TILE_SIZE) < (TILE_SIZE - DOORWIDTH) / 2 && ray->ra <= M_PI)
        {
            ray->rx -= ray->xo;
            ray->ry -= ray->yo;
            ray->dof -= 1;
        }
    }
    while (ray->dof < data->map.width)
    {
        ray->mx = (int)(ray->rx) / TILE_SIZE;
        ray->my = (int)(ray->ry) / TILE_SIZE;
        ray->oriX = ray->rx;
        ray->oriY = ray->ry;
        ray->sideV = 0;
        if (is_wall(&data->map, ray->mx, ray->my) || (is_door(&data->map, ray, 0) && check_door_alpha(data, *ray, 0) == 1))
        {
            if (ray->hitTypeV != 'S')
                ray->hitTypeV = data->map.arr[ray->my][ray->mx];
            ray->dof = data->map.width;
            ray->vx = ray->rx;
            ray->vy = ray->ry;
            ray->disV = sqrt(pow(ray->rx - data->player.px, 2) + pow(ray->ry - data->player.py, 2));
        }
        else
        {
            ray->rx = ray->oriX + ray->xo;
            ray->ry = ray->oriY + ray->yo;
            ray->dof += 1;
        }
    }
}

void cast_horizontal(t_var* data, t_ray* ray)
{
    ray->disH = 100000;
    ray->dof = 0;
    ray->tan =  1 / ray->tan;
    if (sin(ray->ra) < -0.001)
    {
        ray->ry = ((int)(data->player.py) / TILE_SIZE) * TILE_SIZE - 0.0001;
        ray->rx = (data->player.py - ray->ry) * ray->tan + data->player.px;
        ray->yo = -TILE_SIZE;
        ray->xo = -ray->yo * ray->tan;
    }
    else if (sin(ray->ra) > 0.001)
    {
        ray->ry = ((int)(data->player.py) / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
        ray->rx = (data->player.py - ray->ry) * ray->tan + data->player.px;
        ray->yo = TILE_SIZE;
        ray->xo = -ray->yo * ray->tan;
    }
    else
    {
        ray->rx = data->player.px;
        ray->ry = data->player.py;
        ray->dof = 8;
    }
    horizontal_dof(data, ray);
}

void horizontal_dof(t_var* data, t_ray* ray)
{
    if (data->map.arr[(int)data->player.py / TILE_SIZE][(int)data->player.px / TILE_SIZE] == DOORH_CLOSE)
    {
        if (data->player.py - ((int)data->player.py / TILE_SIZE * TILE_SIZE) > (TILE_SIZE - DOORWIDTH) / 2 && ray->ra > M_PI)
        {
            ray->rx -= ray->xo;
            ray->ry -= ray->yo;
            ray->dof -= 1;
        }
        else if (data->player.py - ((int)data->player.py / TILE_SIZE * TILE_SIZE) < (TILE_SIZE - DOORWIDTH) / 2 && ray->ra <= M_PI)
        {
            ray->rx -= ray->xo;
            ray->ry -= ray->yo;
            ray->dof -= 1;
        }
    }
    while (ray->dof < data->map.height)
    {
        ray->mx = (int)(ray->rx) / TILE_SIZE;
        ray->my = (int)(ray->ry) / TILE_SIZE;
        ray->oriX = ray->rx;
        ray->oriY = ray->ry;
        ray->sideH = 1;
        if (is_wall(&data->map, ray->mx, ray->my) || (is_door(&data->map, ray, 1) && check_door_alpha(data, *ray, 1) == 1))
        {
            if (ray->hitTypeH != 'S')
                ray->hitTypeH = data->map.arr[ray->my][ray->mx];
            ray->dof = data->map.height;
            ray->disH = sqrt(pow(ray->rx - data->player.px, 2) + pow(ray->ry - data->player.py, 2));
        }
        else
        {
            ray->rx = ray->oriX + ray->xo;
            ray->ry = ray->oriY + ray->yo;
            ray->dof += 1;
        }
    }
}
