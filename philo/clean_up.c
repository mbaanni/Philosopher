/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:29:36 by mbaanni           #+#    #+#             */
/*   Updated: 2023/05/22 09:06:56 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	data_cleaner(t_data *data)
{
	pthread_mutex_destroy(data->m_dead);
	pthread_mutex_destroy(data->m_write);
	free(data->m_dead);
	free(data->m_write);
	free(data->t);
	free(data->mutex);
	free(data);
}

void	clean_up(t_data *data, t_philo *head)
{
	t_philo	*tmp;
	t_philo	*ptr;

	tmp = head;
	while (tmp)
	{
		pthread_join(*tmp->thread, 0);
		pthread_mutex_destroy(tmp->fork);
		ptr = tmp;
		tmp = tmp->next;
		free(ptr);
		if (tmp == head)
			break ;
	}
	data_cleaner(data);
}
