/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briandri <briandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 23:00:30 by briandri          #+#    #+#             */
/*   Updated: 2025/08/03 10:01:38 by briandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <limits.h>
# include "./printf/ft_printf.h"

typedef struct s_node
{
	char			c;
	struct s_node	*next;
}	t_node;

typedef enum e_status
{
	READY,
	BUSY
}	t_status;
void	manager(int signo, siginfo_t *info, void *more_info);
void	send_bit_per_bit(char c, pid_t client_pid);
int		ft_atoi(const char *str);
t_node	*add_char(t_node **head, char c);
void	print_and_free(t_node *head);

#endif
