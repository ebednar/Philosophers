/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 18:12:04 by ebednar           #+#    #+#             */
/*   Updated: 2020/12/20 14:26:43 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct		s_env
{
	int				start_time;
	int				philos_numb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_eat;
	int				running;
	int				philos_finished;
	pthread_mutex_t	*forks;
	pthread_mutex_t	output;
}					t_env;

typedef struct		s_philo
{
	t_env			*env;
	int				numb;
	int				philos_numb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_eat;
	int				time_left;
	int				eating;
	pthread_mutex_t	philo_m;
}					t_philo;

void				*philo_cycle(void *philo_ptr);
void				*obsever_cycle(void *philo_ptr);
int					time_stamp();
int					precise_time();
int					ft_atoi(const char *str);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				print_message(t_philo *philo, char *str);

#endif
