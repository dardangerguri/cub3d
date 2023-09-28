/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dardangerguri <dardangerguri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:02:23 by dgerguri          #+#    #+#             */
/*   Updated: 2023/09/28 22:28:14 by dardangergu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFF
#  define BUFF 42
# endif

/******************************************************************************/
/*								Includes  									  */
/******************************************************************************/

# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h> //read
# include <sys/uio.h> //read
# include <stdbool.h>

# include "../libft/includes/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

/******************************************************************************/
/*								Error Messages	 							  */
/******************************************************************************/

# define X_VALID_ARGUMENTS "Error: Invalid number of arguments!\n"
# define X_VALID_FILE "Error: The map is not a .cub file!\n"
# define X_OPEN_FILE "Error: Couldn't open the file!\n"
# define X_READ_FILE "Error: Couldn't read the file!\n"
# define X_MALLOC "Error: Malloc allocation has failed!\n"
# define X_UNKNOWN_ELEMENT "Error: Unknown element on the file!\n"
# define X_UNKNOWN_ELEMENT_MAP "Error: Unknown element on the map!\n"
# define X_MULTIPLE_S_POINTS "Error: More than 1 starting point!\n"
# define X_S_P_MISSING "Error: Starting point is missing!\n"
# define X_MISSING_TEXTURE "Error: Texture file is missing!\n"
# define X_MISSING_COLOR "Error: Color is missing!\n"
# define X_WRONG_TEXTURE_FILE "Error: Wrong texture file!\n"
# define X_WRONG_COLOR_VALUE "Error: Wrong color value!\n"
# define X_EMPTY_LINES "Error: Map has empty lines!\n"
# define X_MAP_NOT_CLOSED "Error: Map not closed with walls!\n"
# define X_MLX "Error: MLX has failed!\n"

/******************************************************************************/
/*								Structs 									  */
/******************************************************************************/

typedef struct s_mlx_data
{
	mlx_t			*mlx;
	mlx_image_t		*window;
	mlx_texture_t	*north;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	mlx_texture_t	*south;
}				t_mlx_data;

typedef struct s_map_data
{
	char		**file_splitted;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	int			*floor;
	int			*ceiling;
	char		**map;
	t_mlx_data	*mlx_data;
}				t_map_data;

typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

/******************************************************************************/
/*								Functions									  */
/******************************************************************************/

/* error */
char		*print_error_message(char *message);
bool		error_message(char *message);

/* util.c */
char		**free_array(char **ret);
char		**duplicate_map(char **map);

/* cleanup */
void		cleanup(t_map_data *data);

/*---------------------------------Init---------------------------------------*/

/* data_init */
bool		data_init(t_map_data *data, char *map);

/* read_map */
bool		read_map(t_map_data *data, char *file);

/* split_line */
char		**ft_split_line(char const *s);

/* mlx_init */
bool	init_mlx(t_map_data *data);

/*---------------------------------Parsing------------------------------------*/

/* split_elements_map */
char		*parse_file(t_map_data *data);
char		*save_the_elements(t_map_data *data, int i, int j, bool *error);

/* validate_elements */
bool		validate_elements(t_map_data *data);

/* parse_colors */
void		parse_colors(t_map_data *data, int i, int j, bool *error);

/* validate_map */
bool		validate_map(char **map);

/* validate_map_utils */
t_vector	find_empty_space(char **map);
t_vector	get_last_point(char **map);
void		remove_newline(char **map);
bool		map_filled(char **map);
bool		find_wall(char **map, t_vector pos);




/* validate_map_utils_two */ //PROBABLY DELETE THE WHOLE FILE!
// bool		check_edges(char **map);

/* TEMPORARY IN MAIN*/
void		print_struct(t_map_data *data);

#endif
