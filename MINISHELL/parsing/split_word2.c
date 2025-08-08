/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:46:44 by kkafmagh          #+#    #+#             */
/*   Updated: 2025/08/04 19:46:45 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_flemme/pipex.h"

void	skiping_quotes(char *quote, char **new_input, int *i)
{
	(*quote) = (*new_input)[(*i)];
	(*i)++;
	while ((*new_input)[(*i)] != (*quote))
		(*i)++;
}

int	count_splited_words(char *input)
{
	int		i;
	int		k;
	char	quote;
	char	*new_input;

	k = 0;
	i = 0;
	new_input = espacerchevrons(input);
	if (!new_input)
		return (0);
	while (new_input[i])
	{
		while (new_input[i] && new_input[i] != ' ')
		{
			if (new_input[i] == '\'' || new_input[i] == '\"')
				skiping_quotes(&quote, &new_input, &i);
			i++;
		}
		while (new_input[i] == ' ')
			i++;
		k++;
	}
	return (free(new_input), k + 1);
}

char	*mallocaword(char const *str, int start, int end)
{
	int		i;
	char	*s;

	i = 0;
	s = ft_calloc((end - start + 1), sizeof(char *));
	if (s == NULL || !str[0])
		return (NULL);
	while (start < end)
	{
		s[i] = str[start];
		start++;
		i++;
	}
	s[i] = '\0';
	return (s);
}
