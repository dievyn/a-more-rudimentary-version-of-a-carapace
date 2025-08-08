/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerror2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:46:51 by kkafmagh          #+#    #+#             */
/*   Updated: 2025/08/04 19:46:52 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_flemme/pipex.h"

static int	if_check2(char *input, int type, int (*i))
{
	if (input[(*i) + 2] && input[(*i) + 2] == type)
		return (ft_printf(2, "syntax error near unexpected token '%c'\n",
				type));
	while (input[(*i)] && input[(*i)] == type)
		(*i)++;
	if (input[(*i)] && (input[(*i)] == '<' || input[(*i)] == '>'))
		return (ft_printf(2, "syntax error near unexpected token '%c'\n",
				input[(*i)]));
	return (0);
}

int	errorchevron2(char *input)
{
	int	i;
	int	type;

	i = 0;
	while (input[i] == ' ')
		i++;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
		{
			type = input[i];
			if (if_check2(input, type, &i) != 0)
				return (42);
		}
		if (input[i] == '\'' || input[i] == '\"')
			i += skip_quotes(&input[i]);
		if (input[i])
		i++;
	}
	return (0);
}

static int	if_check(char *input, int type, int (*i))
{
	while (input[(*i)] && input[(*i)] == type)
		(*i)++;
	while (input[(*i)] && input[(*i)] == ' ')
		(*i)++;
	if (!input[(*i)])
		return (ft_printf(2, "syntax error near 'newline'\n"));
	if (input[(*i)] == '|' || input[(*i)] == '<' || input[(*i)] == '>')
		return (ft_printf(2, "syntax error near unexpected token '%c'\n",
				input[(*i)]));
	return (0);
}

int	errorchevron(char *input)
{
	int	i;
	int	type;

	i = 0;
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>')
		{
			type = input[i];
			if (if_check(input, type, &i) != 0)
				return (42);
			while (input[i] && input[i] != ' ' && input[i] != '|')
			{
				if (input[i] == '\'' || input[i] == '\"')
					i += skip_quotes(&input[i]);
				i++;
			}
		}
		if (input[i])
			i++;
	}
	return (0);
}
