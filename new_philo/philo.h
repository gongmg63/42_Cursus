/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:10:27 by mkong             #+#    #+#             */
/*   Updated: 2024/03/21 11:20:34 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct timeval	t_time;

typedef enum e_state
{
	start,
	take_a_fork,
	ready_to_eat,
	eating,
	thinking,
	sleeping,
	died
}	t_state;

typedef struct s_info
{
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	die_mutex;
	pthread_mutex_t	print_mutex;
	t_time			*st_tv;
	int				*fork;
	int				philos;
	int				die;
	int				eat;
	int				sleep;
	int				eat_num;	
	int				error;
}	t_info;

typedef struct s_philo
{
	pthread_mutex_t	**fork_mutex;
	pthread_mutex_t	*die_mutex;
	pthread_mutex_t	*print_mutex;
	struct s_philo	**phs;
	t_time			*st_tv;
	t_time			last_eat;
	t_state			state;
	int				*fork;
	int				*exist_die;
	int				id;
	int				die;
	int				eat;
	int				sleep;
	int				philos;
	int				eat_num;
}	t_philo;

int		simulation(t_philo **ph, t_info *info);
int		ft_atoi(const char *str, t_info *p);
int		get_time(t_time st_tv);
int		check_die(t_philo *ph);
void	take_right_fork(t_philo *ph);
void	take_left_fork(t_philo *ph);
void	putdown_fork(t_philo *ph);
void	ph_sleeping(t_philo *ph);
void	ph_thinking(t_philo *ph);
void	take_fork(t_philo *ph);
void	ph_eating(t_philo *ph);
void	free_info(t_info *info);
void	free_phs(t_philo **phs);

#endif
