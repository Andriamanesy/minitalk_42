/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briandri <briandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 23:01:01 by briandri          #+#    #+#             */
/*   Updated: 2025/08/03 09:59:10 by briandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile t_status	g_client = BUSY;

void	ack_manager(int signo)
{
	if (signo == SIGUSR1)
		g_client = READY;
	else if (signo == SIGUSR2)
		ft_printf("\nMessage reçu par le serveur ✅\n");
}

void	send_bit_per_bit(char c, pid_t client_pid)
{
	int	bit;

	bit = 0;
	while (bit < CHAR_BIT)
	{
		if (c & (0b10000000 >> bit))
			kill(client_pid, SIGUSR1);
		else
			kill(client_pid, SIGUSR2);
		++bit;
		while (g_client == BUSY)
			usleep(42);
		g_client = BUSY;
	}
}

int	main(int ac, char *av[])
{
	pid_t	client;
	char	*message;

	if (ac != 3)
	{
		ft_printf("write: ./client <PID> \"your message\"\n");
		return (EXIT_FAILURE);
	}
	client = ft_atoi(av[1]);
	message = av[2];
	signal(SIGUSR1, ack_manager);
	signal(SIGUSR2, ack_manager);
	while (*message)
		send_bit_per_bit(*message++, client);
	send_bit_per_bit('\0', client);
	return (EXIT_SUCCESS);
}
