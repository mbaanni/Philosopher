/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:47:41 by mbaanni           #+#    #+#             */
/*   Updated: 2023/05/22 09:05:24 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocate_mutex(t_data *data, int i)
{
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*m_dead;
	pthread_mutex_t	*m_write;

	i = -1;
	mutex = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!mutex)
		return (1);
	m_dead = malloc(sizeof(pthread_mutex_t));
	if (!m_dead)
		return (1);
	m_write = malloc(sizeof(pthread_mutex_t));
	if (!m_write)
		return (1);
	while (++i < data->n_philo)
	{
		if (pthread_mutex_init(mutex + i, 0))
			return (1);
	}
	data->m_dead = m_dead;
	data->m_write = m_write;
	data->mutex = mutex;
	return (0);
}

int	creat_mutex(t_philo *head, t_data *data)
{
	t_philo	*tmp;
	int		i;

	if (allocate_mutex(data, i))
		return (1);
	if (pthread_mutex_init(data->m_dead, 0))
		return (1);
	if (pthread_mutex_init(data->m_write, 0))
		return (1);
	tmp = head;
	i = 0;
	while (tmp)
	{
		tmp->fork = data->mutex + i;
		tmp->m_dead = data->m_dead;
		tmp->m_write = data->m_write;
		tmp = tmp->next;
		if (tmp == head)
			break ;
		i++;
	}
	return (0);
}
