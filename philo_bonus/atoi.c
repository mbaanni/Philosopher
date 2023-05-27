/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:50:28 by mbaanni           #+#    #+#             */
/*   Updated: 2023/05/25 10:58:05 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putnbr(long int nb)
{
	char	c;

	c = 0;
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = nb * -1;
	}
	if (nb / 10)
		ft_putnbr(nb / 10);
	c = nb % 10 + 48;
	write(1, &c, 1);
}

void	ft_usleep(long int end, t_philo *philo)
{
	long int	start;

	start = time_it();
	while ((time_it() - start) < (end))
	{
		if (philo->data->dead)
			return ;
		usleep(200);
	}
}

long int	ft_atoi(char *str)
{
	int			i;
	long int	number;

	number = 0;
	i = 0;
	if (!str)
		return (-1);
	while (str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] - 48 >= 0 && str[i] - 48 <= 9))
			return (-1);
		number = number * 10 + (str[i] - 48);
		if (number > 2147483647)
			return (-1);
		i++;
	}
	return (number);
}
