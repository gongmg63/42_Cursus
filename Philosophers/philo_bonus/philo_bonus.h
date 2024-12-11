/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:55:48 by mkong             #+#    #+#             */
/*   Updated: 2024/03/21 19:48:06 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>

typedef struct timeval	t_time;

typedef struct s_philo
{
	sem_t	*forks_sem;
	sem_t	*die_sem;
	sem_t	*print_sem;
	t_time	st_tv;
	t_time	last_eat;
	int		philos;
	int		id;
	int		die;
	int		eat;
	int		sleep;
	int		eat_num;
}	t_philo;

int		ft_atoi(const char *str);
int		get_time(t_time st_tv);
void	check_die(t_philo *ph);
void	simulation(t_philo *philo);
void	prt_bh(char *s, int time, int id, t_philo *ph, int die);
void	take_fork(t_philo *ph);
void	putdown_fork(t_philo *ph);
void	ph_eating(t_philo *ph);
void	ph_sleeping(t_philo *ph);
void	ph_thinking(t_philo *ph);
void	free_philo(t_philo *ph);

#endif
