/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:41:09 by mbaanni           #+#    #+#             */
/*   Updated: 2023/05/25 15:29:27 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include<stdio.h>
# include<unistd.h>
# include<sys/time.h>
# include<sys/wait.h>
# include<pthread.h>
# include<unistd.h>
# include<stdlib.h>
# include<fcntl.h>
# include<semaphore.h>
# include<string.h>
# include<signal.h>

typedef struct t_data
{
	int				dead;
	int				eating;
	long int		n_philo;
	long int		start;
	long int		t_to_die;
	long int		t_to_eat;
	long int		t_to_sleep;
	long int		n_of_t_philo_must_eat;
	sem_t			**s_sema;
}	t_data;

typedef struct t_philo
{
	int				id;
	int				fork_id;
	long int		n_t_eat;
	long int		t_eat;
	sem_t			*fork;
	sem_t			*write;
	sem_t			*dead;
	sem_t			*eat;
	sem_t			*check;
	struct t_philo	*next;
	struct t_philo	*prev;
	t_data			*data;
}	t_philo;
long int	ft_atoi(char *str);
void		routine(t_philo *ptr);
void		*monitor(void *ptr);
long int	time_it(void);
void		ft_usleep(long int end, t_philo *philo);
void		ft_putnbr(long int nb);
void		*kill_all(void *ptr);
t_philo		*creat_philo(t_data *data);
t_philo		*creat_list(t_data *data);
void		clean_up(t_philo *head, t_data *data);
enum
{
	s_fork,
	s_eat,
	s_dead,
	s_write,
	s_check
};
#endif