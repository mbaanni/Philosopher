/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:15:04 by mbaanni           #+#    #+#             */
/*   Updated: 2023/05/22 12:44:59 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_up(t_philo *head, t_data *data)
{
	t_philo	*tmp;
	t_philo	*ptr;
	int		i;

	i = -1;
	tmp = head;
	while (++i < 5)
		sem_close(data->s_sema[i]);
	while (tmp)
	{
		ptr = tmp;
		tmp = tmp->next;
		free(ptr);
		if (tmp == head)
			break ;
	}
	free (data->s_sema);
	free (data);
}
