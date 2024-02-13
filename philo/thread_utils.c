/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:50:05 by mkong             #+#    #+#             */
/*   Updated: 2024/02/13 18:34:02 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		pthread_mutex_unlock(ph->mutex_die);
		return (1);
	}
	pthread_mutex_unlock(ph->mutex_die);
	return (0);
}

int	last_in(t_philo *ph)
{
	pthread_mutex_lock(ph->mutex);
	if (ph->id == ph->philos - 1)
	{
		*ph->last_in = 1;
		// gettimeofday(ph->st_tv, NULL);
	}
	if (*ph->last_in == 1)
	{
		// ph->last_eat = *ph->st_tv;
		pthread_mutex_unlock(ph->mutex);
		return (1);
	}
	pthread_mutex_unlock(ph->mutex);
	return (0);
}

int	get_time(t_time st_tv)
{
	t_time	p_tv;
	int		p_ms;

	gettimeofday(&p_tv, NULL);
	p_ms = p_tv.tv_sec * 1000 + p_tv.tv_usec / 1000;
	p_ms -= st_tv.tv_sec * 1000 + st_tv.tv_usec / 1000;
	return (p_ms);
}
