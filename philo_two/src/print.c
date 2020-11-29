/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:58:55 by ebednar           #+#    #+#             */
/*   Updated: 2020/11/23 20:48:36 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	print_message(t_philo *philo, char *str)
{
	if (!philo->env->running)
		return ;
	sem_wait(philo->env->output);
	ft_putnbr(time_stamp() - philo->env->start_time);
	ft_putchar(' ');
	ft_putnbr(philo->numb + 1);
	ft_putendl(str);
	sem_post(philo->env->output);
}
