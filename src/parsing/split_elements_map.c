/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_elements_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:13:06 by dgerguri          #+#    #+#             */
/*   Updated: 2023/09/27 20:05:38 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	remove_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

static bool	check_element_exists(t_map_data *data, char c)
{
	int	flag;

	flag = 0;
	if (c == 'N' && data->north)
		flag = 1;
	else if (c == 'S' && data->south)
		flag = 1;
	else if (c == 'W' && data->west)
		flag = 1;
	else if (c == 'E' && data->east)
		flag = 1;
	else if (c == 'F' && data->floor[0] >= 0)
		flag = 1;
	else if (c == 'C' && data->ceiling[0] >= 0)
		flag = 1;
	if (flag == 1)
		return (error_message(X_UNKNOWN_ELEMENT));
	return (true);
}

char	*save_the_elements(t_map_data *data, int i, int j, bool *error)
{
	char	*str;

	if (!check_element_exists(data, data->file_splitted[i][0]))
	{
		*(error) = true;
		return (NULL);
	}
	if (data->file_splitted[i][j] != ' ' && data->file_splitted[i][j] != '\t')
	{
		print_error_message(X_UNKNOWN_ELEMENT);
		*(error) = true;
	}
	j += remove_whitespace(&data->file_splitted[i][j]);
	str = ft_strdup(&data->file_splitted[i][j]);
	if (!str)
	{
		print_error_message(X_MALLOC);
		*(error) = true;
	}
	return (str);
}

static char	*save_the_map(t_map_data *data, int i, int j, bool *error)
{
	char	*str;

	if (data->file_splitted[i][j] == '\n' \
		&& data->file_splitted[i + 1] != NULL)
	{
		print_error_message(X_EMPTY_LINES);
		*(error) = true;
		return (NULL);
	}
	str = ft_strdup(&data->file_splitted[i][j]);
	if (!str)
	{
		print_error_message(X_MALLOC);
		*(error) = true;
	}
	return (str);
}

static int	get_elements(t_map_data *data, int i, int j, bool *error)
{
	while (data->file_splitted[i] && !(*error))
	{
		if (data->file_splitted[i][0] != '\n')
			j = remove_whitespace(data->file_splitted[i]);
		if (!ft_strncmp(&data->file_splitted[i][j], "NO", 2))
			data->north = save_the_elements(data, i, j + 2, error);
		else if (!ft_strncmp(&data->file_splitted[i][j], "SO", 2))
			data->south = save_the_elements(data, i, j + 2, error);
		else if (!ft_strncmp(&data->file_splitted[i][j], "WE", 2))
			data->west = save_the_elements(data, i, j + 2, error);
		else if (!ft_strncmp(&data->file_splitted[i][j], "EA", 2))
			data->east = save_the_elements(data, i, j + 2, error);
		else if (!ft_strncmp(&data->file_splitted[i][j], "F", 1) \
			|| !ft_strncmp(&data->file_splitted[i][j], "C", 1))
			parse_colors(data, i, j, error);
		else if (!ft_strncmp(&data->file_splitted[i][j], "1", 1))
			break ;
		else if (data->file_splitted[i][0] != '\n')
		{
			print_error_message(X_UNKNOWN_ELEMENT);
			*(error) = true;
		}
		i++;
	}
	return (i);
}

char	*parse_file(t_map_data *data)
{
	int		i;
	int		j;
	bool	error;

	i = 0;
	j = 0;
	error = false;
	if (data->file_splitted[i])
		i = get_elements(data, i, j, &error);
	if (error)
		return (NULL);
	j = i;
	while (data->file_splitted[i])
		i++;
	data->map = malloc(sizeof(char *) * (i - j + 1));
	if (!data->map)
		return (print_error_message(X_MALLOC));
	i = 0;
	while (data->file_splitted[j] && !error)
		data->map[i++] = save_the_map(data, j++, 0, &error);
	if (error)
		return (NULL);
	data->map[i] = NULL;
	return ("Splitted");
}
