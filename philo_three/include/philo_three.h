/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 18:12:04 by ebednar           #+#    #+#             */
/*   Updated: 2020/12/02 23:03:12 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_env
{
	int				start_time;
	int				philos_numb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_eat;
	sem_t			*running;
	sem_t			*philos_finished;
	sem_t			*forks;
	sem_t			*can_take;
	sem_t			*output;
}			t_env;

typedef struct s_philo
{
	t_env	*env;
	int		numb;
	int		philos_numb;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_eat;
	int		eating;
	int		pid;
}			t_philo;

void	*philo_cycle(void *philo_ptr);
void    *observer_cycle(void *philo_ptr);
void	*observer_eat_count(void *env_ptr);
int		time_stamp();
int		precise_time();
int		ft_atoi(const char *str);
void	ft_putchar(char c);
void	ft_putstr(char const *s);
void	ft_putendl(char const *s);
void	ft_putnbr(int n);
void	print_message(t_philo *philo, char *str);

#endif
