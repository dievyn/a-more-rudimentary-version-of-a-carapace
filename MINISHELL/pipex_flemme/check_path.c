/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdenis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:51:36 by tdenis            #+#    #+#             */
/*   Updated: 2025/03/13 11:51:40 by tdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	paths_4(t_vars *va, char *com)
{
	if (com && access(com, F_OK) == 0 && access(com, X_OK) != 0)
	{
		va->watatus = 126;
		ft_printf(2, "minishell: permission denied: %s\n", com);
		return (0);
	}
	else if (com && access(com, F_OK) == 0)
		return (1);
	else
	{
		va->watatus = 127;
		ft_printf(2, "minishell: command not found: %s\n", com);
		return (0);
	}
}

static int	paths_3(t_list *list, char **all_paths)
{
	int		i;
	char	*commande;
	char	*str;

	i = 1;
	if (list->com && ft_strcmp(list->com, "") == 0)
		return (0);
	while (all_paths[i])
	{
		str = ft_strjoin(all_paths[i], "/");
		commande = ft_strjoin(str, list->com);
		ft_free(str);
		if (access(commande, F_OK) == 0)
		{
			free(list->com);
			list->com = ft_strdup(commande);
			return (free_tab(all_paths));
		}
		ft_free(commande);
		i++;
	}
	return (0);
}

static int	paths_2(t_vars *va, char *path_line, char **all_paths, t_list *list)
{
	int		i;

	i = 0;
	if (list->com[0] == '/'
		&& access(list->com, X_OK) != 0)
	{
		va->watatus = 126;
		ft_printf(2, "minishell: permission denied: %s\n", list->com);
		return (0);
	}
	while (va->envi[i] && ft_strnstr(va->envi[i], "PATH", 4) == 0)
		i++;
	path_line = va->envi[i];
	if (path_line)
		all_paths = ft_split(path_line, ':');
	if (!all_paths)
		return (ft_printf(2, "minishell: command not found: %s\n", list->com));
	if (paths_3(list, all_paths) == 1)
		return (1);
	free_tab(all_paths);
	return (paths_4(va, list->com));
}

int	check_dir(t_vars *va, char *commande)
{
	DIR	*dir;

	dir = opendir(commande);
	if (dir != NULL)
	{
		va->watatus = 126;
		closedir(dir);
		ft_printf(2, "minishell: %s: Is a directory.\n", commande);
		return (0);
	}
	return (1);
}

int	check_path(t_vars *va, t_list *list)
{
	char	*path_line;
	char	**all_paths;

	path_line = NULL;
	all_paths = NULL;
	if (!list->com)
	{
		va->watatus = 0;
		return (0);
	}
	if (check_dir(va, list->com) == 0)
		return (0);
	if (list->com[0] == '/'
		&& access(list->com, F_OK) == 0)
		return (1);
	else if (list->com[0] == '/'
		&& access(list->com, F_OK) != 0)
	{
		va->watatus = 127;
		ft_printf(2, "minishell: no such file or directory: %s\n", list->com);
		return (0);
	}
	return (paths_2(va, path_line, all_paths, list));
}
