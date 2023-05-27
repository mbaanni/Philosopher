/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:06:26 by mbaanni           #+#    #+#             */
/*   Updated: 2023/05/27 19:21:33 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	purge_it(t_philo *head, t_data *data, int i)
{
	t_philo		*tmp;

	tmp = head;
	if (!data->dead)
		data->dead = 1;
	if (tmp->data->dead == 1)
	{
		while (data->n_of_t_philo_must_eat && data->eating < data->n_philo)
		{
			sem_post(tmp->eat);
			data->eating++;
		}
	}
	while (tmp)
	{
		if (tmp->fork_id != i)
			kill(tmp->fork_id, SIGTERM);
		tmp = tmp->next;
		if (tmp == head)
			break ;
	}
}

int	creat_process(t_philo *head, t_philo *tmp)
{
	t_philo	*philo;
	int		i;

	tmp = head;
	philo = head;
	i = 0;
	head->data->start = time_it();
	while (tmp)
	{
		tmp->t_eat = time_it();
		tmp->id = i + 1;
		i++;
		tmp->fork_id = fork();
		if (tmp->fork_id == 0)
			routine(tmp);
		if (tmp->fork_id == -1)
			return (1);
		else
		{
			tmp = tmp->next;
			if (tmp == head)
				break ;
		}
	}
	return (0);
}

t_philo	*creat_philo(t_data *data)
{
	t_philo		*head;
	t_philo		*tmp;
	pthread_t	tr;
	int			i;

	i = -1;
	head = creat_list(data);
	if (!head)
		return (0);
	if (head->data->n_of_t_philo_must_eat)
	{
		while (++i < data->n_philo)
			sem_wait(head->eat);
	}
	i = -1;
	if (creat_process(head, tmp))
		return (0);
	pthread_create(&tr, 0, kill_all, head);
	pthread_detach(tr);
	i = waitpid(-1, 0, 0);
	purge_it(head, data, i);
	return (head);
}
