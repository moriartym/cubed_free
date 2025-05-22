#include "../cub3d.h"

void win(t_var *data)
{
    int px;
    int py;

    px = (int)(data->player.px / TILE_SIZE);
    py = (int)(data->player.py / TILE_SIZE);
    if (data->map.arr[py][px] == WIN_BLOCK)
    {
        printf("🎉 You win!\nPress R to play again\n");
        data->state.state = WIN;
    }
}

void change_to_win(t_var *data, t_bfs *bfs, int index)
{
    int i;
    int x;
    int y;

    i = 0;
    y = 0;
    while (y < data->map.height)
    {
        x = 0;
        while (x < data->map.width)
        {
            if (bfs->reachable[y][x] == true && !(y == bfs->ipy && x == bfs->ipx))
                i++;
            if (i == index)
            {
                x = (int) data->player.px / TILE_SIZE;
                y = (int) data->player.py / TILE_SIZE - 5;
                data->map.arr[y][x] = WIN_BLOCK;
                data->win_sprite.x = x * TILE_SIZE + 0.5 * TILE_SIZE;
                data->win_sprite.y = y * TILE_SIZE + 0.5 * TILE_SIZE;
                return ;
            }
            x++;
        }
        y++;
    }
}

void place_winning_tiles(t_var *data)
{
    t_bfs bfs;
    int y;
    int index;

    bfs = (t_bfs){0};
    do_bfs(data, &bfs);
    if (bfs.empty_spaces > 1)
    {
        index = rand() % bfs.empty_spaces;
        change_to_win(data, &bfs, index);
    } 
    else
        printf("Sorry, no winning tiles for this game.\n");
    free_enemy_bfs(data, &bfs);
}

void draw_win(t_var *data)
{
    t_edraw draw;

    draw = (t_edraw){0};
    init_enemy_draw(data, &draw);
    if (enemy_size(data, &draw, &data->win_sprite))
        return ;
    draw.cur_img = &data->map.textures[WIN_TILE].attr;
    screen_draw(data, &draw);
}
