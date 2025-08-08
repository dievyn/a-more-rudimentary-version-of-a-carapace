/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:46:48 by kkafmagh          #+#    #+#             */
/*   Updated: 2025/08/04 19:46:49 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_flemme/pipex.h"

int	skip_quotes(char *input)
{
	int	i;
	int	type;

	i = 1;
	type = input[0];
	while (input[i] && input[i] != type)
		i++;
	return (i);
}

int	checkquotes(char *input)
{
	int		i;
	int		quote;
	char	type;

	quote = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = 1;
			type = input[i];
			i++;
			while (input[i] && input[i] != type)
				i++;
			if (input[i] == type)
				quote = 0;
		}
		if (input[i])
			i++;
	}
	if (quote == 1)
		return (ft_printf(2, "syntax error. unclosed quotes in \"%s\"\n", input));
	return (0);
}

int	empty_line(char *input)
{
	int	i;

	i = 0;
	while (input[i] && ft_isprint(input[i]) == 0)
		i++;
	if (!input[i])
		return (-1);
	return (0);
}

int	errorpipe(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] == ' ')
		i++;
	if (input[i] && input[i] == '|')
		return (ft_printf(2, "syntax error near unexpected token '|'\n"));
	i = ft_strlen(input) - 1;
	while (input[i] && input[i] == ' ')
		i--;
	if (input[i] && input[i] == '|')
		return (ft_printf(2, "syntax error near unexpected token '|'\n"));
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			i += skip_quotes(&input[i]);
		i++;
		if (input[i] && input[i] == '|' && input[i + 1] == '|')
			return (ft_printf(2, "syntax error near unexpected token '|'\n"));
	}
	return (0);
}

int	syntaxerror(char *input)
{
	if (empty_line(input) != 0)
		return (-1);
	if (checkquotes(input) != 0)
		return (-1);
	if (errorpipe(input) != 0)
		return (-1);
	if (errorchevron(input) != 0)
		return (-1);
	if (errorchevron2(input) != 0)
		return (-1);
	return (0);
}

//	echo >>> ghdrth
//	echo >< dfghsrf
//	echo >> | tghdsrfg
//	echo >> >>> gfhxgfh
//	echo >>< dfgdsf
//	echo etshys || rgser
//	echo > '|'
