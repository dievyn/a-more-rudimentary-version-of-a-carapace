/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdenis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:46:50 by tdenis            #+#    #+#             */
/*   Updated: 2025/07/30 15:46:52 by tdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_flemme/pipex.h"

static char	**export3(char *var, char *arg, char **env)
{
	char	**new;
	int		i;

	i = 0;
	while (env[i])
		i++;
	new = ft_calloc(i + 2, sizeof (char **));
	i = 0;
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	free_tab(env);
	new[i] = ft_strjoin(var, arg);
	new[i + 1] = NULL;
	return (new);
}

char	**export2(char *var, char *arg, char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strnstr(env[i], var, ft_strlen(var)) == NULL)
		i++;
	if (env[i] == NULL)
		return (export3(var, arg, env));
	free(env[i]);
	env[i] = ft_strjoin(var, arg);
	return (env);
}
