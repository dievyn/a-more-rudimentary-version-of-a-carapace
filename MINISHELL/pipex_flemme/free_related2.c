/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_related2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdenis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:22:39 by tdenis            #+#    #+#             */
/*   Updated: 2025/07/30 13:22:43 by tdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_files(int *files)
{
	int	i;

	i = 0;
	while (files && files[i] != 0)
	{
		if (files[i] > 0)
			close(files[i]);
		i++;
	}
	free(files);
}

static void	free_maillon(t_list *list)
{
	free_tab(list->arguments);
	free_tab(list->outfile);
	free_tab(list->infile);
	if (list->next)
		free(list->next);
	if (list->com)
		free(list->com);
}

void	free_list(t_list *list)
{
	while (list && list->next)
		list = list->next;
	while (1)
	{
		free_maillon(list);
		if (!list->prev)
			break ;
		list = list->prev;
	}
	free(list);
}
