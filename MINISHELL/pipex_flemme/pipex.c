/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_flemme->c                                     :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: tdenis <marvin@42->fr>                      +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:51:36 by tdenis            #+#    #+#             */
/*   Updated: 2025/03/13 11:51:40 by tdenis           ###   ########->fr      */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fd(t_vars *va)
{
	close(va->pipe1[1]);
	close(va->pipe1[0]);
	close(va->pipe2[1]);
	close(va->pipe2[0]);
}

static int	anti_minishell(t_list *list)
{
	t_list	*save;

	save = list;
	while (list->next)
	{
		if (list->com && ft_strnstr(list->com, "minishell\0",
				ft_strlen(list->com)) != NULL)
			return (1);
		list = list->next;
	}
	list = save;
	return (0);
}

int	pipex(t_vars *va, t_list *list)
{
	int		i;

	if (anti_minishell(list) == 1)
		return (ft_printf(2, "ERROR. cannot execute './minishell'"
				"inside pipe\n"));
	pipe(va->pipe1);
	pipe(va->pipe2);
	i = 0;
	com_looop(va, list);
	return (0);
}
