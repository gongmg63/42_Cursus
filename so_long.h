/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:24:10 by mkong             #+#    #+#             */
/*   Updated: 2024/01/16 21:56:48 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_W		13
# define KEY_ESC	53
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include "./mlx/mlx.h"

typedef struct s_read_info
{
	char			*buf;
	int				fd;
	size_t			idx;
}				t_read_info;

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

typedef struct s_node
{
	struct s_node	*next_node;
	t_point			p;
}				t_node;

typedef struct s_stack
{
	t_node	*top;
	int		size;
}			t_stack;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_point	p;
	char	**map;
	int		collect;
	int		cnt;
}			t_mlx;

t_point	pop(t_stack *st);
t_point	find_start(char **map);
t_point	check_h_w(char **map);
t_point	find_start(char **map);
size_t	check_nl(char *buf);
size_t	ft_strlen(const char *s);
char	**read_map(char *file);
char	*get_next_line(int fd);
char	*ft_strnjoin(char *s1, char const *s2, size_t n);
char	*ft_strndup(const char *s1, size_t n);
int		find_node(t_stack *st, t_point p);
int		check_element(char c);
int		check_edge(char **map);
int		check_map(char **map);
void	check_map_element(char **map, int count[3]);
void	draw_map(char **map, t_mlx *m);
void	push(t_stack *st, t_point p);
void	initialize(t_stack *st);
void	clear_st(t_stack *st);
void	move_w(t_mlx *m);
void	move_a(t_mlx *m);
void	move_s(t_mlx *m);
void	move_d(t_mlx *m);



void	error_exit(char *s);




#endif
