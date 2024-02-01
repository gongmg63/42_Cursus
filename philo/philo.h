/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:07:08 by mkong             #+#    #+#             */
/*   Updated: 2024/02/01 21:11:20 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct timeval	t_time;

typedef struct s_info
{
	t_time	*st_tv;
	int		philos;
	int		die;
	int		eat;
	int		sleep;
	int		eat_num;	
	int		error;
}	t_info;

typedef struct s_philo
{
	t_time	*p_t;
	int		id;
	int		die;
	int		eat;
	int		sleep;
	int		eat_num;
	int		*fork;
}	t_philo;

int	ft_atoi(const char *str, t_info *p);

#endif
