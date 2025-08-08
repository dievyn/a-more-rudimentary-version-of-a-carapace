/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_dup2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdenis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:23:27 by tdenis            #+#    #+#             */
/*   Updated: 2025/07/30 13:23:30 by tdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_outfile(t_vars *va, char **out_tab)
{
	char	*file;
	int		i;

	i = 0;
	while (out_tab[i])
	{
		file = get_file(out_tab[i]);
		if (check_out_access(va, file) != 0)
		{
			free(file);
			return (-1);
		}
		i++;
		free(file);
	}
	return (0);
}

int	check_infile(t_vars *va, char **in_tab)
{
	char	*file;
	int		i;

	i = 0;
	while (in_tab[i])
	{
		if (in_tab[i][1] != '<')
		{
			file = get_file(in_tab[i]);
			if (check_in_access(va, file) != 0)
			{
				free(file);
				return (-1);
			}
			free(file);
		}
		i++;
	}
	return (0);
}

int	check_in_access(t_vars *va, char *file)
{
	if (check_dir(va, file) == 0)
		return (1);
	if (access(file, F_OK) != 0)
		return (ft_printf(2, "minishell: no such file or directory: %s\n",
				file));
	else if (access(file, R_OK) != 0)
		return (ft_printf(2, "minishell: permission denied: %s\n", file));
	return (0);
}

int	check_out_access(t_vars *va, char *file)
{
	if (check_dir(va, file) == 0)
		return (1);
	if (access(file, W_OK) != 0 && access(file, F_OK) == 0)
		return (ft_printf(2, "minishell: permission denied: %s\n", file));
	return (0);
}
