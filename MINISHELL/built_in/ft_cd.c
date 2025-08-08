/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdenis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:47:09 by tdenis            #+#    #+#             */
/*   Updated: 2025/07/30 15:47:12 by tdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	old_pwd(t_vars *va)
{
	int		i;
	char	*old_path;

	i = 0;
	while (va->envi[i] && ft_strncmp(va->envi[i], "OLDPWD=", 7) != 0)
		i++;
	free(va->envi[i]);
	old_path = getcwd(NULL, 0);
	if (old_path == NULL)
		old_path = ft_strdup("");
	va->envi[i] = ft_strjoin("OLDPWD=", old_path);
	free(old_path);
	return (1);
}

static int	get_home(t_vars *va)
{
	int		i;
	char	*home;

	i = 0;
	va->watatus = 0;
	while (va->envi[i] && ft_strncmp(va->envi[i], "HOME=", 5) != 0)
		i++;
	home = ft_strdup(va->envi[i]);
	chdir(&home[5]);
	i = 0;
	while (va->envi[i] && ft_strncmp(va->envi[i], "PWD=", 4) != 0)
		i++;
	free(va->envi[i]);
	va->envi[i] = ft_strjoin("PWD=", &home[5]);
	free(home);
	return (1);
}

static void	set_pwd(char **env)
{
	char	*temp;
	int		i;

	i = 0;
	temp = getcwd(NULL, 0);
	if (temp == NULL)
		temp = ft_strdup("");
	while (env[i] && ft_strnstr(env[i], "PWD=", 4) == NULL)
		i++;
	free(env[i]);
	env[i] = ft_strjoin("PWD=", temp);
	free(temp);
}

int	ft_cd(t_vars *va, char **arguments)
{
	old_pwd(va);
	if (arguments[2])
		return (ft_printf(2, "minishell: cd: too many arguments.\n"));
	if (!arguments[1])
		return (get_home(va));
	if (access(arguments[1], X_OK) != 0 && access(arguments[1], F_OK) == 0)
		return (ft_printf(2, "minishell: cd: %s: permission denied.\n",
				arguments[1]));
	if (chdir(arguments[1]) == -1)
		return (ft_printf(2, "minishell: cd: %s: no such file or directory.\n",
				arguments[1]));
	va->watatus = 0;
	set_pwd(va->envi);
	return (1);
}
