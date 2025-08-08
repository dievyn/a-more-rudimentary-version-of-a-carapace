/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:38:53 by tdenis            #+#    #+#             */
/*   Updated: 2025/08/04 19:46:19 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	while_alphanum(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isalnum(str[i]) != 0)
		i++;
	return (i);
}

static char	*get_line(char **env, char *var)
{
	int		i;
	int		j;
	char	*temp;
	char	*result;

	i = 0;
	j = 0;
	temp = ft_strjoin(var, "=");
	if (!temp)
		return (NULL);
	free(var);
	while (env[i] && ft_strncmp(env[i], temp, ft_strlen(temp)) != 0)
		i++;
	free(temp);
	if (!env[i])
		return (ft_strdup(""));
	while (env[i][j] && env[i][j] != '=')
		j++;
	result = ft_substr(env[i], j + 1, ft_strlen(env[i]));
	if (!result)
		return (NULL);
	return (result);
}

static char	*get_evar2(t_vars *va, char *var)
{
	char	*temp;
	char	*temp2;
	char	*ret;

	if (!var)
		return (NULL);
	if (var && var[0] == '?')
		return (ft_itoa(g_signal));
	temp2 = ft_substr(var, 0, while_alphanum(var));
	if (!temp2)
		return (NULL);
	temp = get_line(va->envi, temp2);
	temp2 = ft_substr(var, while_alphanum(var), ft_strlen(var));
	if (!temp || !temp2)
		return (NULL);
	ret = ft_strjoin(temp, temp2);
	free(temp);
	free(temp2);
	return (ret);
}

char	*get_evar(t_vars *va, char *var)
{
	char	**tab;
	char	*ret;
	char	*temp;
	char	*copy;
	int		i;

	i = 0;
	ret = ft_strdup("");
	tab = ft_split(var, '$');
	if (!ret || !tab)
		return (NULL);
	while (tab[i])
	{
		temp = get_evar2(va, tab[i]);
		copy = ft_strdup(ret);
		free(ret);
		if (!temp || !copy)
			return (NULL);
		ret = ft_strjoin(copy, temp);
		free(copy);
		free(temp);
		i++;
	}
	free_tab(tab);
	return (ret);
}
