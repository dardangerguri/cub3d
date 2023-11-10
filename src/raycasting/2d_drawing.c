/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardangerguri <dardangerguri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:40:17 by dgerguri          #+#    #+#             */
/*   Updated: 2023/11/09 22:27:12 by dardangergu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_blocks(t_map_data *data, int x, int y, uint32_t color)
{printf("%d\n", x);
	int	block_y;
	int	block_x;

	block_y = 0;
	while (block_y < SIZE_B - 1)
	{
		block_x = 0;
		while (block_x < SIZE_B - 1)
		{
			mlx_put_pixel(data->mlx_data->window, x + block_x, y + block_y, color);
			block_x++;
		}
		block_y++;
	}
}

static void	get_top_left_y_and_x(t_map_data *data, int *y, int *x, int type)
{
	int	pos_x;
	int	pos_y;

	pos_x = ((int)data->pos.x / SIZE_B) + 1;
	pos_y = ((int)data->pos.y / SIZE_B) + 1;
	if (type == 1)
	{
		if (pos_y > 3)
			*y = pos_y - 3;
		else
			*y = 0;
	}
	else if (type == 2)
	{
		if (pos_x > 5)
			*x = pos_x - 5;
		else
			*x = 0;
	}
}

void draw_map_long(t_map_data *data, int row, int column, int x)
{
	int y;
	uint32_t color;

	get_top_left_y_and_x(data, &y, 0, 1);
	while (y < 6)
	{
		column = 0;
		get_top_left_y_and_x(data, 0, &x, 2);
		while ((size_t)x < 10)
		{
				if (x < (int)ft_strlen(data->map[y]) && data->map[y][x] == '1')
					color = 0x808080;
				else if (x < (int)ft_strlen(data->map[y]) \
					&& (data->map[y][x] == '0' || (data->map[y][x] != ' ' \
					&& ft_strrchr("NSWE", data->map[y][x]))))
					color = 0x0000FF;
				else
					color = 0x000000;
				draw_blocks(data, column * SIZE_B, row * SIZE_B, color);
			x++;
			column++;
		}
		y++;
		row++;
	}
}


void	draw_map(t_map_data *data)
{
	// printf("PLAYER X: %d\n", (int)data->pos.x / SIZE_B);
	int x;
	int y;
	uint32_t color;

	x = 0;
	y = 0;
	if (data->longest_line > 10 || data->map_size > 6)
		draw_map_long(data, 0, 0, 0);
		// printf("helo");
	else
	{
		while (data->map[y] && (y * SIZE_B) < HEIGHT_W)
		{
			x = 0;
			while (data->map[y][x] && (x * SIZE_B) < WIDTH_W)
			{
				if (x < (int)ft_strlen(data->map[y]) && data->map[y][x] == '1')
					color = 0x808080;
				else if (x < (int)ft_strlen(data->map[y]) \
					&& (data->map[y][x] == '0' || (data->map[y][x] != ' ' \
					&& ft_strrchr("NSWE", data->map[y][x]))))
					color = 0x0000FF;
				else
					color = 0x000000;
				draw_blocks(data, x * SIZE_B, y * SIZE_B, color);
				x++;
			}
			y++;
		}
	}
}

static void	draw_player_block(t_map_data *data, float x, float y, uint32_t color)
{
	int	block_y;
	int	block_x;

	block_y = 0;
	while (data->pos.x >= 0 && data->pos.y >= 0 && block_y < SIZE_P)
	{
		block_x = 0;
		while (block_x < SIZE_P)
		{
			mlx_put_pixel(data->mlx_data->window, x + block_x, y + block_y, color);
			block_x++;
		}
		block_y++;
	}
}

void	draw_player(t_map_data *data)
{
	int	block_y;
	int	block_x;

	block_y = 0;
	while ((block_y * SIZE_B) < HEIGHT_W)
	{
		block_x = 0;
		while ((block_x * SIZE_B) < WIDTH_W)
		{
			draw_player_block(data, (data->pos.x ), (data->pos.y), 0xDFFF00);
			block_x++;
		}
		block_y++;
	}
}

void	draw_nose(t_map_data *data)
{
	t_float_v	angle;
	t_float_v	pos;
	float		i;

	angle.x = data->dir.x;
	angle.y = data->dir.y;
	pos.x = data->pos.x + SIZE_P / 2;
	pos.y = data->pos.y + SIZE_P / 2;
	i = 0;
	while (i < 20 && pos.y > -1 && pos.x > -1)
	{
		mlx_put_pixel(data->mlx_data->window, pos.x, pos.y, 0xF000FF);
		pos.y += angle.y;
		pos.x += angle.x;
		i++;
	}
}
