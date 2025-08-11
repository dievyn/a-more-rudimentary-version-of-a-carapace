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

static int	is_alphanum(char *str)
{
	int	i;

	i = 0;
	while ((str[i] && ft_isalnum(str[i]) != 0) || str[i] == '_')
		i++;
	if (str[i] != 0)
		return (0);
	return (1);
}

static int	is_what_str(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	**export_1a(t_vars *va, int i, char **arguments, char **new)
{
	char	*var;
	char	*arg;
	int		j;

	j = 0;
	while (arguments[i][j] && arguments[i][j] != '=')
		j++;
	var = ft_substr(arguments[i], 0, j);
	arg = ft_substr(arguments[i], j, ft_strlen(arguments[i]));
	if (is_alphanum(var) == 1 && ft_isdigit(arguments[i][0]) == 0
		&& is_what_str(arguments[i], '=') == 1)
		new = export2(var, arg, new);
	else if ((is_alphanum(var) != 1 || ft_isdigit(arguments[i][0]) != 1)
		&& is_what_str(arguments[i], '=') == 1)
	{
		va->watatus = 256;
		ft_printf(2, "minishell: export: %s: not a valid identifier\n",
			arguments[i]);
	}
	free(var);
	free(arg);
	return (new);
}
