/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:50:02 by mbaanni           #+#    #+#             */
/*   Updated: 2023/05/27 20:03:45 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	taking_fork(t_philo	*philo)
{
	if (philo->data->dead)
	{
		pthread_mutex_unlock(philo->fork);
		return (1);
	}
	pthread_mutex_lock(philo->data->m_write);
	printf("%ld %d has taken a fork\n", time_it() - philo->data->start,
		philo->id);
	pthread_mutex_unlock(philo->data->m_write);
	if (philo->data->n_philo == 1)
	{
		ft_usleep(philo->data->t_to_die * 2, philo, 0);
		pthread_mutex_unlock(philo->fork);
		return (1);
	}
	if (philo->data->dead)
	{
		pthread_mutex_unlock(philo->fork);
		return (1);
	}
	return (0);
}

int	eating_philo(t_philo *philo)
{
	if (philo->data->dead)
	{
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(philo->next->fork);
		return (1);
	}
	pthread_mutex_lock(philo->data->m_write);
	printf("%ld %d is eating\n", time_it() - philo->data->start, philo->id);
	pthread_mutex_unlock(philo->data->m_write);
	philo->t_eat = time_it();
	ft_usleep(philo->data->t_to_eat, philo, 0);
	if (philo->n_t_eat < philo->data->n_of_t_philo_must_eat)
		philo->n_t_eat++;
	if (philo->data->dead)
	{
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(philo->next->fork);
		return (1);
	}
	return (0);
}

int	sleeping_philo(t_philo *philo)
{
	if (philo->data->dead)
		return (1);
	pthread_mutex_lock(philo->data->m_write);
	printf("%ld %d is sleeping\n", time_it() - philo->data->start, philo->id);
	pthread_mutex_unlock(philo->data->m_write);
	ft_usleep(philo->data->t_to_sleep, philo, 0);
	if (philo->data->dead)
		return (1);
	return (0);
}

int	thinking_philo(t_philo *philo, int i)
{
	if (philo->data->dead)
		return (1);
	if (philo->t == 1 && i == 0)
	{
		philo->t = 0;
		return (0);
	}
	pthread_mutex_lock(philo->data->m_write);
	printf("%ld %d is thinking\n", time_it() - philo->data->start, philo->id);
	pthread_mutex_unlock(philo->data->m_write);
	return (0);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2)
		ft_usleep(philo->data->t_to_eat - philo->id, philo, 1);
	while (1)
	{
		if (thinking_philo(philo, 0))
			return (0);
		pthread_mutex_lock(philo->fork);
		if (taking_fork(philo))
			return (0);
		pthread_mutex_lock(philo->next->fork);
		if (taking_fork(philo))
		{
			pthread_mutex_unlock(philo->next->fork);
			return (0);
		}
		if (eating_philo(philo))
			return (0);
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(philo->next->fork);
		if (sleeping_philo(philo))
			return (0);
	}
}
