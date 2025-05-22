#include "../cub3d.h"

void handle_error_noexit(char *err, char *msg, t_map *map, t_var *data)
{
	if (msg || err)
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
}

void	handle_error(char *err, char *msg, t_map *map, t_var *data)
{
	handle_error_noexit(err, msg, map, data);
	exit (1);
}


