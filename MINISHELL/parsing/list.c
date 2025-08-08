/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:32:29 by kkafmagh          #+#    #+#             */
/*   Updated: 2025/08/04 19:46:21 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_flemme/pipex.h"

static void	hate_norminette(t_vars *va, t_list *node, int m, int j)
{
	clean_args(&node);
	clean_files(va, &node);
	node->infile[m] = NULL;
	node->outfile[j] = NULL;
}

t_list	*create_node(t_vars *va, char *command_str)
{
	t_list	*node;
	int		i[3];

	node = initiate_node(command_str);
	if (!node)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (node->arguments[i[0]])
	{
		if (node->arguments[i[0]] && (ft_strcmp(node->arguments[i[0]], "<")
				== 0 || ft_strcmp(node->arguments[i[0]], "<<") == 0))
			copyinfile(&node, i);
		else if (node->arguments[i[0]] && (ft_strcmp(node->arguments[i[0]], ">")
				== 0 || ft_strcmp(node->arguments[i[0]], ">>") == 0))
			copyoutfile(&node, i);
		else if (node->com == NULL && node->arguments[i[0]])
			node->com = ft_strdup(node->arguments[i[0]]);
		else
			i[0]++;
	}
	hate_norminette(va, node, i[2], i[1]);
	return (node);
}

static int	end_norminette(char ***splitpipe, char *input, int *i)
{
	if (!(*input))
		return (0);
	add_history(input);
	if (syntaxerror(input) == -1)
	{
		free(input);
		return (0);
	}
	(*i) = 0;
	(*splitpipe) = split_cmd(input);
	if (!(*splitpipe))
		return (0);
	return (1);
}

static void	anti_norminette(char **splitpipe, char *input)
{
	free_tab(splitpipe);
	free(input);
}

void	make_list(t_vars *va, char *input, char **splitpipe, t_list **current)
{
	t_list	*node;
	int		i;

	node = NULL;
	if (end_norminette(&splitpipe, input, &i) == 1)
	{
		while (splitpipe[i])
		{
			node = create_node(va, splitpipe[i]);
			if (!node)
				break ;
			if (i == 0)
				(*current) = node;
			else
			{
				(*current)->next = node;
				node->prev = (*current);
			}
			(*current) = node;
			i++;
		}
		anti_norminette(splitpipe, input);
	}
}
