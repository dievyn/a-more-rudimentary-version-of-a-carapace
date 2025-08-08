/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:46:29 by kkafmagh          #+#    #+#             */
/*   Updated: 2025/08/04 19:46:30 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_flemme/pipex.h"

static int	count_pipes(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] && input[i] == '|')
			count++;
		if (input[i] && (input[i] == '\'' || input[i] == '\"'))
			i += skip_quotes(&input[i]);
		i++;
	}
	return (count);
}

char	**split_cmd(char *input)
{
	char	**result;
	int		i[2];
	int		start;

	i[0] = 0;
	i[1] = 0;
	start = 0;
	result = ft_calloc(count_pipes(input) + 2, sizeof (char *));
	if (!result)
		return (NULL);
	while (input[i[0]])
	{
		if (input[i[0]] && (input[i[0]] == '\'' || input[i[0]] == '\"'))
			i[0] += skip_quotes(&input[i[0]]);
		i[0]++;
		if ((input[i[0]] && input[i[0]] == '|'))
		{
			result[i[1]] = ft_substr(input, start, i[0] - start);
			i[1]++;
			i[0]++;
			start = i[0];
		}
	}
	result[i[1]] = ft_substr(input, start, i[0] - start);
	return (result);
}
