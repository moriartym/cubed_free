#include "../cub3d.h"

void free_single_img(void **img_ptr, t_var *data)
{
	if (img_ptr && *img_ptr)
	{
		mlx_destroy_image(data->mlx, *img_ptr);
		*img_ptr = NULL;
	}
}

void free_enemy_gifs(t_var *data)
{
	free_single_img((void **)&data->gif.zero.img, data);
	free_single_img((void **)&data->gif.one.img, data);
	free_single_img((void **)&data->gif.two.img, data);
	free_single_img((void **)&data->gif.three.img, data);
	free_single_img((void **)&data->gif.four.img, data);
	free_single_img((void **)&data->gif.five.img, data);
	free_single_img((void **)&data->gif.six.img, data);
	free_single_img((void **)&data->gif.seven.img, data);
	free_single_img((void **)&data->gif.eight.img, data);
}

void free_state_images(t_var *data)
{
	free_single_img((void **)&data->state.win.img, data);
	free_single_img((void **)&data->state.lose.img, data);
}

void close_window_err(t_var *data, char *err)
{
	handle_error(NULL, err, &data->map, data);
    if (data->mlx && data->win)
        mlx_destroy_window(data->mlx, data->win);
    if (data->mlx)
    {
        /* UNCOMMENT BEFORE SUBMISSION */
        // mlx_destroy_display(data->mlx);
        free(data->mlx);
    }
}

void clean_texture(t_map *map)
{
	ft_free_ptr((void **)&map->textures[NORTH].filename);
	ft_free_ptr((void **)&map->textures[EAST].filename);
	ft_free_ptr((void **)&map->textures[SOUTH].filename);
	ft_free_ptr((void **)&map->textures[WEST].filename);
	ft_free_ptr((void **)&map->textures[FLOOR].filename);
	ft_free_ptr((void **)&map->textures[CEILING].filename);
}


void clean_temp(t_map *map)
{
	ft_free_2d(&map->temp_arr);
	ft_free_ptr((void **)&map->temp_str);
}

void safe_close(int *fd)
{
	if (*fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}

void clean_map(t_map *map)
{
	safe_close(&map->open_fd);
	clean_texture(map);
	clean_temp(map);
	ft_free_2d(&map->arr);
}

void clean_data(t_var *data)
{
	free_enemy_gifs(data);
	free_state_images(data);
	ft_free_ptr((void **)&data->sprites);
	free_single_img(&data->image.img, data);
}



void	handle_error(char *err, char *msg, t_map *map, t_var *data)
{
	ft_putstr_fd("Error\n", 2);
	if (err)
	{
		ft_putstr_fd(err, 2);
		ft_putstr_fd("\n", 2);
	}
	if (msg)
		ft_error_return(msg);
	if (map)
		clean_map(map);
	if (data)
		clean_data(data);
	exit (1);
}

int	element_err(int line)
{
	char	*str;

	str = ft_itoa(line);
	if (!line)
		return (ft_error_return("malloc failed"));
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("Invalid configuration of map elements in line ", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	free(str);
	return (0);
}
