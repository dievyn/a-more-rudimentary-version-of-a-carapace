/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdenis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:46:40 by tdenis            #+#    #+#             */
/*   Updated: 2025/07/30 15:46:43 by tdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_echo(char **arg, int mode)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		printf("%s", arg[i]);
		i++;
		if (arg[i])
			printf(" ");
	}
	if (mode == 1)
		printf("\n");
}

static int	skip_flags(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] == '-')
	{
		while (arg[i] && arg[i] == 'n')
			i++;
		if (arg && arg[i])
			return (0);
		return (1);
	}
	return (0);
}

int	ft_echo(t_vars *va, char **arguments)
{
	int	i;

	i = 1;
	va->watatus = 0;
	while (arguments[i] && skip_flags(arguments[i]) == 1)
		i++;
	if (!arguments[1] || skip_flags(arguments[1]) == 0)
		print_echo(&arguments[i], 1);
	else
		print_echo(&arguments[i], 0);
	return (1);
}
