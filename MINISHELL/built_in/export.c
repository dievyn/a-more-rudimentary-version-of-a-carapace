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

static void	switch_tab(char **str1, char **str2)
{
	char *tmp1;
	char *tmp2;

	tmp1 = ft_strdup((*str1));
	tmp2 = ft_strdup((*str2));
	free((*str1));
	free((*str2));
	(*str1) = ft_strdup(tmp2);
	(*str2) = ft_strdup(tmp1);
}

static int	check_order(char **tab)
{
	int i;

	i = 0;
	while (tab[i + 1])
	{
		if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			return (0);
		i++;
	}
	return (1);
}

char	**print_export(t_vars *va, char **env)
{
	int	i;
	char **printer;

	printer = copy_tab(env);
	while(check_order(printer) == 0)
	{
		i = 0;
		while (printer[i + 1])
		{
			if(ft_strcmp(printer[i], printer[i + 1]) > 0)
			{
				printf("[%d]\nbefore switch\n%s\n%s\n", i, printer[i], printer[i + 1]);
				switch_tab(&printer[i], &printer[i + 1]);
				printf("after switch\n%s\n%s\n", printer[i], printer[i + 1]);
				sleep(10);
				// break ;
			}
			i++;
		}
	}
	print_tab(printer);
	free_tab(printer);
	va->watatus = 0;
	return (env);
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
