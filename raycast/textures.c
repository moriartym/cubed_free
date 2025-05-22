#include "../cub3d.h"

void    load_textures(t_var *data)
{
    t_id *tex;
    int i;

    i = 0;
    tex = data->map.textures;
    while (i <= WEST)
    {
        extract_img(data->mlx, &tex[i].attr, tex[i].filename, data);
        i++;
    }
    while (i <= CEILING)
    {
        extract_rgb(&tex[i].color, tex[i].filename, data);
        i++;
    }
    extract_img(data->mlx,&tex[WIN_TILE].attr, "./textures/tiles/sayuri.xpm", data);
    extract_img(data->mlx, &tex[DOOR_C].attr, "./textures/doors/door_close.xpm", data);
    extract_img(data->mlx, &tex[DOOR_O].attr, "./textures/doors/door_open.xpm" , data);
    extract_rgb(&tex[DOOR_S].color, DOOR_SIDE_COLOR ,data);
}

int extract_img(void *mlx, t_img *attr, char *filename, t_var *data)
{
    attr->img = mlx_xpm_file_to_image(mlx, filename, &attr->width, &attr->height);
    if (!attr->img)
        handle_error("mlx_xpm_file_to_image failed", filename, &data->map, data);
    attr->addr = mlx_get_data_addr(attr->img, &attr->bits_per_pixel, &attr->line_length, &attr->endian);
    if (!attr->addr)
        handle_error("mlx_get_data_addr failed", filename, &data->map, data);
    return (0);
}

int    extract_rgb(int *color, char *rgb , t_var *data)
{
    char    **colors;

    colors = ft_split(rgb, ',');
	if (!colors)
        handle_error(NULL, "malloc failed", &data->map, data);
    *color = (ft_atoi(colors[0]) << 16) | (ft_atoi(colors[1]) << 8) | ft_atoi(colors[2]);
    ft_free_2d(&colors);
    return (0);
}

t_img *get_texture(t_var *data, t_ray *ray)
{
    if (ray->hitTypeH == DOORH_CLOSE || ray->hitTypeH == DOORH_OPEN)
    {
        if (ray->hitTypeH == DOORH_CLOSE)
            return (&data->map.textures[DOOR_C].attr);
        return (&data->map.textures[DOOR_O].attr);
    }
    else if (ray->hitTypeH == DOORV_CLOSE || ray->hitTypeH == DOORV_OPEN)
    {
        if (ray->hitTypeH == DOORV_CLOSE)
            return (&data->map.textures[DOOR_C].attr);
        return (&data->map.textures[DOOR_O].attr);
    }
    if (ray->sideH == 0)
    {
        if (ray->rx > data->player.px)
            return (&data->map.textures[EAST].attr);  // Facing East
        return (&data->map.textures[WEST].attr);  // Facing West
    }
    else
    {
        if (ray->ry > data->player.py)
            return (&data->map.textures[SOUTH].attr);  // Facing South
        return (&data->map.textures[NORTH].attr);  // Facing North
    }
}

int    get_color(int x, int y, t_img *tex)
{
    int pixel_index;
    int color;

    pixel_index = y * tex->line_length + x * (tex->bits_per_pixel / 8);
    color = *(int *)(tex->addr + pixel_index);

    if ((color & 0x00FFFFFF) == 0x000000)  // transparent
        return -1;
    return color;
}
