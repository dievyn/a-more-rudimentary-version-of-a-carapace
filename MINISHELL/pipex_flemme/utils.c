/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdenis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:52:05 by tdenis            #+#    #+#             */
/*   Updated: 2025/03/13 11:52:06 by tdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	find_str(const char *big, const char *cute, int len)
{
	int	i;
	int	j;

	i = -1;
	while ((i != len && big[i] != '\0') || i == -1)
	{
		j = 0;
		while (big[i++] == cute[j++])
			if (cute[j] == '\0')
				return (1);
	}
	return (0);
}

int	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	return (1);
}

int	tab_len(char **tab)
{
	int	i;

	i = 1;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

int	chain_len(t_list *list)
{
	int	i;

	i = 1;
	while (list->prev)
		list = list->prev;
	while (list->next)
	{
		list = list->next;
		i++;
	}
	return (i);
}
