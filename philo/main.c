/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:41:54 by mbaanni           #+#    #+#             */
/*   Updated: 2023/05/25 08:49:38 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	time_it(void)
{
	struct timeval	time;
	long int		ends;

	gettimeofday(&time, NULL);
	ends = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ends);
}

int	parse_argument(t_data *data, int ac, char **av)
{
	data->n_philo = ft_atoi(av[1]);
	data->t_to_die = ft_atoi(av[2]);
	data->t_to_eat = ft_atoi(av[3]);
	data->t_to_sleep = ft_atoi(av[4]);
	if (data->n_philo <= 0 || data->t_to_die <= 0
		|| data->t_to_eat < 0 || data->t_to_sleep < 0)
		return (1);
	if (ac == 6)
	{
		data->n_of_t_philo_must_eat = ft_atoi(av[5]);
		if (data->n_of_t_philo_must_eat <= 0)
			return (1);
	}
	else
		data->n_of_t_philo_must_eat = 0;
	return (0);
}

t_philo	*creat_philo(t_data *data)
{
	t_philo	*head;
	t_philo	*tmp;
	int		i;

	i = 0;
	data->dead = 0;
	head = creat_list(data);
	if (!head)
		return (0);
	if (creat_mutex(head, data))
		return (0);
	tmp = head;
	data->start = time_it();
	while (tmp)
	{
		tmp->t_eat = time_it();
		tmp->id = i + 1;
		pthread_create(tmp->thread, 0, routine, tmp);
		tmp = tmp->next;
		if (tmp == head)
			break ;
		i++;
	}
	return (head);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*head;

	if (ac < 5 || ac > 6)
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	memset(data, 0, sizeof(t_data));
	if (parse_argument(data, ac, av))
	{
		free (data);
		return (1);
	}
	head = creat_philo(data);
	if (!head)
	{
		free (data);
		return (1);
	}
	monitoring(head, data);
	clean_up(data, head);
	return (0);
}
