/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:23:05 by mkong             #+#    #+#             */
/*   Updated: 2024/03/21 18:25:01 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*st_simul(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	ph->last_eat = *ph->st_tv;
	if (ph->id % 2 == 1)
		usleep(4000);
	while (ph->eat_num && !check_die(ph))
	{
		if (ph->eat_num)
			take_fork(ph);
		if (ph->eat_num)
			ph_eating(ph);
		if (!check_die(ph))
			putdown_fork(ph);
		if (ph->eat_num && !check_die(ph))
			ph_sleeping(ph);
		if (ph->eat_num)
			ph_thinking(ph);
	}
	return ((void *)ph);
}

void	free_info(t_info *info)
{
	int	i;

	i = -1;
	free(info->fork);
	free(info->st_tv);
	if (info->error != 1)
	{
		pthread_mutex_destroy(&info->die_mutex);
		pthread_mutex_destroy(&info->print_mutex);
		while (++i < info->philos)
			pthread_mutex_destroy(&(info->fork_mutex)[i]);
	}
	free(info->fork_mutex);
	free(info);
}

void	free_phs(t_philo **phs)
{
	int	i;
	int	philos;

	i = 0;
	philos = phs[i]->philos;
	free(phs[i]->exist_die);
	while (i < philos)
		free(phs[i++]);
	free(phs);
}

int	simulation(t_philo **phs, t_info *info)
{
	pthread_t		*tid;
	int				i;

	i = -1;
	tid = (pthread_t *)malloc(sizeof(pthread_t) * info->philos);
	if (tid == NULL)
	{
		free_info(info);
		free_phs(phs);
		return (1);
	}
	gettimeofday(info->st_tv, NULL);
	while (++i < info->philos)
		pthread_create(&tid[i], NULL, st_simul, phs[i]);
	while (--i >= 0)
		pthread_join(tid[i], NULL);
	free(tid);
	free_info(info);
	free_phs(phs);
	return (0);
}
