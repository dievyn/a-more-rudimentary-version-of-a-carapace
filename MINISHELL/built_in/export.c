/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdenis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:46:59 by tdenis            #+#    #+#             */
/*   Updated: 2025/07/30 15:47:01 by tdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	switch_tab(char **str1, char **str2)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strdup((*str1));
	tmp2 = ft_strdup((*str2));
	free((*str1));
	free((*str2));
	(*str1) = ft_strdup(tmp2);
	(*str2) = ft_strdup(tmp1);
	free(tmp1);
	free(tmp2);
}

static int	check_order(char **tab)
{
	int	i;

	i = 0;
	while (tab[i + 1])
	{
		if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			return (i);
		i++;
	}
	return (-1);
}

char	**print_export(t_vars *va, char **env)
{
	char	**printer;

	printer = copy_tab(env);
	while (check_order(printer) != -1)
		switch_tab(&printer[check_order(printer)],
			&printer[check_order(printer) + 1]);
	print_tab(printer);
	free_tab(printer);
	va->watatus = 0;
	return (env);
}

char	**export1(t_vars *va, char **arguments, char **env)
{
	int		i;
	char	**new;

	i = 1;
	va->watatus = 0;
	new = copy_tab(env);
	free_tab(env);
	if (!arguments[1])
		return (print_export(va, new));
	while (arguments[i])
	{
		new = export_1a(va, i, arguments, new);
		i++;
	}
	return (new);
}
