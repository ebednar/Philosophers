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

static void	philo_sleep(t_philo *philo)
{
	print_message(philo, " is sleeping");
	usleep(philo->time_to_sleep);
}

static void	philo_think(t_philo *philo)
{
	print_message(philo, " is thinking");
}

static void	philo_take_fork(t_philo *philo)
{
	if (philo->numb == 0)
	{
		pthread_mutex_lock(&(philo->env->forks[philo->numb]));
		print_message(philo, " has taken a fork");
		pthread_mutex_lock(&(philo->env->forks[philo->philos_numb - 1]));
		print_message(philo, " has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&(philo->env->forks[philo->numb - 1]));
		print_message(philo, " has taken a fork");
		pthread_mutex_lock(&(philo->env->forks[philo->numb]));
		print_message(philo, " has taken a fork");
	}
}

static void	philo_eat(t_philo *philo)
{
	philo_take_fork(philo);
	pthread_mutex_lock(&philo->philo_m);
	philo->eating = 1;
	print_message(philo, " is eating");
	philo->time_left = philo->time_to_die;
	pthread_mutex_unlock(&philo->philo_m);
	usleep(philo->time_to_eat);
	philo->eating = 0;
	philo->number_of_eat--;
	if (philo->numb == 0)
	{
		pthread_mutex_unlock(&(philo->env->forks[philo->philos_numb - 1]));
		pthread_mutex_unlock(&(philo->env->forks[philo->numb]));
	}
	else
	{
		pthread_mutex_unlock(&(philo->env->forks[philo->numb]));
		pthread_mutex_unlock(&(philo->env->forks[philo->numb - 1]));
	}
}

void		*philo_cycle(void *philo_ptr)
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
