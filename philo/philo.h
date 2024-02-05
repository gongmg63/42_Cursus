/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:07:08 by mkong             #+#    #+#             */
/*   Updated: 2024/02/05 21:33:10 by mkong            ###   ########.fr       */
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
	t_time	st_tv;
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
	t_philo			**phs;
	t_time			*st_tv;
	t_time			*last_eat;
	int				*exist_die;
	int				state[3];
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
void	think(t_philo *ph);
void	sleep(t_philo *ph);
void	check_die(t_philo *ph);
int		get_time(t_time st_tv);

#endif
