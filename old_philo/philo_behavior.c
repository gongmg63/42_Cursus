/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behavior.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 20:55:58 by mkong             #+#    #+#             */
/*   Updated: 2024/03/20 15:14:05 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pickup_fork(t_philo *ph)
{
	pthread_mutex_lock(ph->mutex);
	if (!check_die(ph)
		&& ph->fork[(ph->id + 1) % ph->philos] == 0 && ph->fork[ph->id] == 0)
	{
		printf("%d ms %d has taken a fork\n", get_time(*ph->st_tv), ph->id);
		printf("%d ms %d has taken a fork\n", get_time(*ph->st_tv), ph->id);
		ph->fork[(ph->id + 1) % ph->philos] = 1;
		ph->fork[ph->id] = 1;
		ph->state = 1;
	}
	pthread_mutex_unlock(ph->mutex);
}

void	eating(t_philo *ph)
{
	t_time	eat_tv;

	usleep(50);
	if (ph->state != 1 || ph->eat_num == 0)
		return ;
	gettimeofday(&eat_tv, NULL);
	printf("%d ms %d is eating\n", get_time(*ph->st_tv), ph->id);
	while (get_time(eat_tv) < ph->eat)
	{
		if (check_die(ph))
			return ;
		usleep(50);
		if (check_die(ph))
			return ;
	}
	gettimeofday(&ph->last_eat, NULL);
	if (ph->eat_num > 0)
		ph->eat_num--;
}

void	putdown_fork(t_philo *ph)
{
	if (ph->state != 1)
		return ;
	pthread_mutex_lock(ph->mutex);
	ph->fork[ph->id] = 0;
	ph->fork[(ph->id + 1) % ph->philos] = 0;
	ph->state = 2;
	pthread_mutex_unlock(ph->mutex);
}

void	sleeping(t_philo *ph)
{
	t_time	sleep_tv;

	usleep(50);
	if (check_die(ph) || ph->state != 2)
		return ;
	gettimeofday(&sleep_tv, NULL);
	printf("%d ms %d is sleeping\n", get_time(*ph->st_tv), ph->id);
	while (get_time(sleep_tv) < ph->sleep)
	{
		if (check_die(ph))
			return ;
		usleep(50);
		if (check_die(ph))
			return ;
	}
	ph->state = 0;
	return ;
}

void	thinking(t_philo *ph)
{
	usleep(50);
	if (check_die(ph))
		return ;
	if (ph->state == 0)
	{
		printf("%d ms %d is thinking\n", get_time(*ph->st_tv), ph->id);
		ph->state = 1;
	}
	return ;
}
