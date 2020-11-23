/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:58:55 by ebednar           #+#    #+#             */
/*   Updated: 2020/11/22 20:03:56 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	time_stamp()
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&(philo->env->output));
	ft_putnbr(time_stamp() - philo->env->start_time);
	ft_putchar(' ');
	ft_putnbr(philo->numb + 1);
	ft_putendl(str);
	pthread_mutex_unlock(&(philo->env->output));
}