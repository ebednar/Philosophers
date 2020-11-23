/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 20:08:30 by ebednar           #+#    #+#             */
/*   Updated: 2020/11/23 22:04:43 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	philo_sleep(t_philo *philo)
{
	print_message(philo, " is sleeping");
	usleep(philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_message(philo, " is thinking");
}

void	philo_eat(t_philo *philo)
{
	if (philo->numb == 0)
		pthread_mutex_lock(&(philo->env->forks[philo->philos_numb - 1]));
	else
		pthread_mutex_lock(&(philo->env->forks[philo->numb - 1]));
	pthread_mutex_lock(&(philo->env->forks[philo->numb]));
	philo->eating = 1;
	print_message(philo, " has taken a fork");
	print_message(philo, " is eating");
	usleep(philo->time_to_eat);
	philo->eating = 0;
	if (philo->numb == 0)
		pthread_mutex_unlock(&(philo->env->forks[philo->philos_numb - 1]));
	else
		pthread_mutex_unlock(&(philo->env->forks[philo->numb - 1]));
	pthread_mutex_unlock(&(philo->env->forks[philo->numb]));
}

void    *obsever_cycle(void *philo_ptr)
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
			philo->time_to_die -= delta_time;
		if (philo->time_to_die == 0)
		{
			print_message(philo, " died");
			philo->env->running = 0;
		}
	}
	return (0);
}

void	*philo_cycle(void *philo_ptr)
{
	pthread_t	obs;
	t_philo     *philo;

	philo = philo_ptr;
	if (pthread_create(&obs, NULL, obsever_cycle, philo) != 0)
	{
		ft_putendl("pthread creation error");
		return (0);
	}
	pthread_detach(obs);
	while (philo->env->running)
	{
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (0);
}
