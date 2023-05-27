/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 09:41:12 by mbaanni           #+#    #+#             */
/*   Updated: 2023/05/27 19:31:03 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	count_time_ate(t_philo *philo)
{
	if (philo->n_t_eat == philo->data->n_of_t_philo_must_eat)
	{
		sem_wait(philo->check);
		philo->n_t_eat++;
		philo->data->eating++;
		sem_post(philo->eat);
		sem_post(philo->check);
	}
}

void	*monitor(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		sem_wait(philo->check);
		if (time_it() - philo->t_eat >= philo->data->t_to_die)
		{
			philo->data->dead = 1;
			sem_wait(philo->write);
			printf("%ld %d died\n", time_it() - philo->data->start, philo->id);
			if (philo->data->n_philo == 1)
				sem_post(philo->fork);
			sem_post(philo->check);
			return (0);
		}
		sem_post(philo->check);
		if (philo->data->n_of_t_philo_must_eat)
			count_time_ate(philo);
	}
	return (0);
}

void	*kill_all(void *ptr)
{
	t_philo	*philo;
	t_philo	*tmp;
	int		i;

	philo = (t_philo *) ptr;
	i = -1;
	tmp = philo;
	if (!philo->data->n_of_t_philo_must_eat)
		return (0);
	if (philo->data->n_philo == 1)
		return (0);
	while (++i < philo->data->n_philo)
	{
		if (philo->data->dead)
			return (0);
		sem_wait(philo->eat);
		philo->data->eating++;
	}
	philo->data->dead = 2;
	kill(tmp->fork_id, SIGTERM);
	return (0);
}
