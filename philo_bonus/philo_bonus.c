/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:55:56 by mkong             #+#    #+#             */
/*   Updated: 2024/03/22 15:27:33 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_philo	*set_philo(int ac, char *av[])
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (philo == NULL)
		exit(1);
	philo->philos = ft_atoi(av[1]);
	philo->id = -1;
	philo->die = ft_atoi(av[2]);
	philo->eat = ft_atoi(av[3]);
	philo->sleep = ft_atoi(av[4]);
	sem_unlink("forks_sem");
	sem_unlink("die_sem");
	sem_unlink("print_sem");
	philo->forks_sem = sem_open("forks_sem", O_CREAT, 0644, philo->philos);
	philo->die_sem = sem_open("die_sem", O_CREAT, 0644, 1);
	philo->print_sem = sem_open("print_sem", O_CREAT, 0644, 1);
	if (ac == 6)
		philo->eat_num = ft_atoi(av[5]);
	else
		philo->eat_num = -1;
	return (philo);
}

int	main(int ac, char *av[])
{
	t_philo	*philo;

	if (!(ac == 5 || ac == 6))
		return (1);
	philo = set_philo(ac, av);
	simulation(philo);
	return (0);
}
