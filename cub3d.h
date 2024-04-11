/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:12:39 by mkong             #+#    #+#             */
/*   Updated: 2024/04/09 20:41:35 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "./libft/libft.h"
# include "./mlx/mlx.h"

# define KEY_W				13
# define KEY_A				0
# define KEY_D				2
# define KEY_S				1
# define KEY_ESC 			53
# define KEY_AR_L 			123
# define KEY_AR_R 			124
# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_EXIT	17
# define WIDTH				1000
# define HEIGHT				1000

typedef enum e_map_component
{
	wall,
	empty,
	space,
	east,
	west,
	south,
	north
}	t_map_component;

typedef struct s_data {
  void	*img;
  char	*addr;
  int	bits_per_pixel;
  int	line_length;
  int	endian;
}    t_data;

typedef struct	s_img
{
	void	*img;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}	t_img;

typedef struct s_info
{
	void	*mlx;
	void	*win;
	char	**map;
	t_img	img;
	t_data	data;
	double	pos_X;
	double	pos_Y;
	double	move_speed;
}	t_info;

// #define texWidth 64
// #define texHeight 64
// #define mapWidth 24
// #define mapHeight 24
// #define width 640
// #define height 480

// typedef struct	s_info
// {
// 	double posX;
// 	double posY;
// 	double dirX;
// 	double dirY;
// 	double planeX;
// 	double planeY;
// 	void	*mlx;
// 	void	*win;
// 	t_img	img;
// 	int		buf[height][width];
// 	int		**texture;
// 	double	moveSpeed;
// 	double	rotSpeed;
// 	int		re_buf;

// }				t_info;

#endif