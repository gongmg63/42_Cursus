/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:07:08 by mkong             #+#    #+#             */
/*   Updated: 2024/03/20 15:13:59 by mkong            ###   ########.fr       */
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

typedef struct s_info
{
	t_time	*st_tv;
	int		*fork;
	int		philos;
	int		die;
	int		eat;
	int		sleep;
	int		eat_num;	
	int		error;
}	t_info;

typedef struct s_philo
{
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*mutex_die;
	struct s_philo	**phs;
	t_time			*st_tv;
	t_time			last_eat;
	int				*fork;
	int				*exist_die;
	int				*last_in;
	int				state;
	int				id;
	int				die;
	int				eat;
	int				sleep;
	int				philos;
	int				eat_num;
}	t_philo;

int		ft_atoi(const char *str, t_info *p);
void	simulation(t_philo **ph, t_info *info);
void	pickup_fork_eat(t_philo *ph);
void	thinking(t_philo *ph);
void	sleeping(t_philo *ph);
int		check_die(t_philo *ph);
int		get_time(t_time st_tv);
void	pickup_fork(t_philo *ph);
void	eating(t_philo *ph);
void	putdown_fork(t_philo *ph);
int		last_in(t_philo *ph);

#endif
