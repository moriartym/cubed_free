#include "../cub3d.h"

void	free_all_door(t_var *data)
{
	t_door	*cur;
	t_door	*next;
    if (!data->map.doors)
        return; 

	cur = data->map.doors;
	while (cur)
	{
		next = cur->next;
		ft_free_ptr((void **)&cur);
		cur = next;
	}
	data->map.doors = NULL;
}

void safe_close(int *fd)
{
	if (*fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}

void free_single_img(void **img_ptr, t_var *data)
{
	if (img_ptr && *img_ptr)
	{
		mlx_destroy_image(data->mlx, *img_ptr);
		*img_ptr = NULL;
	}
}
