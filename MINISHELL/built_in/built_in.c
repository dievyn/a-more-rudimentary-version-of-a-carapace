/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdenis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:46:28 by tdenis            #+#    #+#             */
/*   Updated: 2025/07/30 15:46:30 by tdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	built_in2(t_vars *va, t_list *list)
{
	if (list->com && ft_strncmp(list->com, "echo\0",
			ft_strlen("echo\0") + 1) == 0)
		return (ft_echo(va, list->arguments));
	else if (list->com && ft_strncmp(list->com, "export\0",
			ft_strlen("export\0") + 1) == 0)
	{
		va->envi = export1(va, list->arguments, va->envi);
		return (1);
	}
	else if (list->com && ft_strncmp(list->com, "unset\0",
			ft_strlen("unset\0") + 1) == 0)
	{
		va->envi = ft_unset(list->arguments, va->envi);
		return (1);
	}
	return (0);
}

int	built_in(t_vars *va, t_list *list)
{
	if (list->com && ft_strncmp(list->com, "exit\0",
			ft_strlen("exit\0") + 1) == 0)
		return (ft_exit(va, list));
	else if (list->com && ft_strncmp(list->com, "pwd\0",
			ft_strlen("pwd\0") + 1) == 0)
		return (ft_pwd(va));
	else if (list->com && ft_strncmp(list->com, "env\0",
			ft_strlen("env\0") + 1) == 0)
		return (print_tab(va->envi));
	else if (list->com && ft_strncmp(list->com, "cd\0",
			ft_strlen("cd\0") + 1) == 0)
	{
		if (ft_cd(va, list->arguments) != 1)
			va->watatus = 257;
		return (1);
	}
	else if (list->com && ft_strncmp(list->com, "hex\0",
			ft_strlen("hex\0") + 1) == 0)
		return (print_hex(va));
	return (built_in2(va, list));
}
