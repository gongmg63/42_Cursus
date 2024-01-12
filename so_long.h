/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:24:10 by mkong             #+#    #+#             */
/*   Updated: 2024/01/12 16:43:45 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./libft/libft.h"

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
	t_node	*next_node;
	t_point	p;
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
}			t_mlx;

t_stack	*check_map_route(char **map, t_stack *st);
t_point	pop(t_stack *st);
t_point	find_start(char **map);
t_point	check_h_w(char **map);
t_point	find_start(char **map);
size_t	check_nl(char *buf);
size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);
char	*ft_strnjoin(char *s1, char const *s2, size_t n);
char	*ft_strndup(const char *s1, size_t n);
int		find_node(t_stack *st, t_point p);
int		check_element(char c);
int		check_edge(char **map);
int		*check_map_element(char **map);
int		check_map_valid(char **map, t_stack *visit, int count[3]);
void	initialize(t_stack *st);
void	push(t_stack *st, t_point p);
void	check_map_size(char **map, t_mlx *m);

#endif
