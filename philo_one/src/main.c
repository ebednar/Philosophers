/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 18:12:12 by ebednar           #+#    #+#             */
/*   Updated: 2020/11/23 20:56:10 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	set_philos(t_env *env, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < env->philos_numb)
	{
		philos[i].numb = i;
		philos[i].philos_numb = env->philos_numb;
		philos[i].time_to_die = env->time_to_die * 1000000;
		philos[i].time_to_eat = env->time_to_eat * 1000000;
		philos[i].time_to_sleep = env->time_to_sleep * 1000000;
		philos[i].number_of_eat = env->number_of_eat;
		philos[i].eating = 0;
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
		ft_putendl("mem allocation error");
			return (1);
	}
	i = -1;
	while (++i < env->philos_numb)
	{
		if (pthread_create(&threads[i], NULL, philo_cycle, &philos[i]) != 0)
		{
			ft_putendl("pthread creation error");
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
		ft_putendl("wrong number of args: number_of_philosophers, time_to_die, time_to_eat, time_to_sleep,[number_of_times_each_philosopher_must_eat]");
		return (0);
	}
	env.philos_numb = ft_atoi(argv[1]);
	env.time_to_die = ft_atoi(argv[2]);
	env.time_to_eat = ft_atoi(argv[3]);
	env.time_to_sleep = ft_atoi(argv[4]);
	env.running = 1;
	if (argc == 6)
		env.number_of_eat = ft_atoi(argv[5]);
	else
		env.number_of_eat = -1;
	if (!(philos = (t_philo *)malloc(env.philos_numb * sizeof(t_philo))))
	{
		ft_putendl("mem allocation error");
		return (1);
	}
	if (!(env.forks = (pthread_mutex_t *)malloc((env.philos_numb) * sizeof(pthread_mutex_t))))
	{
		ft_putendl("mem allocation error");
		return (1);
	}
	set_philos(&env, philos);
	pthread_mutex_init(&env.output, NULL);
	start_threads(&env, philos);
	int	i;
	i = -1;
	while (++i < env.philos_numb)
		pthread_mutex_destroy(&env.forks[i]);
	pthread_mutex_destroy(&env.output);
	free(philos);
	free(env.forks);
	return (0);
}
