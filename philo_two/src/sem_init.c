/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 22:57:58 by ebednar           #+#    #+#             */
/*   Updated: 2020/12/20 14:42:48 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int			semaphore_init(t_env *env)
{
	sem_unlink("/forks");
	if (!(env->forks = sem_open("/forks", O_CREAT | O_EXCL,
	0644, env->philos_numb)))
	{
		ft_putendl("semaphore open fail");
		return (1);
	}
	sem_unlink("/output");
	if (!(env->output = sem_open("/output", O_CREAT, 0644, 1)))
	{
		ft_putendl("semaphore open fail");
		return (1);
	}
	sem_unlink("/can_take");
	if (!(env->can_take = sem_open("/can_take", O_CREAT, 0644, 1)))
	{
		ft_putendl("semaphore open fail");
		return (1);
	}
	return (0);
}
