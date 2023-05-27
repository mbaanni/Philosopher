/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:46:51 by mbaanni           #+#    #+#             */
/*   Updated: 2023/05/25 09:30:32 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_fulls(int t, t_data *data)
{
	if (t == data->n_philo)
	{
		data->dead = 1;
		pthread_mutex_unlock(data->m_dead);
		pthread_mutex_unlock(data->m_write);
		return (1);
	}
	return (0);
}

int	ate_full(t_philo *head, t_data *data, t_philo *ptr)
{
	int		t;

	ptr = head;
	t = 0;
	if (data->n_of_t_philo_must_eat)
	{
		pthread_mutex_lock(data->m_dead);
		pthread_mutex_lock(data->m_write);
		ptr = head;
		while (ptr)
		{
			if (ptr->n_t_eat == data->n_of_t_philo_must_eat)
				t++;
			if (check_fulls(t, data))
				return (1);
			ptr = ptr->next;
			if (ptr == head)
				break ;
		}
		pthread_mutex_unlock(data->m_write);
		pthread_mutex_unlock(data->m_dead);
	}
	return (0);
}

void	monitoring(t_philo	*head, t_data *data)
{
	t_philo	*tmp;
	t_philo	*ptr;

	tmp = head;
	while (tmp)
	{
		pthread_mutex_lock(data->m_dead);
		if (time_it() - tmp->t_eat >= data->t_to_die)
		{
			data->dead = 1;
			pthread_mutex_lock(data->m_write);
			printf("%ld %d died\n", time_it() - data->start, tmp->id);
			pthread_mutex_unlock(data->m_write);
			pthread_mutex_unlock(data->m_dead);
			break ;
		}
		pthread_mutex_unlock(data->m_dead);
		if (ate_full(head, data, ptr))
			break ;
		tmp = tmp->next;
	}
}
