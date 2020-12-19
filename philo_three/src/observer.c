/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 22:47:10 by ebednar           #+#    #+#             */
/*   Updated: 2020/12/19 21:50:08 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*observer_eat_count(void *env_ptr)
{
	t_env	*env;
	int		i;

	env = env_ptr;
	i = 0;
	while (1)
	{
		sem_wait(env->philos_finished);
		i++;
		if (i == env->philos_numb)
		{
			sem_post(env->running);
			return (0);
		}
	}
	return (0);
}

void	*observer_cycle(void *philo_ptr)
{
	t_philo *philo;
	int		old_time;
	int		delta_time;
	int		current_time;

	philo = philo_ptr;
	old_time = precise_time();
	while (1)
	{
		current_time = precise_time();
		delta_time = current_time - old_time;
		old_time = current_time;
		if (!philo->eating)
			philo->time_left -= delta_time;
		if (philo->time_left <= 0)
		{
			sem_wait(philo->philo_s);
			print_message(philo, " died");
			sem_post(philo->env->running);
			return (0);
		}
		if (philo->number_of_eat == 0)
		{
			sem_wait(philo->philo_s);
			sem_post(philo->env->philos_finished);
			philo->number_of_eat--;
		}
	}
	return (0);
}
