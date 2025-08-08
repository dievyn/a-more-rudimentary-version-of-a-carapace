/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdenis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:08:41 by tdenis            #+#    #+#             */
/*   Updated: 2025/07/30 16:08:43 by tdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int signal)
{
	if (signal == 2 && g_signal != -2)
	{
		g_signal = 130;
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	end_of_file(char *str, t_vars *va)
{
	free_tab(va->envi);
	close (va->fd[0]);
	close (va->fd[1]);
	close (va->fd[2]);
	free(str);
	printf("exit\n");
	exit (va->last_code);
}

void	end_heredoc(int signal)
{
	(void)signal;
	g_signal = 130;
	close(0);
}
