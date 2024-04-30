/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:12:39 by mkong             #+#    #+#             */
/*   Updated: 2024/04/30 16:30:29 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "essential.h"
# include "./map_parsing/parsing.h"

# define KEY_W				13
# define KEY_A				0
# define KEY_D				2
# define KEY_S				1
# define KEY_ESC 			53
# define KEY_AR_L 			123
# define KEY_AR_R 			124
# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_EXIT	17
# define WIDTH				1920
# define HEIGHT				1080
# define TEXTURE_WIDTH		64
# define TEXTURE_HEIGHT		64

typedef struct s_data
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_data;

typedef struct s_dda
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
}	t_dda;

typedef struct s_draw_info
{
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		color;
}	t_draw_info;

typedef struct s_texture_info
{
	int		tex_num;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		color;
}	t_texture_info;

typedef struct s_info
{
	t_data	data;
	void	*mlx;
	void	*win;
	char	**map;
	int		**texture;
	int		f_c_color[2];
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	raydir_x;
	double	raydir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	double	move_speed;
	double	rotate_speed;
}	t_info;

//set_info.c
t_texture_info	set_texture_info(t_info *info, t_dda *dda, t_draw_info *d_info);
t_draw_info		set_draw_info(t_info *info, t_dda *dda);
t_dda			set_dda_info(t_info *info, int i);
void			set_info(t_info *info, t_map_info *map_info);
void			set_texture_util(t_info *info, t_map_info *map_info);

//cub3d.c
void			find_start_point(t_info *info, t_map_info *map_info);
void			set_floor_ceiling_color(t_info *info, t_map_info *map_info);
char			**copy_map(t_map_info *map_info);

//darw.c
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			draw_texture_line(t_info *info, t_dda *dda, \
				t_draw_info *d_info, int i);
void			draw_floor(t_info *info, int color);
void			draw_ceiling(t_info *info, int color);

//event.c
int				exit_window(void);
int				key_press(int keycode, t_info *info);
void			rotate_press(int keycode, t_info *info);
void			set_pos(double *pos_x, double *pos_y, \
				int keycode, t_info *info);
void			move_position(int keycode, t_info *info);

//calc_ray.c
void			calc_ray(t_info *info);
void			get_sidedist(t_info *info, t_dda *dda);
void			get_lay_length(t_info *info, t_dda *dda);

//set_info_utils.c
void			set_image(t_info *info, int *texture, char *path, t_data *data);
void			set_texture_image(t_info *info, t_map_info *map_info);

#endif
