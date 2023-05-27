/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:41:09 by mbaanni           #+#    #+#             */
/*   Updated: 2023/05/25 14:38:45 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include<stdio.h>
# include<unistd.h>
# include<sys/time.h>
# include<pthread.h>
# include<unistd.h>
# include<string.h>
# include<stdlib.h>

typedef struct t_data
{
	int				dead;
	long int		n_philo;
	long int		start;
	long int		t_to_die;
	long int		t_to_eat;
	long int		t_to_sleep;
	long int		n_of_t_philo_must_eat;
	pthread_mutex_t	*m_dead;
	pthread_mutex_t	*m_write;
	pthread_mutex_t	*mutex;
	pthread_t		*t;
}	t_data;

typedef struct t_philo
{
	int				id;
	int				t;
	long int		n_t_eat;
	long int		t_eat;
	pthread_t		*thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*m_dead;
	pthread_mutex_t	*m_write;
	struct t_philo	*next;
	struct t_philo	*prev;
	t_data			*data;
}	t_philo;
long int	ft_atoi(char *str);
void		*routine(void *ptr);
long int	time_it(void);
void		ft_usleep(long int end, t_philo *philo, int i);
void		ft_putnbr(long int nb);
void		monitoring(t_philo	*head, t_data *data);
int			creat_mutex(t_philo *head, t_data *data);
void		clean_up(t_data *data, t_philo *head);
int			thinking_philo(t_philo *philo, int i);
t_philo		*creat_list(t_data *data);
#endif