/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briandri <briandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 23:00:48 by briandri          #+#    #+#             */
/*   Updated: 2025/08/03 10:15:42 by briandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	extension_manager(int *bit, char *c, t_node **msg, pid_t client_pid)
{
	if (*bit == CHAR_BIT)
	{
		if (*c == '\0')
		{
			print_and_free(*msg);
			*msg = NULL;
			kill(client_pid, SIGUSR2);
		}
		else
			add_char(msg, *c);
		*bit = 0;
		*c = 0;
	}
}

void	manager(int signo, siginfo_t *info, void *context)
{
	static char		c = 0;
	static int		bit = 0;
	static pid_t	client_pid = 0;
	static t_node	*msg = NULL;

	(void)context;
	if (info && info->si_pid)
		client_pid = info->si_pid;
	if (signo == SIGUSR1)
		c |= (0b10000000 >> bit);
	else if (signo == SIGUSR2)
		c &= ~(0b10000000 >> bit);
	bit++;
	extension_manager(&bit, &c, &msg, client_pid);
	kill(client_pid, SIGUSR1);
}

t_node	*add_char(t_node **head, char c)
{
	t_node	*new;
	t_node	*last;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->c = c;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	return (new);
}

void	print_and_free(t_node *head)
{
	t_node	*tmp;

	while (head)
	{
		write(1, &head->c, 1);
		tmp = head;
		head = head->next;
		free(tmp);
	}
	write(1, "\n", 1);
}

int	ft_atoi(const char *nprtr)
{
	int	i;
	int	sign;
	int	result;
	int	cmpt;

	sign = 1;
	i = 0;
	result = 0;
	cmpt = 0;
	while (nprtr[i] == 32 || (nprtr[i] >= 9 && nprtr[i] <= 13))
		i++;
	while (nprtr[i] == '-' || nprtr[i] == '+')
	{
		if (nprtr[i] == '-')
			sign *= -1;
		cmpt++;
		if (cmpt > 1)
			return (0);
		i++;
	}
	while (nprtr[i] >= 48 && nprtr[i] <= 57)
		result = result * 10 + (nprtr[i++] - '0');
	return (result * sign);
}
