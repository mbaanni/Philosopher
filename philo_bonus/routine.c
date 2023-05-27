/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:50:02 by mbaanni           #+#    #+#             */
/*   Updated: 2023/05/27 20:03:58 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	taking_fork(t_philo	*philo)
{
	if (philo->data->dead)
		return (1);
	sem_wait(philo->write);
	printf("%ld %d has taken a fork\n", time_it() - philo->data->start,
		philo->id);
	sem_post(philo->write);
	if (philo->data->dead)
		return (1);
	return (0);
}

int	eating_philo(t_philo *philo)
{
	if (philo->data->dead)
		return (1);
	sem_wait(philo->write);
	printf("%ld %d is eating\n", time_it() - philo->data->start, philo->id);
	sem_post(philo->write);
	philo->t_eat = time_it();
	ft_usleep(philo->data->t_to_eat, philo);
	philo->n_t_eat += 1;
	if (philo->data->dead)
		return (1);
	return (0);
}

int	sleeping_philo(t_philo *philo)
{
	if (philo->data->dead)
		return (1);
	sem_wait(philo->write);
	printf("%ld %d is sleeping\n", time_it() - philo->data->start, philo->id);
	sem_post(philo->write);
	ft_usleep(philo->data->t_to_sleep, philo);
	if (philo->data->dead)
		return (1);
	return (0);
}

int	thinking_philo(t_philo *philo)
{
	if (philo->data->dead)
		return (1);
	sem_wait(philo->write);
	printf("%ld %d is thinking\n", time_it() - philo->data->start, philo->id);
	sem_post(philo->write);
	if (philo->data->dead)
		return (1);
	return (0);
}

void	routine(t_philo	*philo)
{
	pthread_t	thread;

	pthread_create(&thread, 0, monitor, philo);
	pthread_detach(thread);
	while (1)
	{
		if (thinking_philo(philo))
			break ;
		sem_wait(philo->fork);
		if (taking_fork(philo))
			break ;
		sem_wait(philo->fork);
		if (taking_fork(philo))
			break ;
		if (eating_philo(philo))
			break ;
		sem_post(philo->fork);
		sem_post(philo->fork);
		if (sleeping_philo(philo))
			break ;
	}
	exit (0);
}
