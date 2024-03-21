/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:18:53 by mkong             #+#    #+#             */
/*   Updated: 2024/03/21 20:08:21 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_time(t_time st_tv)
{
	t_time	p_tv;
	int		p_ms;

	gettimeofday(&p_tv, NULL);
	p_ms = p_tv.tv_sec * 1000 + p_tv.tv_usec / 1000;
	p_ms -= st_tv.tv_sec * 1000 + st_tv.tv_usec / 1000;
	return (p_ms);
}

void	child_philo(t_philo *ph)
{
	if (ph->id % 2 == 1)
		usleep(4000);
	while (1)
	{
		take_fork(ph);
		ph_eating(ph);
		ph_sleeping(ph);
		ph_thinking(ph);
	}
}

void	parent_process(pid_t *pid, t_philo *ph)
{
	int	status;
	int	i;
	int	die;

	die = 0;
	while (!die)
	{
		i = -1;
		while (++i < ph->philos)
		{
			waitpid(pid[i], &status, 0);
			if (status == 1)
			{
				i = -1;
				while (++i < ph->philos)
					kill(pid[i], SIGKILL);
				die = 1;
			}
		}
	}
}

void	free_philo(t_philo *ph)
{
	sem_unlink("forks_sem");
	sem_unlink("die_sem");
	sem_unlink("print_sem");
	free(ph);
}

void	simulation(t_philo *philo)
{
	pid_t	*pid;
	int		i;

	pid = (pid_t *)malloc(sizeof(pid) * philo->philos);
	if (pid == NULL)
		exit(1);
	i = -1;
	gettimeofday(&philo->st_tv, NULL);
	philo->last_eat = philo->st_tv;
	while (++i < philo->philos)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			philo->id = i;
			child_philo(philo);
		}
	}
	parent_process(pid, philo);
	free_philo(philo);
	free(pid);
}
