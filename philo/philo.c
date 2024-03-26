/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:10:17 by mkong             #+#    #+#             */
/*   Updated: 2024/03/21 16:36:40 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_mutex(t_info *info)
{
	int	i;

	i = -1;
	if (info->error != 1 && info->philos != 0)
		info->fork = (int *)malloc(sizeof(int) * info->philos);
	if (info->error == 1 || info->philos == 0 || info->fork == NULL)
	{
		free(info);
		return (1);
	}
	memset(info->fork, 0, sizeof(int) * info->philos);
	info->fork_mutex = malloc(sizeof(pthread_mutex_t) * info->philos);
	if (info->fork_mutex == NULL)
	{
		info->error = 1;
		free_info(info);
		return (1);
	}
	pthread_mutex_init(&info->die_mutex, NULL);
	pthread_mutex_init(&info->print_mutex, NULL);
	while (++i < info->philos)
		pthread_mutex_init(&info->fork_mutex[i], NULL);
	return (0);
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
	if (set_mutex(info))
		return (NULL);
	info->st_tv = (t_time *)malloc(sizeof(t_time));
	if (info->st_tv == NULL)
	{
		free_info(info);
		return (NULL);
	}
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
	if (phs == NULL)
		return (NULL);
	i = -1;
	while (++i < info->philos)
	{
		phs[i] = set_philo_info(info, i, exist_die);
		if (phs[i] == NULL)
		{
			while (--i >= 0)
				free(phs[i]);
			free(phs);
			free_info(info);
			return (NULL);
		}
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
	if (info == NULL)
		return (1);
	exist_die = (int *)malloc(sizeof(int));
	if (exist_die == NULL)
	{
		free_info(info);
		return (1);
	}
	*exist_die = 0;
	phs = set_philos(info, exist_die);
	if (phs == NULL)
		return (1);
	return (simulation(phs, info));
}
