/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:23:05 by mkong             #+#    #+#             */
/*   Updated: 2024/02/07 20:10:45 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(t_time st_tv)
{
	t_time	p_tv;
	int		p_ms;

	gettimeofday(&p_tv, NULL);
	p_ms = p_tv.tv_sec * 1000 + p_tv.tv_usec / 1000;
	p_ms -= st_tv.tv_sec * 1000 + st_tv.tv_usec / 1000;
	return (p_ms);
}

int	check_die(t_philo *ph)
{
	pthread_mutex_lock(ph->mutex_die);
	if (*ph->exist_die == 1)
	{
		pthread_mutex_unlock(ph->mutex_die);
		return (1);
	}
	if (get_time(ph->last_eat) > ph->die)
	{
		printf("%d ms %d is died\n", get_time(*ph->st_tv), ph->id);
		*ph->exist_die = 1;
	}
	pthread_mutex_unlock(ph->mutex_die);
	return (*ph->exist_die);
}

void	*st_simul(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (*ph->exist_die == 0 && ph->eat_num != 0)
	{	
		usleep(1);
		if (*ph->exist_die == 0 && ph->eat_num != 0)
			pickup_fork(ph);
		if (*ph->exist_die == 0 && ph->eat_num != 0)
			eating(ph);
		if (*ph->exist_die == 0 && ph->eat_num != 0)
			putdown_fork(ph);
		if (*ph->exist_die == 0 && ph->eat_num != 0)
			thinking(ph);
		if (*ph->exist_die == 0 && ph->eat_num != 0)
			sleeping(ph);
		if (*ph->exist_die == 0 && ph->eat_num != 0)
			thinking(ph);
	}
	return ((void *)ph);
}

void	simulation(t_philo **ph, t_info *info)
{
	pthread_mutex_t	mutex;
	pthread_mutex_t	mutex_die;
	pthread_t		*tid;
	int				i;

	i = -1;
	tid = (pthread_t *)malloc(sizeof(pthread_t) * info->philos);
	if (tid == 0)
	{
		info->error = 1;
		return ;
	}
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&mutex_die, NULL);
	gettimeofday(&info->st_tv, NULL);
	while (++i < info->philos)
	{
		ph[i]->last_eat = info->st_tv;
		ph[i]->mutex = &mutex;
		ph[i]->mutex_die = &mutex_die;
		pthread_create(&tid[i], NULL, st_simul, ph[i]);
	}
	i = -1;
	while (++i < info->philos)
		pthread_join(tid[i], NULL);
	pthread_mutex_destroy(&mutex);
	pthread_mutex_destroy(&mutex_die);
}
