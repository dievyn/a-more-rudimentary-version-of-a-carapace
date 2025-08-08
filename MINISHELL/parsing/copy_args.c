/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:19:45 by tdenis            #+#    #+#             */
/*   Updated: 2025/08/04 19:46:13 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*copyfile(char *src, char *src2)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	dest = ft_calloc((ft_strlen(src) + ft_strlen(src2) + 2), sizeof(char *));
	if (!dest)
		return (NULL);
	while (src[i])
	{
		dest[j] = src[i];
		j++;
		i++;
	}
	dest[ft_strlen(src)] = ' ';
	j = ft_strlen(src) + 1;
	i = 0;
	while (src2[i])
	{
		dest[j] = src2[i];
		j++;
		i++;
	}
	return (dest[j] = '\0', dest);
}

void	copyinfile(t_list **node, int *idx)
{
	while ((ft_strcmp((*node)->arguments[idx[0]], "<") == 0
			|| ft_strcmp((*node)->arguments[idx[0]], "<<") == 0)
		&& (*node)->arguments[idx[0] + 1])
	{
		(*node)->infile[idx[2]] = copyfile((*node)->arguments[idx[0]],
				(*node)->arguments[idx[0] + 1]);
		idx[0] += 2;
		idx[2]++;
	}
}

void	copyoutfile(t_list **node, int *idx)
{
	while ((ft_strcmp((*node)->arguments[idx[0]], ">") == 0
			|| ft_strcmp((*node)->arguments[idx[0]], ">>") == 0)
		&& (*node)->arguments[idx[0] + 1])
	{
		(*node)->outfile[idx[1]] = copyfile((*node)->arguments[idx[0]],
				(*node)->arguments[idx[0] + 1]);
		idx[0] += 2;
		idx[1]++;
	}
}
