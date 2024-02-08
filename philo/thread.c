/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:23:05 by mkong             #+#    #+#             */
/*   Updated: 2024/02/08 19:45:22 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*st_simul(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (1)
		if (last_in(ph))
			break ;
	while (ph->eat_num != 0 && !check_die(ph))
	{	
		if (ph->eat_num != 0 && !check_die(ph))
			pickup_fork(ph);
		if (ph->eat_num != 0 && !check_die(ph))
			eating(ph);
		if (!check_die(ph))
			putdown_fork(ph);
		if (!check_die(ph))
			sleeping(ph);
		if (ph->eat_num != 0 && !check_die(ph))
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
	// gettimeofday(info->st_tv, NULL);
	while (++i < info->philos)
	{
		ph[i]->last_eat = *info->st_tv;
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
