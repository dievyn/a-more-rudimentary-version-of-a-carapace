/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdenis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:24:00 by tdenis            #+#    #+#             */
/*   Updated: 2025/07/30 13:24:05 by tdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	dup_out(t_vars *va, t_list *list)
{
	int	i;

	i = 0;
	if (list->outfile[0] == NULL && list->next != NULL)
	{
		dup2(va->pipe2[1], 1);
		close(va->pipe2[0]);
	}
	if (check_outfile(va, list->outfile) != 0)
		return (-1);
	if (list->outfile[0] != NULL && list->fd_out > 0)
		dup2(list->fd_out, 1);
	return (0);
}

int	dup_in(t_vars *va, t_list *list)
{
	int	i;

	i = 0;
	if (list->infile[0] == NULL && list->prev != NULL)
	{
		dup2(va->pipe1[0], 0);
		close(va->pipe1[1]);
	}
	if (check_infile(va, list->infile) != 0)
		return (-1);
	if (list->infile[0] != NULL && list->fd_in > 0)
		dup2(list->fd_in, 0);
	return (0);
}

int	make_dup(t_vars *va, t_list *list)
{
	va->watatus = -1;
	if (dup_in(va, list) != 0)
	{
		if (va->watatus == 126)
			va->watatus = 126 * 257;
		else
			va->watatus = 257;
		if (list->infile[0] && list->fd_in > 0)
			close(list->fd_in);
		return (1);
	}
	if (dup_out(va, list) != 0)
	{
		if (va->watatus == 126)
			va->watatus = 126 * 257;
		else
			va->watatus = 257;
		if (list->outfile[0] && list->fd_out > 0)
			close(list->fd_out);
		return (1);
	}
	return (0);
}
