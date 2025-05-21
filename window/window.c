#include "../cub3d.h"

int close_window(t_var *data)
{
    if (data->mlx && data->win)
        mlx_destroy_window(data->mlx, data->win);
    if (data->mlx)
    {
        /* UNCOMMENT BEFORE SUBMISSION */
        // mlx_destroy_display(data->mlx);
        free(data->mlx);
    }
    // handle_error(NULL, NULL, &data->map, data);// exit 1
    exit(0);
    return 0;
}


int render(t_var *data)
{
    if (data->state.state == LOSE)
        show_lose_screen(data);
    else if (data->state.state == WIN)
        show_win_screen(data);
    else if (data->state.state == RETRY)
    {
        printf("retry\n");
        init_all(data);
    }
    else
    {
        update_movement(data);
        create_minimap(data);
        draw_player(data);
        draw_rays(data);
        draw_enemies_minimap(data);
        mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
    }
    return (0);
}

int create_visual(t_map *map)
{
    t_var data = {0};

    data.state.state = INIT;
    data.map = *map;
    init_all(&data);
    create_image_buffer(&data);
    load_textures(&data);  
    mlx_loop_hook(data.mlx, render, &data);
    mlx_hook(data.win, DestroyNotify, StructureNotifyMask, &close_window, &data);
    mlx_hook(data.win, KeyPress, KeyPressMask, &handle_keypress, &data);
    mlx_hook(data.win, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
    mlx_hook(data.win, 6, (1L<<6), &handle_mouse_move, &data);
    mlx_loop(data.mlx);
    return 0;
}
