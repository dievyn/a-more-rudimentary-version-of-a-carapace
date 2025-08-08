/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:19:54 by tdenis            #+#    #+#             */
/*   Updated: 2025/08/04 19:46:26 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	copy_quotes(char *input, char *result, int *i, int *j)
{
	int	quote;

	quote = input[(*i)];
	result[(*j)] = input[(*i)];
	(*i)++;
	(*j)++;
	while (input[(*i)] && input[(*i)] != quote)
	{
		result[(*j)] = input[(*i)];
		(*i)++;
		(*j)++;
	}
	if (input[(*i)] == quote)
	{
		result[(*j)] = input[(*i)];
		(*i)++;
		(*j)++;
	}
}

char	*espacerchevrons(char *input)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = ft_calloc(strlen(input) * 3 + 1, sizeof (char *));
	if (!result)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
			copy_quotes(input, result, &i, &j);
		else
			chevrons(&input, &result, &i, &j);
	}
	result[j] = '\0';
	return (result);
}
