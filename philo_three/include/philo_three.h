/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 18:12:04 by ebednar           #+#    #+#             */
/*   Updated: 2020/12/20 17:05:49 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

typedef struct	s_env
{
	int		start_time;
	int		philos_numb;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_eat;
	sem_t	*running;
	sem_t	*philos_finished;
	sem_t	*forks;
	sem_t	*can_take;
	sem_t	*output;
}				t_env;

typedef struct	s_philo
{
	t_env	*env;
	int		numb;
	int		philos_numb;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_eat;
	int		time_left;
	int		eating;
	int		pid;
	sem_t	*philo_s;
}				t_philo;

void			*philo_cycle(void *philo_ptr);
void			*observer_cycle(void *philo_ptr);
void			*observer_eat_count(void *env_ptr);
void			fork_process(t_env *env, t_philo *philos);
int				time_stamp();
int				precise_time();
int				ft_atoi(const char *str);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			print_message(t_philo *philo, char *str);
int				semaphore_init(t_env *env);

#endif
