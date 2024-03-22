/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:54:33 by mkong             #+#    #+#             */
/*   Updated: 2024/03/22 18:44:06 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *ph)
{
	if (ph->id % 2 == 0)
	{
		take_left_fork(ph);
		take_right_fork(ph);
	}
	else
	{
		take_right_fork(ph);
		take_left_fork(ph);
	}
}

void	take_left_fork(t_philo *ph)
{
	pthread_mutex_lock(&((*ph->fork_mutex)[ph->id]));
	if (ph->fork[ph->id] == 0)
	{
		pthread_mutex_lock(ph->print_mutex);
		if (!check_die(ph))
			printf("%d %d has taken a fork\n", get_time(*ph->st_tv), ph->id + 1);
		pthread_mutex_unlock(ph->print_mutex);
		ph->fork[ph->id] = 1;
		if (ph->state == take_a_fork)
			ph->state = ready_to_eat;
		else
			ph->state = take_a_fork;
	}
	pthread_mutex_unlock(&((*ph->fork_mutex)[ph->id]));
}

void	take_right_fork(t_philo *ph)
{
	pthread_mutex_lock(&((*ph->fork_mutex)[(ph->id + 1) % ph->philos]));
	if (ph->fork[(ph->id + 1) % ph->philos] == 0)
	{
		pthread_mutex_lock(ph->print_mutex);
		if (!check_die(ph))
			printf("%d %d has taken a fork\n", get_time(*ph->st_tv), ph->id + 1);
		pthread_mutex_unlock(ph->print_mutex);
		ph->fork[(ph->id + 1) % ph->philos] = 1;
		if (ph->state == take_a_fork)
			ph->state = ready_to_eat;
		else
			ph->state = take_a_fork;
	}
	pthread_mutex_unlock(&((*ph->fork_mutex)[(ph->id + 1) % ph->philos]));
}

void	putdown_fork(t_philo *ph)
{
	if (ph->state != eating)
		return ;
	pthread_mutex_lock(&((*ph->fork_mutex)[(ph->id + 1) % ph->philos]));
	ph->fork[(ph->id + 1) % ph->philos] = 0;
	pthread_mutex_unlock(&((*ph->fork_mutex)[(ph->id + 1) % ph->philos]));
	pthread_mutex_lock(&((*ph->fork_mutex)[ph->id]));
	ph->fork[ph->id] = 0;
	pthread_mutex_unlock(&((*ph->fork_mutex)[ph->id]));
}

int	check_die(t_philo *ph)
{
	pthread_mutex_lock(ph->die_mutex);
	if (*ph->exist_die == 1)
	{
		pthread_mutex_unlock(ph->die_mutex);
		return (1);
	}
	if (get_time(ph->last_eat) > ph->die)
	{
		printf("%d %d is died\n", get_time(*ph->st_tv), ph->id + 1);
		*ph->exist_die = 1;
		pthread_mutex_unlock(ph->die_mutex);
		return (1);
	}
	pthread_mutex_unlock(ph->die_mutex);
	return (0);
}
