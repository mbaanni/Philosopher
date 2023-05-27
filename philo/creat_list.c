/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:06:07 by mbaanni           #+#    #+#             */
/*   Updated: 2023/05/21 20:15:39 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*first_node(pthread_t *t)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (0);
	memset(philo, 0, sizeof(t_philo));
	philo->thread = t;
	philo->n_t_eat = 0;
	philo->next = philo;
	philo->prev = 0;
	return (philo);
}

t_philo	*add_node(pthread_t *t, t_philo *tail)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (0);
	memset(philo, 0, sizeof(t_philo));
	philo->next = tail->next;
	philo->prev = tail;
	tail->next = philo;
	philo->n_t_eat = 0;
	philo->thread = t;
	return (philo);
}

t_philo	*creat_list(t_data *data)
{
	pthread_t		*t;
	t_philo			*tail;
	t_philo			*head;
	int				i;

	i = 0;
	t = malloc(sizeof(pthread_t) * data->n_philo);
	if (!t)
		return (0);
	memset(t, 0, sizeof(pthread_t) * data->n_philo);
	head = first_node(t);
	if (!head)
		return (0);
	head->data = data;
	tail = head;
	while (++i < data->n_philo)
	{
		tail = add_node(t + i, tail);
		if (!tail)
			return (0);
		tail->data = data;
	}
	data->t = t;
	tail->next->prev = tail;
	return (head);
}
