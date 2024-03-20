/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:10:17 by mkong             #+#    #+#             */
/*   Updated: 2024/03/20 21:07:16 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_mutex(t_info *info)
{
	int	i;

	i = -1;
	info->fork_mutex = (pthread_mutex_t *) \
	malloc(sizeof(pthread_mutex_t) * info->philos);
	if (info->fork_mutex == NULL)
	{
		info->error = 1;
		return ;
	}
	pthread_mutex_init(&info->die_mutex, NULL);
	pthread_mutex_init(&info->print_mutex, NULL);
	while (++i < info->philos)
		pthread_mutex_init(&info->fork_mutex[i], NULL);
}

static t_info	*set_info(int ac, char *av[])
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (info == NULL)
		return (NULL);
	info->error = 0;
	info->philos = ft_atoi(av[1], info);
	info->die = ft_atoi(av[2], info);
	info->eat = ft_atoi(av[3], info);
	info->sleep = ft_atoi(av[4], info);
	info->fork = (int *)malloc(sizeof(int) * info->philos);
	info->st_tv = (t_time *)malloc(sizeof(t_time));
	if (info->fork == 0 || info->st_tv == 0)
	{
		info->error = 1;
		return ;
	}
	memset(info->fork, 0, sizeof(int) * info->philos);
	set_mutex(info);
	if (ac == 6)
		info->eat_num = ft_atoi(av[5], info);
	else
		info->eat_num = -1;
	return (info);
}

static t_philo	*set_philo_info(t_info *info, int id, int *exist_die)
{
	t_philo	*ph;

	ph = (t_philo *)malloc(sizeof(t_philo));
	if (ph == NULL)
		return (NULL);
	ph->st_tv = info->st_tv;
	ph->fork = info->fork;
	ph->state = start;
	ph->id = id;
	ph->die = info->die;
	ph->eat = info->eat;
	ph->sleep = info->sleep;
	ph->philos = info->philos;
	ph->eat_num = info->eat_num;
	ph->exist_die = exist_die;
	ph->fork_mutex = &info->fork_mutex;
	ph->die_mutex = &info->die_mutex;
	ph->print_mutex = &info->print_mutex;
	return (ph);
}

static t_philo	**set_philos(t_info *info, int *exist_die)
{
	t_philo	**phs;
	int		i;

	phs = (t_philo **)malloc(sizeof(t_philo *) * info->philos);
	if (phs == 0)
		return (NULL);
	i = -1;
	while (++i < info->philos)
	{
		phs[i] = set_philo_info(info, i, exist_die);
		if (phs[i] == NULL)
			return (NULL);
		phs[i]->phs = phs;
	}
	return (phs);
}

int	main(int ac, char *av[])
{
	t_info	*info;
	t_philo	**phs;
	int		*exist_die;

	if (!(ac == 5 || ac == 6))
		return (1);
	info = set_info(ac, av);
	if (info->error == 1)
		return (1);
	exist_die = (int *)malloc(sizeof(int));
	if (exist_die == NULL)
		return (1);
	*exist_die = 0;
	phs = set_philos(info, exist_die);
	if (phs == NULL)
		return (1);
	return (simulation(phs, info));
}
