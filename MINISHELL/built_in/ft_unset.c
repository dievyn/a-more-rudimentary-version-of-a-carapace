/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdenis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:47:59 by tdenis            #+#    #+#             */
/*   Updated: 2025/07/30 15:48:07 by tdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	find_variable(char *variable, char **env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i] && env[i][j] != '=')
			j++;
		temp = ft_substr(env[i], 0, j);
		if (ft_strncmp(variable, temp, ft_strlen(variable)) == 0)
		{
			free(temp);
			return (i);
		}
		free(temp);
		i++;
	}
	return (-1);
}

static char	**ft_unset2(char *variable, char **env)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	new = ft_calloc(tab_len(env) + 1, sizeof(char **));
	while (j <= tab_len(env))
	{
		if (find_variable(variable, env) == j)
			j++;
		if (env[j])
			new[i] = ft_strdup(env[j]);
		i++;
		j++;
	}
	return (new);
}

char	**ft_unset(char **arg, char **env)
{
	int		i;
	char	**new;
	char	**copy;

	i = 1;
	copy = copy_tab(env);
	free_tab(env);
	if (!arg[i])
		return (copy);
	while (arg[i])
	{
		new = ft_unset2(arg[i], copy);
		i++;
		if (arg[i])
		{
			free_tab(copy);
			copy = copy_tab(new);
			free_tab(new);
		}
	}
	free_tab(copy);
	return (new);
}
