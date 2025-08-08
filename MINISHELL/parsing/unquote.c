/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:46:54 by kkafmagh          #+#    #+#             */
/*   Updated: 2025/08/04 19:46:55 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_flemme/pipex.h"

static int	im_tired(char *str)
{
	int	i;

	i = 0;
	while (ft_isalnum(str[i]) != 0 || str[i] == '$')
	{
		i++;
		if (str[i] == '?')
			i++;
	}
	return (i);
}

static char	*environement_variable_in_quotes(t_vars *va, char *input,
		char *result, int *idx)
{
	char	*environement_va;
	char	*tmp;

	tmp = ft_substr(&input[idx[0]], 0, im_tired(&input[idx[0]]));
	if (!tmp)
		return (NULL);
	environement_va = get_evar(va, tmp);
	if (!environement_va)
		return (NULL);
	idx[0] += ft_strlen(tmp);
	idx[1] += ft_strlen(environement_va);
	free(tmp);
	if (result && environement_va)
		tmp = ft_strjoin(result, environement_va);
	if (!tmp)
		return (NULL);
	free(result);
	result = ft_calloc(ft_strlen(input) + ft_strlen(environement_va) + 1,
			sizeof (char *));
	if (!result)
		return (NULL);
	ft_strlcpy(result, tmp, ft_strlen(tmp) + 1);
	free(tmp);
	free(environement_va);
	return (result);
}

static char	*double_quotes(t_vars *va, char *input, char *result, int *idx)
{
	idx[0]++;
	while (input[idx[0]] && input[idx[0]] != 34)
	{
		if (input[idx[0]] == '$')
			result = environement_variable_in_quotes(va, input, result, idx);
		else if (input[idx[0]] == 34)
			idx[0]++;
		else if (result && input)
		{
			result[idx[1]] = input[idx[0]];
			idx[0]++;
			idx[1]++;
		}
	}
	idx[0]++;
	return (result);
}

static void	single_quotes(char *input, char *result, int *idx)
{
	idx[0]++;
	while (input[idx[0]] && input[idx[0]] != 39)
	{
		result[idx[1]] = input[idx[0]];
		idx[0]++;
		idx[1]++;
	}
	idx[0]++;
}

char	*ft_unquote(t_vars *va, char *str)
{
	int		index[2];
	char	*result;

	index[0] = 0;
	index[1] = 0;
	result = ft_calloc(ft_strlen(str) + 1, sizeof(char *));
	if (!result)
		return (NULL);
	while (str[index[0]])
	{
		if (str[index[0]] == '$')
			result = environement_variable_in_quotes(va, str, result, index);
		else if (str[index[0]] == '\"')
			result = double_quotes(va, str, result, index);
		else if (str[index[0]] == '\'')
			single_quotes(str, result, index);
		else if (result && str)
		{
			result[index[1]] = str[index[0]];
			index[0]++;
			index[1]++;
		}
	}
	return (result);
}
