/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behavior_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:26:43 by mkong             #+#    #+#             */
/*   Updated: 2024/03/21 19:49:05 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ph_eating(t_philo *ph)
{
	t_time	eat_tv;

	prt_bh("%d %d is eating\n", get_time(ph->st_tv), ph->id, ph, 0);
	gettimeofday(&eat_tv, NULL);
	while (get_time(eat_tv) < ph->eat)
	{
		usleep(200);
		check_die(ph);
	}
	gettimeofday(&ph->last_eat, NULL);
	putdown_fork(ph);
	if (ph->eat_num > 0)
		if (--ph->eat_num == 0)
			exit(0);
}

void	ph_sleeping(t_philo *ph)
{
	t_time	sleep_tv;

	prt_bh("%d %d is sleeping\n", get_time(ph->st_tv), ph->id, ph, 0);
	gettimeofday(&sleep_tv, NULL);
	while (get_time(sleep_tv) < ph->sleep)
	{
		usleep(200);
		check_die(ph);
	}
}

void	ph_thinking(t_philo *ph)
{
	check_die(ph);
	prt_bh("%d %d is thinking\n", get_time(ph->st_tv), ph->id, ph, 0);
	usleep(200);
}

void	check_die(t_philo *ph)
{
	if (get_time(ph->last_eat) > ph->die)
	{
		prt_bh("%d %d is died\n", get_time(ph->st_tv), ph->id, ph, 1);
		exit(1);
	}
}
