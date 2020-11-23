/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 18:12:12 by ebednar           #+#    #+#             */
/*   Updated: 2020/11/22 20:08:44 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	philo_sleep(t_philo *philo)
{
	print_message(philo, " is sleeping");
	usleep(philo->time_to_sleep * 1000000);
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
	print_message(philo, " has taken a fork");
	print_message(philo, " is eating");
	usleep(philo->time_to_eat * 1000000);
	if (philo->numb == 0)
		pthread_mutex_unlock(&(philo->env->forks[philo->philos_numb - 1]));
	else
		pthread_mutex_unlock(&(philo->env->forks[philo->numb - 1]));
	pthread_mutex_unlock(&(philo->env->forks[philo->numb]));
}

void	*philo_cycle(void *philo_ptr)
{
	t_philo	*philo;
	philo = philo_ptr;
	philo_eat(philo);
	philo_sleep(philo);
	philo_think(philo);
	return (0);
}

void	set_philos(t_env *env, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < env->philos_numb)
	{
		philos[i].numb = i;
		philos[i].philos_numb = env->philos_numb;
		philos[i].time_to_die = env->time_to_die;
		philos[i].time_to_eat = env->time_to_eat;
		philos[i].time_to_sleep = env->time_to_sleep;
		philos[i].number_of_eat = env->number_of_eat;
		philos[i].env = env;
		pthread_mutex_init(&env->forks[i], NULL);
	}
}

int		start_threads(t_env *env, t_philo* philos)
{
	pthread_t	*threads;
	int			i;

	if (!(threads = (pthread_t*)malloc(env->philos_numb * sizeof(pthread_t))))
	{
		printf("mem allocation error\n");
			return (1);
	}
	i = -1;
	while (++i < env->philos_numb)
	{
		if (pthread_create(&threads[i], NULL, philo_cycle, &philos[i]) != 0)
		{
			printf("pthread creation error\n");
			return (1);
		}
	}
	i = -1;
	while (++i < env->philos_numb)
		pthread_join(threads[i], NULL);
	free(threads);
	return (0);
}

int		main(int argc, char **argv)
{
	t_env		env;
	t_philo		*philos;

	env.start_time = time_stamp();
	if (argc != 5 && argc != 6)
	{
		printf("wrong number of args: number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	env.philos_numb = ft_atoi(argv[1]);
	env.time_to_die = ft_atoi(argv[2]);
	env.time_to_eat = ft_atoi(argv[3]);
	env.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		env.number_of_eat = ft_atoi(argv[5]);
	else
		env.number_of_eat = -1;
	if (!(philos = (t_philo *)malloc(env.philos_numb * sizeof(t_philo))))
	{
		printf("mem allocation error\n");
		return (1);
	}
	if (!(env.forks = (pthread_mutex_t *)malloc((env.philos_numb) * sizeof(pthread_mutex_t))))
	{
		printf("mem allocation error\n");
		return (1);
	}
	set_philos(&env, philos);
	pthread_mutex_init(&env.output, NULL);
	start_threads(&env, philos);
	free(philos);
	int	i;
	i = -1;
	while (++i < env.philos_numb)
		pthread_mutex_destroy(&env.forks[i]);
	return (0);
}
