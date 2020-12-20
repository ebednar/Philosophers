/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 18:12:12 by ebednar           #+#    #+#             */
/*   Updated: 2020/12/20 14:06:46 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	free_mem(t_env *env, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < env->philos_numb)
		pthread_mutex_destroy(&env->forks[i]);
	pthread_mutex_destroy(&env->output);
	free(philos);
	free(env->forks);
}

static void	set_philos(t_env *env, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < env->philos_numb)
	{
		philos[i].numb = i;
		philos[i].philos_numb = env->philos_numb;
		philos[i].time_to_die = env->time_to_die * 1000;
		philos[i].time_to_eat = env->time_to_eat * 1000;
		philos[i].time_to_sleep = env->time_to_sleep * 1000;
		philos[i].number_of_eat = env->number_of_eat;
		philos[i].time_left = philos[i].time_to_die;
		philos[i].eating = 0;
		philos[i].env = env;
		pthread_mutex_init(&env->forks[i], NULL);
	}
}

static void	start_threads(t_env *env, t_philo *philos)
{
	pthread_t	*threads;
	int			i;

	if (!(threads = (pthread_t*)malloc(env->philos_numb * sizeof(pthread_t))))
	{
		ft_putendl("mem allocation error");
		return ;
	}
	i = -1;
	while (++i < env->philos_numb)
	{
		if (pthread_create(&threads[i], NULL, philo_cycle, &philos[i]) != 0)
		{
			ft_putendl("pthread creation error");
			free(threads);
			return ;
		}
		pthread_detach(threads[i]);
	}
	i = -1;
	while (env->running)
		;
	free(threads);
}

static void	read_input(int argc, char **argv, t_env *env)
{
	if (argc != 5 && argc != 6)
	{
		ft_putendl("wrong number of args: number_of_philosophers,\
		time_to_die, time_to_eat, time_to_sleep, \
		[number_of_times_each_philosopher_must_eat]");
		return ;
	}
	env->philos_numb = ft_atoi(argv[1]);
	if (env->philos_numb <= 0)
	{
		ft_putendl("incorrect number of philosophers");
		return ;
	}
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	env->running = 1;
	env->philos_finished = 0;
	if (argc == 6)
		env->number_of_eat = ft_atoi(argv[5]);
	else
		env->number_of_eat = -1;
}

int			main(int argc, char **argv)
{
	t_env		env;
	t_philo		*philos;

	env.start_time = time_stamp();
	read_input(argc, argv, &env);
	if (!(philos = (t_philo *)malloc(env.philos_numb * sizeof(t_philo))))
	{
		ft_putendl("mem allocation error");
		return (-1);
	}
	if (!(env.forks = (pthread_mutex_t *)malloc((env.philos_numb) *
	sizeof(pthread_mutex_t))))
	{
		ft_putendl("mem allocation error");
		free(philos);
		return (-1);
	}
	set_philos(&env, philos);
	pthread_mutex_init(&env.output, NULL);
	start_threads(&env, philos);
	free_mem(&env, philos);
	return (0);
}
