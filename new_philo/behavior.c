/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behavior.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:23:32 by mkong             #+#    #+#             */
/*   Updated: 2024/03/20 20:46:50 by mkong            ###   ########.fr       */
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

void	ph_eating(t_philo *ph)
{
	t_time	eat_tv;

	if (ph->state != ready_to_eat)
		return ;
	pthread_mutex_lock(ph->print_mutex);
	if (!check_die(ph))
		printf("%d %d is eating\n", get_time(*ph->st_tv), ph->id);
	pthread_mutex_unlock(ph->print_mutex);
	gettimeofday(&eat_tv, NULL);
	while (get_time(eat_tv) < ph->eat)
	{
		usleep(200);
		if (check_die(ph))
			return ;
	}
	ph->state = eating;
	gettimeofday(&ph->last_eat, NULL);
	if (ph->eat_num > 0)
		ph->eat_num--;
}

void	ph_sleeping(t_philo *ph)
{
	t_time	sleep_tv;

	if (ph->state != eating)
		return ;
	pthread_mutex_lock(ph->print_mutex);
	if (!check_die(ph))
		printf("%d %d is sleeping\n", get_time(*ph->st_tv), ph->id);
	pthread_mutex_unlock(ph->print_mutex);
	gettimeofday(&sleep_tv, NULL);
	while (get_time(sleep_tv) < ph->sleep)
	{
		usleep(200);
		if (check_die(ph))
			return ;
	}
	ph->state = sleeping;
}

void	ph_thinking(t_philo *ph)
{
	if (ph->state != sleeping)
		return ;
	pthread_mutex_lock(ph->print_mutex);
	if (!check_die(ph))
	{
		printf("%d %d is thinking\n", get_time(*ph->st_tv), ph->id);
		ph->state = thinking;
	}
	pthread_mutex_unlock(ph->print_mutex);
	usleep(200);
}
