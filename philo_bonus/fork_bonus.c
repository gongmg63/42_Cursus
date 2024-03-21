/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:41:44 by mkong             #+#    #+#             */
/*   Updated: 2024/03/21 19:49:21 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_fork(t_philo *ph)
{
	sem_wait(ph->forks_sem);
	prt_bh("%d %d has taken a fork\n", get_time(ph->st_tv), ph->id, ph, 0);
	sem_wait(ph->forks_sem);
	prt_bh("%d %d has taken a fork\n", get_time(ph->st_tv), ph->id, ph, 0);
}

void	putdown_fork(t_philo *ph)
{
	sem_post(ph->forks_sem);
	sem_post(ph->forks_sem);
}

void	prt_bh(char *s, int time, int id, t_philo *ph, int die)
{
	sem_wait(ph->print_sem);
	if (sem_post(ph->die_sem) == 0)
	{
		sem_wait(ph->die_sem);
		printf(s, time, id);
		if (die)
			unlink("die_sem");
	}
	sem_post(ph->print_sem);
}
