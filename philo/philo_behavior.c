/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behavior.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 20:55:58 by mkong             #+#    #+#             */
/*   Updated: 2024/02/05 21:26:19 by mkong            ###   ########.fr       */
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

void	pickup_fork_eat(t_philo *ph)
{
	if (check_die(ph))
		return ;
	pthread_mutex_lock(ph->mutex);
	if (ph->state[1] == 1
		&& !ph->phs[(ph->id + 1) % ph->philos]->state[0]
		&& !ph->phs[(ph->id + ph->philos - 1) % ph->philos]->state[0])
	{
		printf("%d ms %d has taken a fork\n", get_time(*ph->st_tv), ph->id);
		printf("%d ms %d has taken a fork\n", get_time(*ph->st_tv), ph->id);
		gettimeofday(ph->last_eat, NULL);
		printf("%d ms %d is eating\n", get_time(*ph->st_tv), ph->id);
		if (ph->eat_num > 0)
			ph->eat_num--;
		memset(ph->state, 0, sizeof(ph->state));
		ph->state[0] = 1;
		while (get_time(*ph->last_eat) < ph->eat)
			usleep(ph->eat * 100);
		gettimeofday(ph->last_eat, NULL);
	}
	pthread_mutex_unlock(ph->mutex);
}

void	think(t_philo *ph)
{
	printf("%d ms %d is thinking\n", get_time(*ph->st_tv), ph->id);
	memset(ph->state, 0, sizeof(ph->state));
	ph->state[1] = 1;
	return ;
}

void	sleep(t_philo *ph)
{
	t_time	sleep_tv;

	gettimeofday(&sleep_tv, NULL);
	printf("%d ms %d is sleeping\n", get_time(*ph->st_tv), ph->id);
	memset(ph->state, 0, sizeof(ph->state));
	ph->state[2] = 1;
	while (get_time(sleep_tv) < ph->sleep)
	{
		if (check_die(ph))
			return ;
		usleep(ph->sleep * 100);
		if (check_die(ph))
			return ;
	}
	return ;
}

int	check_die(t_philo *ph)
{
	if (get_time(*ph->last_eat) > ph->die)
	{
		printf("%d ms %d is died\n", get_time(*ph->st_tv), ph->id);
		*ph->exist_die = 1;
	}
	return (*ph->exist_die);
}
