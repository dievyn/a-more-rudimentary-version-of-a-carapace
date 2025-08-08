/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_annexes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:47:14 by kkafmagh          #+#    #+#             */
/*   Updated: 2025/08/04 19:46:16 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_flemme/pipex.h"

static int	count_files(char **tab, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!tab || !c)
		return (0);
	while (tab[i])
	{
		if (!tab[i][0])
			return (0);
		if (tab[i] && tab[i][0] == c)
			j++;
		i++;
	}
	if (j)
		j++;
	return (j);
}

t_list	*initiate_node(char *command_str)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->arguments = NULL;
	node->arguments = split_words(command_str);
	if (!node->arguments)
		return (NULL);
	node->prev = NULL;
	node->next = NULL;
	node->com = NULL;
	node->infile = NULL;
	node->infile = ft_calloc(count_files(node->arguments, '<') + 1,
			sizeof(char *));
	node->fd_in = 0;
	node->outfile = NULL;
	node->outfile = ft_calloc(count_files(node->arguments, '>') + 1,
			sizeof(char *));
	node->fd_out = 0;
	if (!node->infile || !node->outfile)
		return (NULL);
	return (node);
}

void	chevrons(char **input, char **result, int *i, int *j)
{
	if ((*input)[(*i)] && ((*input)[(*i)] == '<' || (*input)[(*i)] == '>'
			|| (*input)[(*i)] == '|'))
	{
		if (((*input)[(*i)] == '<' && (*input)[(*i) + 1] == '<')
			|| ((*input)[(*i)] == '>' && (*input)[(*i) + 1] == '>'))
		{
			if ((*result)[(*j) && (*result)[(*j)] != ' '])
				(*result)[(*j)++] = ' ';
			(*result)[(*j)++] = (*input)[(*i)++];
			(*result)[(*j)++] = (*input)[(*i)++];
			if ((*input)[(*i)] != ' ')
				(*result)[(*j)++] = ' ';
		}
		else
		{
			if ((*result)[(*j) && (*result)[(*j)] != ' '])
				(*result)[(*j)++] = ' ';
			(*result)[(*j)++] = (*input)[(*i)++];
			if ((*input)[(*i)] != ' ')
				(*result)[(*j)++] = ' ';
		}
	}
	else
		(*result)[(*j)++] = (*input)[(*i)++];
}
