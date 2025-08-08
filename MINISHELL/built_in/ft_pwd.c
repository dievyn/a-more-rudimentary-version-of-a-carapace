/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdenis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:47:51 by tdenis            #+#    #+#             */
/*   Updated: 2025/07/30 15:47:52 by tdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_vars *va)
{
	char	*path;
	char	*path2;

	path = NULL;
	path2 = getcwd(path, 0);
	if (path2 == NULL)
		return (printf("minishell: pwd: ERROR. cannot access"
				"current working directory.\n"));
	va->watatus = 0;
	printf("%s\n", path2);
	free(path);
	free(path2);
	return (1);
}
