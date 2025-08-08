/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdenis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:52:05 by tdenis            #+#    #+#             */
/*   Updated: 2025/03/13 11:52:06 by tdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	get_code(int code)
{
	if (code == 0)
		return (0);
	else if (code >= 256)
		return (code / 256);
	else
		return (code + 128);
}

void	exec_wait(t_vars *va)
{
	int	i;

	i = 0;
	while (va->pid[i])
	{
		waitpid(va->pid[i], &va->watatus, 0);
		if (va->watatus == 139)
		{
			va->watatus = va->watatus * 256;
			ft_printf(2, "Segmentation fault (core dumpted)\n");
		}
		else if (va->watatus == 15)
			ft_printf(2, "Terminated\n");
		else if (va->watatus == 131)
		{
			va->watatus = va->watatus * 256;
			ft_printf(2, "Quit (core dumpted)\n");
		}
		i++;
	}
	free(va->pid);
}

void	exec(t_vars *va, t_list *list)
{
	va->pid = ft_calloc (chain_len(list) + 1, sizeof (int));
	if (!va->pid)
		return ;
	g_signal = -2;
	while (list->prev)
		list = list->prev;
	if (chain_len(list) == 1)
		single_com(va, list);
	else
	{
		pipex(va, list);
		close_list(list);
	}
	exec_wait(va);
	close_fd(va);
	g_signal = get_code(va->watatus);
	va->last_code = g_signal;
}
