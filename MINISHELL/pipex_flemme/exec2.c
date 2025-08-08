/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdenis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:14:16 by tdenis            #+#    #+#             */
/*   Updated: 2025/07/30 12:14:26 by tdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	switch_pipe(int in_pipe[2], int out_pipe[2])
{
	int	temp;

	temp = in_pipe[1];
	in_pipe[1] = out_pipe[1];
	out_pipe[1] = temp;
	temp = in_pipe[0];
	in_pipe[0] = out_pipe[0];
	out_pipe[0] = temp;
	close(in_pipe[0]);
	close(in_pipe[1]);
	pipe(in_pipe);
}

void	single_com(t_vars *va, t_list *list)
{
	if (make_dup(va, list) == 0)
	{
		close_list(list);
		if (built_in(va, list) == 0)
		{
			va->pid[0] = fork();
			if (va->pid[0] == 0)
			{
				close (va->fd[2]);
				close (va->fd[1]);
				close (va->fd[0]);
				signal(2, NULL);
				signal(3, NULL);
				if (check_path(va, list) == 1)
					execve(list->com, list->arguments, va->envi);
				free_end(va, list);
			}
		}
	}
}

static void	loop2(t_vars *va, t_list *list)
{
	signal(2, NULL);
	signal(3, NULL);
	close_list(list);
	close_fd(va);
	if (built_in(va, list) == 0)
		if (check_path(va, list) == 1)
			execve(list->com, list->arguments, va->envi);
}

void	com_looop(t_vars *va, t_list *list)
{
	int	i;

	i = 0;
	while (list != NULL)
	{
		va->pid[i] = fork();
		if (va->pid[i] == 0)
		{
			close (va->fd[2]);
			close (va->fd[1]);
			close (va->fd[0]);
			if (make_dup(va, list) == 0)
				loop2(va, list);
			else
				close_list(list);
			close_fd(va);
			free_end(va, list);
		}
		switch_pipe(va->pipe2, va->pipe1);
		list = list->next;
		i++;
	}
}
