/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardangerguri <dardangerguri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:43:20 by dgerguri          #+#    #+#             */
/*   Updated: 2023/09/28 20:00:13 by dardangergu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_mlx_data(t_mlx_data *data)
{
	data->mlx = NULL;
	data->window = NULL;

}

static void	init_map_data(t_map_data *data)
{
	data->file_splitted = NULL;
	data->north = NULL;
	data->south = NULL;
	data->west = NULL;
	data->east = NULL;
	data->floor = malloc(sizeof(int) * 3);
	data->ceiling = malloc(sizeof(int) * 3);
	data->map = NULL;
	init_mlx_data(&data->mlx_data);
}

bool	data_init(t_map_data *data, char *map)
{
	init_map_data(data);
	if (!read_map(data, map))
		return (false);
	if (!parse_file(data))
		return (false);
	if (!validate_elements(data))
		return (false);
	if (!validate_map(data->map))
		return (false);
	if (!init_mlx(data))
		return (false);
	return (true);
}