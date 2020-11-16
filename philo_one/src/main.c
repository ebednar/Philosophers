#include "philosophers.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>

typedef struct s_env
{
	int	philos_numb;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int number_of_eat;
} t_env;

typedef struct s_philo
{
	int numb;
	int	philos_numb;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int number_of_eat;
} t_philo;

void	sleep(t_env *env)
{
	printf(" is sleeping\n");
	usleep(env->time_to_sleep);
}

void	think(t_env *env)
{
	printf(" is thinking\n");
}

void	eat(t_env *env)
{
	printf(" is eating\n");
	usleep(env->time_to_eat);
}

void *philo_cycle(void *philo_ptr)
{
	t_philo	*philo;
	philo = philo_ptr;
}

void	set_philos(t_env *env, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < env->philos_numb)
	{
		philos[i]->numb = i;
		philos[i]->philos_numb = env->philos_numb;
		philos[i]->time_to_die = env->time_to_die;
		philos[i]->time_to_eat = env->time_to_eat;
		philos[i]->time_to_sleep = env->time_to_sleep;
		philos[i]->number_of_eat = env->number_of_eat;
	}
}

int		start_threads(t_env *env, t_philo* philos)
{
	pthread_t*	threads;
	int			i;

	if (!(threads = (pthread_t*)malloc(env.philos_numb * sizeof(pthread_t))))
	{
		printf("mem allocation error\n")
			return (1);
	}
	i = -1;
	while (++i < env.philos_numb)
	{
		if (pthread_create(&threads[i], NULL, philo_cycle, &philos[i]) != 0)
		{
			printf("pthread creation error\n");
			return (1);
		}
	}
	i = -1;
	while (++i < env.philos_numb)
		pthread_join(&threads[i], NULL);
	free(threads);
}

int		main(int argc, char **argv)
{
	t_env		env;
	t_philo		*philos;

	if (argc != 5 || argc != 6)
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
		printf("mem allocation error\n")
		return (1);
	}
	set_philos(&env, philos);
	start_threads(&env, philos);
	free(philos);
	return (0);
}
