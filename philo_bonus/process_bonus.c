/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:18:53 by mkong             #+#    #+#             */
/*   Updated: 2024/03/22 15:22:26 by mkong            ###   ########.fr       */
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
	while (1)
	{
		take_fork(ph);
		ph_eating(ph);
		ph_sleeping(ph);
		ph_thinking(ph);
	}
}

int	count_finish(int *cnt_finish, int size)
{
	int	i;
	int	cnt;

	i = -1;
	cnt = 0;
	while (++i < size)
		cnt += cnt_finish[i];
	return (cnt);
}

void	parent_process(pid_t *pid, int *cnt_finish, t_philo *ph)
{
	int	status;
	int	i;
	int	finish;

	finish = 0;
	while (!finish)
	{
		i = -1;
		while (++i < ph->philos)
		{
			if (waitpid(pid[i], &status, WNOHANG) == -1)
				cnt_finish[i] = 1;
			if (WEXITSTATUS(status) == 1)
			{
				i = -1;
				while (++i < ph->philos)
					kill(pid[i], SIGKILL);
				finish = 1;
			}
			if (count_finish(cnt_finish, ph->philos) == ph->philos)
				finish = 1;
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
	int		*cnt_finish;
	int		i;

	pid = (pid_t *)malloc(sizeof(pid) * philo->philos);
	cnt_finish = (int *)malloc(sizeof(int) * philo->philos);
	if (pid == NULL || cnt_finish == NULL)
		exit(1);
	i = -1;
	memset(cnt_finish, 0, sizeof(int) * philo->philos);
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
	parent_process(pid, cnt_finish, philo);
	free_philo(philo);
	free(pid);
	free(cnt_finish);
}
