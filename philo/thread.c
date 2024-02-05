/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:23:05 by mkong             #+#    #+#             */
/*   Updated: 2024/02/05 21:32:25 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*st_simul(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (ph->exist_die == 0 && ph->eat_num == 0)
	{
		if (ph->exist_die == 0)
			pickup_fork_eat(ph);
		if (ph->exist_die == 0)
			think(ph);
		if (ph->exist_die == 0)
			sleep(ph);
		if (ph->exist_die == 0)
			think(ph);
	}
}

void	simulation(t_philo **ph, t_info *info)
{
	pthread_mutex_t	*mutex;
	pthread_t		*tid;
	int				i;

	i = -1;
	tid = (pthread_t *)malloc(sizeof(pthread_t) * info->philos);
	if (tid == 0)
	{
		info->error = 1;
		return ;
	}
	pthread_mutex_init(mutex, NULL);
	gettimeofday(&info->st_tv, NULL);
	while (++i < info->philos)
	{
		ph[i]->mutex = mutex;
		ph[i]->last_eat = ph[i]->st_tv;
		pthread_create(&tid[i], NULL, st_simul, ph[i]);
	}
	i = -1;
	while (++i < info->philos)
		pthread_join(tid[i], NULL);
}
