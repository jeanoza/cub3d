/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:15:07 by kychoi            #+#    #+#             */
/*   Updated: 2022/06/16 15:04:08 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED "\033[0;31m"
# define GRN "\033[0;32m"
# define YEL "\033[0;33m"
# define BLU "\033[0;34m"
# define MAG "\033[0;35m" //purple
# define CYN "\033[0;36m" //emerald
# define WHT "\033[0;37m"
# define DFT "\033[0m"

# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>

# include <dirent.h> 
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

# include <readline/readline.h>
# include <readline/history.h>

/* libft */
# include "../libft/libft.h"

# define CHAR_FORBIDDEN ";\\"
# define CHAR_OP "><|"

/* Pointer size */
# define P_SIZE 8

/* Non-printable */
# define M_SPACE -32
# define M_QUOTE_D -34
# define M_QUOTE_S -39

extern int	g_exit_status;

typedef enum e_op { NONE, IN, HEREDOC, OUT, APPEND }	t_op;

typedef struct s_redir {
	t_op	op;
	int		fdin;
	int		savein;
	int		saveout;
	int		fdout;
	char	*file;
}		t_redir;

typedef struct s_cmd {
	char			*name;
	char			**args;
	char			**envp;
	t_redir			**redirs;
	int				pid;
	int				exit;
}	t_cmd;

/* maxbon_shell.c */
void	put_header(void);
void	print_res_parsing(t_cmd **cmds);

/* signal.c */
void	add_signal_listener(void);
/* parsing/parse.c */
t_cmd	**parse(char *line, char **envp);
/* parsing/error_op.c */
int		err_forbidden_char(char *line, char *e_char);
int		err_end_by_op(char *line, char *e_char);
int		err_multiple_op(char *line, char *e_char);
int		err_space_btw_op(char *line, char *e_char, int i);
int		err_mix_op(char *line, char *e_char);
/* parsing/error_quote.c */
int		err_quote(char *line);
int		err_pipe(char *line, char *e_char);
/* parsing/getter_cmd.c */
void	get_op(t_cmd *cmd, char *str);
void	get_name(t_cmd *cmd, char *str);
/* parsing/init_cmd.c */
t_cmd	**init_cmd_array(char *line, char **envp);

/* parsing/manage_line.c */
char	*manage_quote_dollar(char *str, char **envp, char ***strsp, int idx);

/* utils.c */
int		count_el(void **_2d_array);
int		contains(const char *charset, char c);
int		is_redir_op(char c);
void	free_2d_array(void **_2d_array);
void	merci_encore_norm(char **strp, char *left, char *right);

/* exec.c */
void	simple_cmd(t_cmd *cmd, t_cmd **all);
void	exec_command(t_cmd **all_cmds);

/* exec_ve.c */
void	exec_ve(char *cmd, char **envp, t_cmd *c);

/* pipe.c */
int		exec_pipe(t_cmd **cmd, int cmd_nbr);

/* redir.c, reset_redir.c*/
void	redir(t_cmd *cmd);
void	reset_stdin(t_cmd *cmd, int index);
void	reset_redir(t_cmd *cmd);
int		open_all_fd(t_cmd *cmd);
int		get_last_out(t_cmd *cmd);
int		get_last_in(t_cmd *cmd);
void	close_all_prev_fd(t_cmd *cmd);
void	ask_all_heredoc(t_cmd *cmd);
void	ask_pipe_heredoc(t_cmd **cmd);
void	close_all_heredoc(t_cmd *cmd);
void	close_allcmds_heredoc(t_cmd **cmd);

/* env_utils.c */
void	print_env(char **s);
void	realloc_env(char ***envp);
int		get_env_index(char **envp, char *s);
char	*get_env(char **envp, char *s);
char	*spec_get_env(char **envp, char *s);
void	realloc_env(char ***envp);

/* builtins */
int		do_cd(t_cmd *cmd);
int		do_export(t_cmd *cmd);
int		do_unset(t_cmd *cmd);
int		do_echo(t_cmd *cmd);
int		do_pwd(void);
int		do_env(t_cmd *cmd);
int		do_exit(t_cmd *cmd, t_cmd **all);
void	exec_builtins(t_cmd *cmd, t_cmd **all);
int		is_builtin(char *s);

/* free.c */
void	free_cmd(t_cmd *cmd);
void	free_all_cmd(t_cmd **all);
void	free_all(t_cmd **cmd);

/* error.c */
void	exit_error(void);
int		ret_error(char *s);

/* exec/lib */
void	*ft_free_split(char **d);
char	**ft_quote_split(char const *s, char c);

#endif
