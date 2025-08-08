/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:52:31 by tdenis            #+#    #+#             */
/*   Updated: 2025/07/28 19:21:40 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../big_ft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <fcntl.h>
# define O_TMPFILE 0x410000
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

extern int	g_signal;

typedef enum e_token
{
	DOUBLE_QUOTE,
	SIMPLE_QUOTE,
	PIPE,
	WORD,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	SPACES,
	PARENTHESIS,
}		t_token;

typedef struct s_vars
{
	char	**envi;
	int		*pid;
	int		watatus;
	int		last_code;
	char	*current_path;
	int		pipe1[2];
	int		pipe2[2];
	int		fd[3];
}	t_vars;

typedef struct s_list
{
	char			*com;
	char			**arguments;
	char			**infile;
	char			**outfile;
	int				fd_in;
	int				fd_out;
	struct s_list	*prev;
	struct s_list	*next;
}		t_list;

// Command name
// Array of strings (arguments)
// Array of strings (input file paths)
// Array of strings (output file paths)
// Open file descriptor (infile)
// Open file descriptor (outfile)
// Previous command in list
// Next command in list

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- free/close/print/debug

int		ft_free(void *str);
void	close_list(t_list *list);
int		free_tab(char **tab);
int		print_tab(char **arg_list);
void	free_cmds(char ***commands);
void	close_fd(t_vars *va);
void	free_list(t_list *list);
int		find_str(const char *big, const char *cute, int len);
void	free_end(t_vars *va, t_list *list);
void	close_files(int *files);
// void	print_list(t_list *list);

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- pipex

void	exec(t_vars *va, t_list *list);
int		pipex(t_vars *va, t_list *list);
int		check_path(t_vars *va, t_list *list);
void	com_looop(t_vars *va, t_list *list);
void	single_com(t_vars *va, t_list *list);

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- dup pipex

void	restore_fd(t_vars *va);
int		check_dir(t_vars *va, char *commande);
int		make_dup(t_vars *va, t_list *list);
int		dup_in(t_vars *va, t_list *list);
int		dup_out(t_vars *va, t_list *list);
int		check_in_access(t_vars *va, char *str);
int		check_out_access(t_vars *va, char *str);
int		check_infile(t_vars *va, char **in_tab);
int		check_outfile(t_vars *va, char **out_tab);
int		open_files(t_vars *va, t_list *list);
int		open_infile(t_vars *va, t_list *list);
int		open_outfile(t_list *list);
int		heredoc(t_vars *va, t_list *list, char *file);

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- set_list

int		count_in(char *str);
int		count_out(char *str);
char	*catch_word(char *str);
t_list	*new_node(t_list *list);
t_list	*prev_node(t_list *list);
t_list	*next_node(t_list *list);
t_list	*set_list(t_vars *va, t_list *list, char *str);
int		fill_list(t_vars *va, t_list *list, char *str);
int		set_infile(t_vars *va, t_list *list, char *str);
int		set_outfile(t_vars *va, t_list *list, char *str);
int		set_evar(t_vars *va, t_list *list, char *str);
int		set_arg(t_vars *va, t_list *list, char *str);

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- built in

int		built_in(t_vars *va, t_list *list);
char	**export1(t_vars *va, char **tab, char **env);
char	**export_1a(t_vars *va, int i, char **arguments, char **new);
char	**export2(char *var, char *arg, char **env);
char	*get_evar(t_vars *va, char *var);
char	**ft_unset(char **arg, char **env);
int		ft_cd(t_vars *va, char **arguments);
int		ft_echo(t_vars *va, char **arguments);
int		ft_exit(t_vars *va, t_list *list);
int		ft_pwd(t_vars *va);

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- random

int		while_alphanum(char *str);
int		ft_printf(int fd, const char *s, ...);
char	*get_file(char *str);
char	*ft_trim(char *str);
int		chain_len(t_list *list);
int		tab_len(char **tab);
void	tab_cmds(t_vars *va, char *str);
void	clean_ter(char **env);
int		print_hex(t_vars *va);
char	**copy_tab(char **tab);
void	handler(int signal);
int		ft_strcmp(char *src, char *dest);
char	**set_env(t_vars *va, char **env);

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-  signaux

void	handle_sigint(int sig);
void	end_of_file(char *str, t_vars *va);
void	end_heredoc(int signal);
void	handler(int signal);

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-  parsing

int		syntaxerror(char *input);
int		checkquotes(char *input);
int		errorpipe(char *input);
int		errorchevron(char *input);
int		errorchevron2(char *input);
char	**split_words(char *input);
char	**split_cmd(char *input);
char	*espacerchevrons(char *input);
int		skip_quotes(char *input);
t_list	*initiate_node(char *command_str);
void	chevrons(char **input, char **result, int *i, int *j);
char	*copyfile(char *src, char *src2);
char	*ft_unquote(t_vars *va, char *str);
void	make_list(t_vars *va, char *input, char **splitpipe, t_list **current);
void	copyinfile(t_list **node, int *idx);
void	copyoutfile(t_list **node, int *idx);
void	clean_files(t_vars *va, t_list **node);
void	clean_args(t_list **node);
char	*clean_string(t_vars *va, char *str);
int		count_splited_words(char *input);
char	*mallocaword(char const *str, int start, int end);

#endif
