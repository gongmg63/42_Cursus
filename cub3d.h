/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:12:39 by mkong             #+#    #+#             */
/*   Updated: 2024/04/16 17:27:28 by mkong            ###   ########.fr       */
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
# define texture_width		64
# define texture_height		64

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

typedef	struct s_dda
{
	int		hit;
	int		step_x;
	int		step_y;
	int		side;
	int		map_x;
	int		map_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_dda;

typedef struct s_info
{
	t_img	img;
	t_data	data;
	void	*mlx;
	void	*win;
	char	(*map)[10];
	int		**texture;
	double	pos_x; //플레이어의 현재 위치
	double	pos_y;
	double	dir_x; //방향벡터 - 내가 어디를 보고 있는지, 항상 크기는 1로 고정
	double	dir_y;
	double	raydir_x; //레이저의 방향벡터
	double	raydir_y;
	double	plane_x; //카메라평면의 끝점 - 방향벡터 + 위치벡터 + 플레인벡터 / 방향벡터 + 위치벡터 - 플레인벡터
	double	plane_y;
	double	camera_x; //카메라 평면 - 실제 계산에 쓰기위해 화면을 축소? 시킨것
	double	move_speed;
	double	rotate_speed;
}	t_info;

//darw.c
void    my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_verline(t_info info, int draw_start, int draw_end, int y, int color);

//event.c
int		exit_window(void);
int		key_press(int keycode, t_info *info);
void	rotate_press(int keycode, t_info *info);
void	set_pos(double *pos_x, double *pos_y, int keycode, t_info *info);
void	move_position(int keycode, t_info *info);

//calc_ray.c
void	calc_ray(t_info *info);


#endif
