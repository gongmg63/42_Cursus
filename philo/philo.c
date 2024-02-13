/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:33:02 by mkong             #+#    #+#             */
/*   Updated: 2024/02/13 18:32:54 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_info(t_info *info, int ac, char *av[])
{
	info->error = 0;
	info->philos = ft_atoi(av[1], info);
	info->die = ft_atoi(av[2], info);
	info->eat = ft_atoi(av[3], info);
	info->sleep = ft_atoi(av[4], info);
	info->fork = (int *)malloc(sizeof(int) * info->philos);
	info->st_tv = (t_time *)malloc(sizeof(t_time));
	if (info->fork == 0 || info->st_tv == 0)
		info->error = 1;
	memset(info->fork, 0, sizeof(int) * info->philos);
	if (ac == 6)
		info->eat_num = ft_atoi(av[5], info);
	else
		info->eat_num = -1;
}

static t_philo	*set_philo_info(t_info *info, int id, int *exist_die, int *l_i)
{
	t_philo	*ph;

	ph = (t_philo *)malloc(sizeof(t_philo));
	// ph->st_tv = info->st_tv;
	ph->st_tv = (t_time *)malloc(sizeof(t_time));
	if (ph == 0 || ph->st_tv == 0)
		info->error = 1;
	ph->fork = info->fork;
	ph->state = -1;
	ph->id = id;
	ph->die = info->die;
	ph->eat = info->eat;
	ph->sleep = info->sleep;
	ph->philos = info->philos;
	ph->eat_num = info->eat_num;
	ph->exist_die = exist_die;
	ph->last_in = l_i;
	return (ph);
}

static t_philo	**set_philos(t_info *info, int *exist_die, int *last_in)
{
	t_philo	**phs;
	int		i;

	phs = (t_philo **)malloc(sizeof(t_philo *) * info->philos);
	if (phs == 0)
		info->error = 1;
	i = -1;
	while (++i < info->philos)
	{
		phs[i] = set_philo_info(info, i, exist_die, last_in);
		phs[i]->phs = phs;
	}
	return (phs);
}

int	main(int ac, char *av[])
{
	t_info	*info;
	t_philo	**phs;
	int		*exist_die;
	int		*last_in;

	if (!(ac == 5 || ac == 6))
		return (1);
	info = (t_info *)malloc(sizeof(t_info));
	if (info == 0)
		return (1);
	set_info(info, ac, av);
	exist_die = (int *)malloc(sizeof(int));
	last_in = (int *)malloc(sizeof(int));
	if (exist_die == 0 || last_in == 0)
		info->error = 1;
	*exist_die = 0;
	*last_in = 0;
	phs = set_philos(info, exist_die, last_in);
	simulation(phs, info);
	return (0);
}
