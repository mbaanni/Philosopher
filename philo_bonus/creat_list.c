/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:06:07 by mbaanni           #+#    #+#             */
/*   Updated: 2023/05/25 11:14:05 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*first_node(sem_t **sema, t_data *data)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	memset(philo, 0, sizeof(t_philo));
	philo->n_t_eat = 0;
	philo->next = philo;
	philo->prev = 0;
	philo->fork = sema[s_fork];
	philo->write = sema[s_write];
	philo->dead = sema[s_dead];
	philo->eat = sema[s_eat];
	philo->check = sema[s_check];
	philo->data = data;
	return (philo);
}

t_philo	*add_node(sem_t **sema, t_philo *tail, t_data *data)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	memset(philo, 0, sizeof(t_philo));
	philo->next = tail->next;
	philo->prev = tail;
	tail->next = philo;
	philo->n_t_eat = 0;
	philo->fork = sema[s_fork];
	philo->write = sema[s_write];
	philo->dead = sema[s_dead];
	philo->eat = sema[s_eat];
	philo->check = sema[s_check];
	philo->data = data;
	return (philo);
}

int	ft_sem_unlink(t_data *data)
{
	sem_t	**s_sema;

	sem_unlink("s__fork");
	sem_unlink("s__eat");
	sem_unlink("s__dead");
	sem_unlink("s__write");
	sem_unlink("s__check");
	s_sema = malloc(sizeof(sem_t *) * 6);
	if (!s_sema)
		return (1);
	s_sema[s_fork] = sem_open("s__fork", O_CREAT | O_EXCL, 0644, data->n_philo);
	s_sema[s_eat] = sem_open("s__eat", O_CREAT | O_EXCL, 0644, data->n_philo);
	s_sema[s_dead] = sem_open("s__dead", O_CREAT | O_EXCL, 0644, 1);
	s_sema[s_write] = sem_open("s__write", O_CREAT | O_EXCL, 0644, 1);
	s_sema[s_check] = sem_open("s__check", O_CREAT | O_EXCL, 0644, 1);
	data->s_sema = s_sema;
	return (0);
}

t_philo	*allocate_list(t_data *data)
{
	t_philo	*head;
	t_philo	*tail;
	int		i;

	i = 0;
	head = first_node(data->s_sema, data);
	if (!head)
		return (0);
	tail = head;
	while (++i < data->n_philo)
	{
		tail = add_node(data->s_sema, tail, data);
		if (!tail)
			return (0);
	}
	tail->next->prev = tail;
	return (head);
}

t_philo	*creat_list(t_data *data)
{
	t_philo	*head;
	int		i;
	int		j;

	j = -1;
	i = -1;
	if (ft_sem_unlink(data))
		return (0);
	while (++i < 5)
	{
		if (data->s_sema[i] == SEM_FAILED)
		{
			while (++j < i)
				sem_close(data->s_sema[j]);
			return (0);
		}
	}
	head = allocate_list(data);
	return (head);
}
