#include "../cub3d.h"

void load_enemy_gifs(t_var *data)
{
    load_single_image(data, &data->gif.zero,  "textures/enemy/hangy-0.xpm");
    load_single_image(data, &data->gif.one,   "textures/enemy/hangy-1.xpm");
    load_single_image(data, &data->gif.two,   "textures/enemy/hangy-2.xpm");
    load_single_image(data, &data->gif.three, "textures/enemy/hangy-3.xpm");
    load_single_image(data, &data->gif.four,  "textures/enemy/hangy-4.xpm");
    load_single_image(data, &data->gif.five,  "textures/enemy/hangy-5.xpm");
    load_single_image(data, &data->gif.six,   "textures/enemy/hangy-6.xpm");
    load_single_image(data, &data->gif.seven, "textures/enemy/hangy-7.xpm");
    load_single_image(data, &data->gif.eight, "textures/enemy/hangy-8.xpm");
}

void forbidden_enemy(t_var *data, t_bfs *bfs)
{
    int y;
    int x;

    y = bfs->ipy - 5;
    while (y <= bfs->ipy + 5)
    {
        x = bfs->ipx - 5;
        while (x <= bfs->ipx + 5)
        {
            if (y >= 0 && y < data->map.height && x >= 0 && x < data->map.width)
            {
                if (bfs->reachable[y][x] == true)
                {
                    bfs->reachable[y][x] = false;
                    bfs->empty_spaces--;
                }
            }
            x++;
        }
        y++;
    }
}

void place_enemy_helper(t_var *data, t_bfs *bfs, t_place *enemy)
{
    enemy->x = 0;
    while (enemy->x < data->map.width)
    {
        if (bfs->reachable[enemy->y][enemy->x] == true)
        {
            if (enemy->i == enemy->index)
            {
                bfs->reachable[enemy->y][enemy->x] = false;
                bfs->empty_spaces--;
                data->save.sprites[enemy->count].x = enemy->x * 32 + 16;
                data->save.sprites[enemy->count].y = enemy->y * 32 + 16;
                data->sprites[enemy->count].x = enemy->x * 32 + 16;
                data->sprites[enemy->count].y = enemy->y * 32 + 16;
                enemy->count++;
                break;
            }
            enemy->i++;
        }
        enemy->x++;
    }
}

void place_enemy(t_var *data, t_bfs *bfs)
{
    t_place enemy;

    enemy = (t_place){0};
    enemy.count = 0;
    forbidden_enemy(data, bfs);
    while (enemy.count < data->num_sprites && bfs->empty_spaces > 0)
    {
        enemy.index = rand() % bfs->empty_spaces;
        enemy.i = 0;
        enemy.y = 0;
        while (enemy.y < data->map.height)
        {
            place_enemy_helper(data, bfs, &enemy);
            if (enemy.count > 0 && enemy.i == enemy.index)
                break;
            enemy.y++;
        }
    }
    data->num_sprites = enemy.count;
}

void init_sprites(t_var *data)
{
    t_bfs bfs;
    int x;

    bfs = (t_bfs){0};
    srand(time(NULL));
    do_bfs(data, &bfs);
    data->num_sprites = bfs.empty_spaces / 30;
    data->sprites = malloc(sizeof(t_sprite) * (data->num_sprites + 1));
    if (!data->sprites)
        enemy_bfs_error(data, &bfs, "malloc error");
    data->save.sprites = malloc(sizeof(t_sprite) * (data->num_sprites + 1)); // new check this
    if (!data->sprites)
        enemy_bfs_error(data, &bfs, "malloc error");
    x = 0;
    while (x <= data->num_sprites)
    {
        data->sprites[x] = (t_sprite){0};
        data->sprites[x] = (t_sprite){0};
        data->save.sprites[x].is_unstucking = 1;
        data->save.sprites[x].is_unstucking = 1;
        x++;
    }
    place_enemy(data, &bfs);    
    free_enemy_bfs(data, &bfs);
}
