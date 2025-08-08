/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_related.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdenis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:22:51 by tdenis            #+#    #+#             */
/*   Updated: 2025/07/30 13:23:02 by tdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
	return (1);
}

int	ft_free(void *str)
{
	if (str != NULL)
		free(str);
	str = NULL;
	return (1);
}

void	free_end(t_vars *va, t_list *list)
{
	free_list(list);
	free(va->pid);
	free_tab(va->envi);
	rl_clear_history();
	exit (va->watatus);
}

void	close_list(t_list *list)
{
	t_list	*saved;

	saved = NULL;
	saved = list;
	while (list->prev)
		list = list->prev;
	while (list)
	{
		if ((*list->infile) && list->infile[0] && list->fd_in > 0)
			close(list->fd_in);
		if ((*list->outfile) && list->outfile[0] && list->fd_out > 0)
			close(list->fd_out);
		list = list->next;
	}
	list = saved;
}

//	<< here cat | grep i > file3 > file2>file1
