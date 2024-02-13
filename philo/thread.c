/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:23:05 by mkong             #+#    #+#             */
/*   Updated: 2024/02/13 18:39:45 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_time(t_philo *ph)
{
	gettimeofday(ph->st_tv, NULL);
	ph->last_eat = *ph->st_tv;
}

void	*st_simul(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (1)
		if (last_in(ph))
			break ;
	set_time(ph);
	if (ph->id % 2 == 1)
		usleep(ph->die / 4 * 1000);
	while ((ph->eat_num != 0 && !check_die(ph)))
	{	
		if ((ph->id + 1) % ph->philos != ph->id
			&& ph->eat_num != 0 && !check_die(ph))
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

void	set_ph(t_philo *p, t_info *i, pthread_mutex_t *m, pthread_mutex_t *md)
{
	// p->last_eat = *i->st_tv;
	(void)i;
	p->mutex = m;
	p->mutex_die = md;
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
	while (++i < info->philos)
	{
		set_ph(ph[i], info, &mutex, &mutex_die);
		pthread_create(&tid[i], NULL, st_simul, ph[i]);
	}
	while (--i >= 0)
		pthread_join(tid[i], NULL);
	free(tid);
	pthread_mutex_destroy(&mutex);
	pthread_mutex_destroy(&mutex_die);
}
