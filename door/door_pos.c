#include "../cub3d.h"

void translate_ray(t_ray *ray, int side, char c)
{
    float dy;
    if (side == 1 && (c == DOORH_CLOSE || c == DOORH_OPEN))
    {
        if (ray->ra <= PI)
            dy = (ray->my * TILE_SIZE + (TILE_SIZE - DOORWIDTH) / 2) - ray->ry;
        else
            dy = (ray->my * TILE_SIZE + (TILE_SIZE - DOORWIDTH) / 2 + DOORWIDTH) - ray->ry;
        ray->rx += ray->xo * dy / ray->yo;
        ray->ry += dy;
    }
    else if (side == 0 && (c == DOORV_CLOSE || c == DOORV_OPEN))
    {
        if (ray->ra > PI/2 && ray->ra < 1.5 * PI)
            dy = (ray->mx * TILE_SIZE + (TILE_SIZE - DOORWIDTH) / 2 + DOORWIDTH) - ray->rx;
        else
            dy = (ray->mx * TILE_SIZE + (TILE_SIZE - DOORWIDTH) / 2) - ray->rx;
        ray->ry += ray->yo * dy / ray->xo;
        ray->rx += dy;
    }
}

bool is_door_side(t_door *cur, t_ray *ray, int side, char c)
{
    if (cur->xStart <= ray->rx && cur->xEnd >= ray->rx && cur->yStart <= ray->ry && cur->yEnd >= ray->ry)
    {
        if (side == 1 && (c == DOORV_CLOSE || c == DOORV_OPEN))
            ray->hitTypeH = 'S';
        else if (side == 0 && (c == DOORH_CLOSE || c == DOORH_OPEN))
            ray->hitTypeV = 'S';
        return (true);
    }
    return (false);
}

bool doorv_from_side_check(t_ray *ray, t_door *cur, int side, char c)
{
    float dx;
    if ((c == DOORV_CLOSE || c == DOORV_OPEN) && side == 1)
    {
        if (ray->ra > PI/2 && ray->ra < 1.5 * PI)
            dx = cur->xEnd - ray->rx;
        else
            dx = cur->xStart - ray->rx;
        ray->ry += ray->yo * dx / ray->xo;
        ray->rx += dx;
        if (cur->xStart <= ray->rx && cur->xEnd >= ray->rx && cur->yStart <= ray->ry && cur->yEnd >= ray->ry)
        {
            ray->sideH = 0;
            return (true);
        }
        ray->ry = ray->oriY;
        ray->rx = ray->oriX;
    }
    return (false);
}

bool doorh_from_side_check(t_ray *ray, t_door *cur, int side, char c)
{
    float dy;
    if ((c == DOORH_CLOSE || c == DOORH_OPEN) && side == 0)
    {
        if (ray->ra <= PI)
            dy = cur->yStart - ray->ry;
        else
            dy = cur->yEnd - ray->ry;
        ray->rx += ray->xo * dy / ray->yo;
        ray->ry += dy;
        if (cur->xStart <= ray->rx && cur->xEnd >= ray->rx && cur->yStart <= ray->ry && cur->yEnd >= ray->ry)
        {
            ray->sideV = 1;
            return (true);
        }
        ray->rx = ray->oriX;
        ray->ry = ray->oriY;
    }
    return (false);
}

bool is_door(t_map *map, t_ray *ray, int side)
{
    char c;
    t_door *cur;

    if (ray->my < 0 || ray->my >= map->height || map->arr[ray->my] == NULL)
        return false;
    if (ray->mx < 0 || ray->mx >= (int)ft_strlen(map->arr[ray->my]))
        return false;
    c = map->arr[ray->my][ray->mx];
    if (c != DOORH_OPEN && c != DOORH_CLOSE && c != DOORV_OPEN && c != DOORV_CLOSE)
        return (false);
    translate_ray(ray, side, c);
    cur = map->doors;
    while (cur != NULL)
    {
        if (c == map->arr[cur->idY][cur->idX])
        {
            if (is_door_side(cur, ray, side, c) == true ||
                doorh_from_side_check(ray, cur, side, c) == true ||
                doorv_from_side_check(ray, cur, side, c) == true)
                return (true);
        }
        cur = cur->next;
    }
    return (false);
}
