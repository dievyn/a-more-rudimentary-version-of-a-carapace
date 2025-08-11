/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdenis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:24:32 by tdenis            #+#    #+#             */
/*   Updated: 2025/07/30 13:24:35 by tdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_file(char *str)
{
	char	*file;

	if (str[1] == '<' || str[1] == '>')
		file = ft_substr(str, 3, ft_strlen(str));
	else
		file = ft_substr(str, 2, ft_strlen(str));
	return (file);
}

int	open_infile(t_vars *va, t_list *list)
{
	int		i;
	char	*file;

	i = 0;
	while (list->infile[i])
	{
		file = get_file(list->infile[i]);
		if (list->infile[i] && list->infile[i][1] != '<')
		{
			list->fd_in = open(file, O_RDONLY);
			free(file);
		}
		else if (heredoc(va, list, file) == -1)
			return (-1);
		i++;
		if (list->fd_in == -1)
			return (-1);
		if (list->infile[i] && list->fd_in > 1)
			close(list->fd_in);
	}
	return (0);
}

int	open_outfile(t_list *list)
{
	int		i;
	char	*file;

	i = 0;
	while (list->outfile[i])
	{
		file = get_file(list->outfile[i]);
		if (list->outfile[i] && list->outfile[i][1] != '>')
			list->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			list->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		free(file);
		i++;
		if (list->fd_out == -1)
			return (-1);
		if (list->outfile[i] && list->fd_out > 1)
			close(list->fd_out);
	}
	return (0);
}

int	open_files(t_vars *va, t_list *list)
{
	int	check;

	while (list->prev)
		list = list->prev;
	while (list)
	{
		check = 0;
		if (open_infile(va, list) == -1)
		{
			if (va->watatus == 256)
			{
				close_list(list);
				g_signal = 130;
				return (-1);
			}
			else
				g_signal = 0;
			check = 42;
		}
		if (check == 0)
			open_outfile(list);
		list = list->next;
	}
	return (0);
}
