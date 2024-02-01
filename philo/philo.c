/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:33:02 by mkong             #+#    #+#             */
/*   Updated: 2024/02/01 21:10:54 by mkong            ###   ########.fr       */
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
	info->st_tv = (t_time *)malloc(sizeof(t_time));
	if (ac == 6)
		info->eat_num = ft_atoi(av[5], info);
	else
		info->eat_num = -1;
}

static t_philo	**set_philo(t_info *info)
{
	t_philo	**p;
	int		i;
	int		*fork;

	p = (t_philo *)malloc(sizeof(t_philo) * info->philos);
	i = -1;
	fork = (int *)malloc(sizeof(int) * info->philos);
	memset(fork, 0, sizeof(int) * info->philos);
	while (++i < info->philos)
	{
		p[i]->p_t = (t_time *)malloc(sizeof(t_time));
		p[i]->id = i;
		p[i]->die = info->die;
		p[i]->eat = info->eat;
		p[i]->sleep = info->sleep;
		p[i]->eat_num = info->eat_num;
		p[i]->fork = fork;
	}
	return (p);
}

int	main(int ac, char *av[])
{
	t_info	*info;
	t_philo	**philo;
	int		i;

	if (!(ac == 5 || ac == 6))
		return (1);
	info = (t_info *)malloc(sizeof(t_info));
	set_info(info, ac, av);
	philo = set_philo(info);
}
