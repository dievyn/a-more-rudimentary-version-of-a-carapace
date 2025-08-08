/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:46:32 by kkafmagh          #+#    #+#             */
/*   Updated: 2025/08/04 19:46:33 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_flemme/pipex.h"

void	spliting_bis(char **new_input, int *i, int *start)
{
	int		in_quote;
	char	quote_type;

	(*start) = (*i);
	in_quote = 0;
	quote_type = 0;
	while ((*new_input)[(*i)] && (in_quote || (*new_input)[(*i)] != ' '))
	{
		if (((*new_input)[(*i)] == '\'' || (*new_input)[(*i)] == '"')
				&& !in_quote)
		{
			in_quote = 1;
			quote_type = (*new_input)[(*i)];
		}
		else if (in_quote && (*new_input)[(*i)] == quote_type)
		{
			in_quote = 0;
			quote_type = 0;
		}
		(*i)++;
	}
}

void	spliting(char ***splited, char **new_input)
{
	int	i;
	int	k;
	int	start;

	start = 0;
	i = 0;
	k = 0;
	while ((*new_input)[i])
	{
		while ((*new_input)[i] == ' ')
			i++;
		if (!(*new_input)[i])
			break ;
		spliting_bis(new_input, &i, &start);
		(*splited)[k] = mallocaword((*new_input), start, i);
		if (!(*splited)[k])
		{
			free_tab((*splited));
			(*splited) = NULL;
			return ;
		}
		k++;
	}
	(*splited)[k] = NULL;
}

char	**split_words(char *input)
{
	char	**splited;
	char	*new_input;

	new_input = espacerchevrons(input);
	if (!new_input)
		return (NULL);
	splited = ft_calloc(count_splited_words(new_input) + 1, sizeof(char *));
	if (!splited)
		return (free(new_input), NULL);
	spliting(&splited, &new_input);
	free(new_input);
	return (splited);
}
