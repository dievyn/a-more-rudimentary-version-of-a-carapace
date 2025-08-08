/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdenis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:08:22 by tdenis            #+#    #+#             */
/*   Updated: 2025/07/30 16:08:25 by tdenis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex_flemme/pipex.h"

int	g_signal;

void	init_terminal(int argc, char **argv, char **env)
{
	int		pid;
	char	**arg;

	(void)env;
	(void)argv;
	(void)argc;
	arg = ft_calloc(2, sizeof (char *));
	if (!arg)
		return ;
	arg[0] = ft_strdup("clear");
	arg[1] = NULL;
	pid = fork();
	if (pid == 0)
	{
		execve("/usr/bin/clear", arg, env);
		ft_printf(2, "error\n");
		exit(0);
	}
	wait(0);
	free(arg[0]);
	free(arg);
}

static char	*get_path(void)
{
	char	*str;
	char	*ret;

	str = getcwd(NULL, 0);
	if (str == NULL)
		return (NULL);
	ret = ft_strjoin(str, "-$ ");
	if (ret == NULL)
		return (NULL);
	free(str);
	return (ret);
}

void	restore_fd(t_vars *va)
{
	dup2(va->fd[0], STDIN_FILENO);
	dup2(va->fd[1], STDOUT_FILENO);
	dup2(va->fd[2], STDERR_FILENO);
	close (va->fd[2]);
	close (va->fd[1]);
	close (va->fd[0]);
}

static char	*ft_init_read(t_vars *va)
{
	char	*str;

	va->fd[0] = dup(STDIN_FILENO);
	va->fd[1] = dup(STDOUT_FILENO);
	va->fd[2] = dup(STDERR_FILENO);
	signal(2, &handler);
	signal(SIGQUIT, SIG_IGN);
	va->current_path = get_path();
	str = readline(va->current_path);
	free(va->current_path);
	if (str == NULL)
		end_of_file(str, va);
	return (str);
}

int	main(int argc, char **argv, char **envp)
{
	static struct s_vars	va;
	t_list					*list;
	char					**tab;
	char					*str;

	tab = NULL;
	va.envi = set_env(&va, envp);
	init_terminal(argc, argv, va.envi);
	while (1)
	{
		str = ft_init_read(&va);
		list = NULL;
		make_list(&va, str, tab, &list);
		if (list)
		{
			if (open_files(&va, list) != -1)
				exec(&va, list);
			free_list(list);
		}
		restore_fd(&va);
	}
	return (0);
}
