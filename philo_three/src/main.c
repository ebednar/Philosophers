/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 18:12:12 by ebednar           #+#    #+#             */
/*   Updated: 2020/12/02 23:04:22 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	free_mem(t_env *env, t_philo *philos)
{
	int	i;

	i = -1;
	sem_close(env->forks);
	sem_close(env->output);
	sem_close(env->can_take);
	free(philos);
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
		philos[i].eating = 0;
		philos[i].env = env;
	}
}

static void	start_threads(t_env *env, t_philo *philos)
{
	pthread_t	*threads;
	pthread_t	observer;
	int			i;

	if (!(threads = (pthread_t*)malloc(env->philos_numb * sizeof(pthread_t))))
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
	i = -1;
	while (++i < env->philos_numb)
	{
		philos[i].pid = fork();
		if (!philos[i].pid)
		{
			philo_cycle(&philos[i]);
			exit(0);
		}
	}
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
		ft_putendl("wrong number of args: number_of_philosophers, time_to_die, time_to_eat, time_to_sleep,[number_of_times_each_philosopher_must_eat]");
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
	sem_unlink("/forks");
	if (!(env->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, env->philos_numb)))
	{
		ft_putendl("semaphore open fail");
		return (1);
	};
	sem_unlink("/running");
	if (!(env->running = sem_open("/running", O_CREAT | O_EXCL, 0644, 0)))
	{
		ft_putendl("semaphore open fail");
		return (1);
	};
	sem_unlink("/philos_finished");
	if (!(env->philos_finished = sem_open("/philos_finished", O_CREAT | O_EXCL, 0644, 0)))
	{
		ft_putendl("semaphore open fail");
		return (1);
	};
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
	set_philos(&env, philos);
	sem_unlink("/output");
	if (!(env.output = sem_open("/output", O_CREAT, 0644, 1)))
	{
		ft_putendl("semaphore open fail");
		return (1);
	};
	sem_unlink("/can_take");
	if (!(env.can_take = sem_open("/can_take", O_CREAT, 0644, 1)))
	{
		ft_putendl("semaphore open fail");
		return (1);
	};
	start_threads(&env, philos);
	free_mem(&env, philos);
	return (0);
}
