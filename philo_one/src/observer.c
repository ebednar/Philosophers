/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 14:05:27 by ebednar           #+#    #+#             */
/*   Updated: 2020/12/20 20:10:02 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	check_end(t_philo *philo)
{
	if (philo->time_left <= 0)
	{
		pthread_mutex_lock(&philo->philo_m);
		print_message(philo, " died");
		philo->env->running = 0;
	}
	if (philo->env->philos_finished == philo->env->philos_numb)
		philo->env->running = 0;
}

void		*obsever_cycle(void *philo_ptr)
{
	t_philo *philo;
	int		old_time;
	int		delta_time;
	int		current_time;

	philo = philo_ptr;
	old_time = precise_time();
	while (philo->env->running)
	{
		current_time = precise_time();
		delta_time = current_time - old_time;
		old_time = current_time;
		if (!philo->eating)
			philo->time_left -= delta_time;
		if (philo->number_of_eat == 0)
		{
			philo->env->philos_finished++;
			philo->number_of_eat--;
		}
		check_end(philo);
	}
	return (0);
}
