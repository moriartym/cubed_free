#include "../cub3d.h"

t_door *new_door(int x, int y, char *tile)
{
    t_door *new;
    
    new = malloc(sizeof(t_door));
    if (!new)
        return (NULL);
    new->idX = x;
    new->idY = y;
    if (*tile == DOORH_CLOSE || *tile == DOORH_OPEN)
    {
        new->xStart = x * TILE_SIZE;
        new->xEnd = new->xStart + TILE_SIZE;
        new->yStart = y * TILE_SIZE + (TILE_SIZE - DOORWIDTH) / 2;
        new->yEnd = new->yStart + DOORWIDTH;
    }
    else
    {
        new->xStart = x * TILE_SIZE + (TILE_SIZE - DOORWIDTH) / 2;
        new->xEnd = new->xStart + DOORWIDTH;    
        new->yStart = y * TILE_SIZE;
        new->yEnd = new->yStart + TILE_SIZE;
    }
    new->next = NULL;
    new->status = tile;
    return (new);
}

void add_door(t_var *data, int x, int y, char *tile)
{
    t_door *new;
    t_door *cur;

    new = new_door(x, y, tile);
    if (!new)
        ft_error_exit("malloc failed");
    if (data->map.doors == NULL)
    {
        data->map.doors = new;
        return ;
    }
    cur = data->map.doors;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = new;
}

void delete_door(t_var *data, int x, int y)
{
    t_door *cur;
    t_door *prev;

    prev = NULL;
    cur = data->map.doors;
    while (cur != NULL)
    {
        if (cur->idX == x && cur->idY == y)
        {
            if (prev == NULL)
                data->map.doors = cur->next;
            else
                prev->next = cur->next;
            free(cur);
            break ;
        }
        prev = cur;
        cur = cur->next;
    }
}

void create_door(t_var *data)
{
    char *tile;
    int tile_in_front_x;
    int tile_in_front_y;

    tile_in_front_x = get_front_tile_x(data);
    tile_in_front_y = get_front_tile_y(data);
    if (tile_in_front_x >= 0 && tile_in_front_x < data->map.width &&
        tile_in_front_y >= 0 && tile_in_front_y < data->map.height)
    {
        tile = &data->map.arr[tile_in_front_y][tile_in_front_x];
        if (*tile == '0')
        {
            float angle = normalize_radians(data->player.pa);
            if ((angle > M_PI / 4 && angle < 3 * M_PI / 4) || (angle > 5 * M_PI / 4 && angle < 7 * M_PI / 4))
                *tile = DOORH_CLOSE;
            else
                *tile = DOORV_CLOSE;
            add_door(data, tile_in_front_x, tile_in_front_y, tile);
        }
        else if (*tile == DOORH_CLOSE || *tile == DOORH_OPEN || *tile == DOORV_CLOSE || *tile == DOORV_OPEN)
        {
            *tile = '0';
            delete_door(data, tile_in_front_x, tile_in_front_y);
        }
    }
}

void open_door(t_var *data)
{
    int tile_in_front_x;
    int tile_in_front_y;

    tile_in_front_x = get_front_tile_x(data);
    tile_in_front_y = get_front_tile_y(data);
    if (tile_in_front_x >= 0 && tile_in_front_x < data->map.width &&
        tile_in_front_y >= 0 && tile_in_front_y < data->map.height)
    {
        char *tile = &data->map.arr[tile_in_front_y][tile_in_front_x];
        if (*tile == DOORH_CLOSE || *tile == DOORV_CLOSE)
        {
            *tile += 1;
            printf("%c: Door Opened\n", *tile);
        }
        else if (*tile == DOORH_OPEN || *tile == DOORV_OPEN)
        {
            *tile -= 1;
            printf("%c: Door Closed\n", *tile);
        }
    }
}
