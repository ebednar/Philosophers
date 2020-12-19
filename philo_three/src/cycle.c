/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 20:08:30 by ebednar           #+#    #+#             */
/*   Updated: 2020/12/19 21:47:11 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
	sem_wait(philo->env->can_take);
	sem_wait(philo->env->forks);
	print_message(philo, " has taken a fork");
	sem_wait(philo->env->forks);
	print_message(philo, " has taken a fork");
	sem_post(philo->env->can_take);
}

static void	philo_eat(t_philo *philo)
{
	philo_take_fork(philo);
	sem_wait(philo->philo_s);
	philo->eating = 1;
	print_message(philo, " is eating");
	philo->time_left = philo->time_to_die;
	sem_post(philo->philo_s);
	usleep(philo->time_to_eat);
	philo->eating = 0;
	philo->number_of_eat--;
	sem_post(philo->env->forks);
	sem_post(philo->env->forks);
}

void		*philo_cycle(void *philo_ptr)
{
	pthread_t	obs;
	t_philo     *philo;

	philo = philo_ptr;
	if (pthread_create(&obs, NULL, observer_cycle, philo) != 0)
	{
		ft_putendl("pthread creation error");
		return (0);
	}
	pthread_detach(obs);
	while (1)
	{
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (0);
}
