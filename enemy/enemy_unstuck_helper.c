#include "../cub3d.h"

void ebfs_one(t_enemy_bfs *bfs, t_var *data)
{
    bfs->size = bfs->width * bfs->height;
    bfs->front = 0;
    bfs->rear = 0;
    bfs->queue_x = malloc(sizeof(int) * bfs->size);
    if (!bfs->queue_x)
        enemy_move_bfs_error(data, bfs, "malloc failed");
    bfs->queue_y = malloc(sizeof(int) * bfs->size);
    if (!bfs->queue_y)
        enemy_move_bfs_error(data, bfs, "malloc failed");
    bfs->visited = malloc(sizeof(bool *) * bfs->height);
    if (!bfs->visited)
        enemy_move_bfs_error(data, bfs, "malloc failed");
    bfs->prev_x = malloc(sizeof(int *) * bfs->height);
    if (!bfs->prev_x)
        enemy_move_bfs_error(data, bfs, "malloc failed");
    bfs->prev_y = malloc(sizeof(int *) * bfs->height);
    if (!bfs->prev_y)
        enemy_move_bfs_error(data, bfs, "malloc failed");
}

void ebfs_two(t_enemy_bfs *bfs, t_var *data)
{
    bfs->y = 0;
    while (bfs->y < bfs->height)
    {
        bfs->visited[bfs->y] = malloc(sizeof(bool) * bfs->width);
        if (!bfs->visited[bfs->y])
            enemy_move_bfs_error(data, bfs, "malloc failed (visited row)");
        bfs->prev_x[bfs->y] = malloc(sizeof(int) * bfs->width);
        if (!bfs->prev_x[bfs->y])
            enemy_move_bfs_error(data, bfs, "malloc failed (prev_x row)");
        bfs->prev_y[bfs->y] = malloc(sizeof(int) * bfs->width);
        if (!bfs->prev_y[bfs->y])
            enemy_move_bfs_error(data, bfs, "malloc failed (prev_y row)");
        bfs->x = 0;
        while (bfs->x < bfs->width)
        {
            bfs->visited[bfs->y][bfs->x] = false;
            bfs->prev_x[bfs->y][bfs->x] = -1;
            bfs->prev_y[bfs->y][bfs->x] = -1;
            bfs->x++;
        }
        bfs->y++;
    }
}

void ebfs_three(t_enemy_bfs *bfs)
{
    bfs->dir[0][0] = 0;
    bfs->dir[0][1] = -1;
    bfs->dir[1][0] = 0;
    bfs->dir[1][1] = 1;
    bfs->dir[2][0] = -1;
    bfs->dir[2][1] = 0;
    bfs->dir[3][0] = 1;
    bfs->dir[3][1] = 0;
}

void ebfs_four(char **map, t_enemy_bfs *bfs)
{
    bfs->queue_x[bfs->rear] = bfs->start_x;
    bfs->queue_y[bfs->rear] = bfs->start_y;
    bfs->rear++;
    bfs->visited[bfs->start_y][bfs->start_x] = true;
    while (bfs->front < bfs->rear)
    {
        bfs->x = bfs->queue_x[bfs->front];
        bfs->y = bfs->queue_y[bfs->front];
        bfs->front++;
        if (bfs->x == bfs->goal_x && bfs->y == bfs->goal_y)
            break;
        ebfs_four_helper(map, bfs);
    }
}

void ebfs_four_helper(char **map,t_enemy_bfs *bfs)
{
    bfs->i = 0;
    while (bfs->i < 4)
    {
        bfs->nx = bfs->x + bfs->dir[bfs->i][0];
        bfs->ny = bfs->y + bfs->dir[bfs->i][1];

        if (bfs->nx >= 0 && bfs->ny >= 0 &&
            bfs->nx < bfs->width && bfs->ny < bfs->height &&
            !bfs->visited[bfs->ny][bfs->nx] && map[bfs->ny][bfs->nx] == '0')
        {
            bfs->queue_x[bfs->rear] = bfs->nx;
            bfs->queue_y[bfs->rear] = bfs->ny;
            bfs->rear++;
            bfs->visited[bfs->ny][bfs->nx] = true;
            bfs->prev_x[bfs->ny][bfs->nx] = bfs->x;
            bfs->prev_y[bfs->ny][bfs->nx] = bfs->y;
        }
        bfs->i++;
    }
}

