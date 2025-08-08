/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:19:35 by tdenis            #+#    #+#             */
/*   Updated: 2025/08/04 19:46:10 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*clean_string(t_vars *va, char *str)
{
	char	*result;

	if (!str)
		return (NULL);
	result = ft_unquote(va, str);
	free(str);
	if (!result)
		return (NULL);
	return (result);
}

void	clean_files(t_vars *va, t_list **node)
{
	int	i;

	i = 0;
	while ((*node)->arguments[i])
	{
		(*node)->arguments[i] = clean_string(va, (*node)->arguments[i]);
		i++;
	}
	i = 0;
	while ((*node)->infile[i])
	{
		(*node)->infile[i] = clean_string(va, (*node)->infile[i]);
		i++;
	}
	i = 0;
	while ((*node)->outfile[i])
	{
		(*node)->outfile[i] = clean_string(va, (*node)->outfile[i]);
		i++;
	}
	(*node)->com = clean_string(va, (*node)->com);
}

static int	count_clean_args(t_list *node)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (node->arguments[i])
	{
		if (node->arguments[i][0] == '<' || node->arguments[i][0] == '>')
			i = i + 2;
		else
		{
			i++;
			j++;
		}
	}
	return (j + 1);
}

void	clean_args(t_list **node)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	tab = ft_calloc(count_clean_args(*node) + 1, sizeof(char *));
	if (!tab)
		return ;
	while ((*node)->arguments[i])
	{
		if ((*node)->arguments[i][0] == '<' || (*node)->arguments[i][0] == '>')
			i = i + 2;
		else
		{
			tab[j] = ft_strdup((*node)->arguments[i]);
			if (!tab[j] || !(*node)->arguments[i])
				break ;
			i++;
			j++;
		}
	}
	free_tab((*node)->arguments);
	(*node)->arguments = tab;
}
