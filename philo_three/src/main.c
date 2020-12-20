/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 18:12:12 by ebednar           #+#    #+#             */
/*   Updated: 2020/12/20 17:05:33 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	free_mem(t_philo *philos)
{
	free(philos);
}

static int	set_philos(t_env *env, t_philo *philos)
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
		sem_unlink("/alive");
		if (!(philos[i].philo_s = sem_open("/alive", O_CREAT, 0644, 1)))
		{
			ft_putendl("semaphore open fail");
			return (1);
		}
	}
	return (0);
}

static void	start_threads(t_env *env, t_philo *philos)
{
	pthread_t	*threads;
	pthread_t	observer;
	int			i;

	if (!(threads = (pthread_t *)malloc(env->philos_numb * sizeof(pthread_t))))
	{
		ft_putendl("mem allocation error");
		return ;
	}
	if (pthread_create(&observer, NULL, observer_eat_count, env) != 0)
	{
		ft_putendl("pthread creation error");
		return ;
	}
	pthread_detach(observer);
	fork_process(env, philos);
	sem_wait(env->running);
	i = -1;
	while (++i < env->philos_numb)
		kill(philos[i].pid, SIGKILL);
	free(threads);
}

static int	read_input(int argc, char **argv, t_env *env)
{
	if (argc != 5 && argc != 6)
	{
		ft_putendl("wrong number of args: number_of_philosophers, \
		time_to_die, time_to_eat, time_to_sleep,\
		[number_of_times_each_philosopher_must_eat]");
		return (1);
	}
	env->philos_numb = ft_atoi(argv[1]);
	if (env->philos_numb <= 0)
	{
		ft_putendl("incorrect number of philosophers");
		return (1);
	}
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		env->number_of_eat = ft_atoi(argv[5]);
	else
		env->number_of_eat = -1;
	return (0);
}

int			main(int argc, char **argv)
{
	t_env		env;
	t_philo		*philos;

	env.start_time = time_stamp();
	if (read_input(argc, argv, &env))
		return (-1);
	if (!(philos = (t_philo *)malloc(env.philos_numb * sizeof(t_philo))))
	{
		ft_putendl("mem allocation error");
		return (-1);
	}
	if (!set_philos(&env, philos))
		if (!semaphore_init(&env))
			start_threads(&env, philos);
	free_mem(philos);
	return (0);
}
