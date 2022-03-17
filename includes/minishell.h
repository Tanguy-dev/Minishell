/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:35:33 by thamon            #+#    #+#             */
/*   Updated: 2022/03/17 19:00:41 by jusaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <fcntl.h>
# include <errno.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <sys/syslimits.h>
# include "../libft/includes/libft.h"
/* Pour Mac Ecole */
# include "../../../.brew/opt/readline/include/readline/readline.h"
# include "../../../.brew/opt/readline/include/readline/rlstdc.h"
# include "../../../.brew/opt/readline/include/readline/history.h"
/* Pour Mac Tanguy *//*
# include "/opt/homebrew/Cellar/readline/8.1.2/include/readline/readline.h"
# include "/opt/homebrew/Cellar/readline/8.1.2/include/readline/rlstdc.h"
# include "/opt/homebrew/Cellar/readline/8.1.2/include/readline/history.h"*/

# define PROMPT "👍 \033[0;32m\033[1mMinishell : \033[0m"
# define ERROR_PROMPT "👎 \033[0;32m\033[1mMinishell : \033[0m"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

/*
** TOKEN SEP
*/
# define EMPTY 0
# define CMD 1
# define ARG 2
# define PIPE 3
# define CHEVRON 4
# define OPEN_CHEVRON 5
# define DOUBLE_CHEVRON 6
# define DOUBLE_INPUT 8
# define END 7

# define BUF_SIZE 4096
# define EXPANSION -36

typedef struct s_expansion
{
	char				*str;
	int					i;
	int					j;
}				t_expansion;

typedef struct s_token
{
	char				*str;
	int					type;
	struct s_token		*next;
	struct s_token		*prev;
}				t_token;

typedef struct s_env
{
	char				*value;
	struct s_env		*next;
}				t_env;

typedef struct s_mini
{
	t_token				*token;
	t_env				*env;
	t_env				*export;
	int					exit;
	int					ret;
	int					in;
	int					out;
	int					fdin;
	int					fdout;
	int					pipin;
	int					pipout;
	int					pid;
	int					charge;
	int					parent;
	int					no_run;
	int					end;
	int					check;
}				t_mini;

typedef struct s_sig
{
	int					sigquit;
	int					sigint;
	int					exit_status;
	pid_t				pid;
}				t_sig;

/*
** SIGNAL
*/
void			sig_int(int a);
void			sig_quit(int a);
/*
** PARSING
*/
void			parse(t_mini *mini);
int				check_quote(t_mini *mini, char *line);
int				quote(char *line, int nb);
int				quote2(char *line, int nb, int i);
int				check_line(t_mini *mini, t_token *token);
int				is_sep(int i, char *line);
char			*find_lim(char *line, t_mini *mini, t_env *env);
int				ret_size(int ret);
int				get_arg_len(int pos, char *arg, t_env *env, int ret);
char			find_lim2(t_env *env, char *line, t_mini *mini, int i);
char			*lim_test(char *new, int j, char *line);
char			*line2(char *line, char *test, int i, int j);
char			dollar(char *line, int i, t_mini *mini);
int				quote_check(char *line, int i);
/*
** TOKEN
*/
t_token			*get_token(char *line);
void			token_type(t_token *token, int sep);
int				is_type(t_token *token, int type);
int				what_type(t_token *token, char *type);
t_token			*next_cmd(t_token *token, int i);
int				its_pipe(t_token *token);
t_token			*next_sep(t_token *token, int skip);
t_token			*prev_sep(t_token *token, int skip);
int				tk(char *line, int i);
char			token_test(char c, int *i, char *line);
/*
** ENV & EXPORT
*/
int				export_add(char *value, t_env *export);
int				check_double(char *arg, t_env *export);
int				set_env(t_mini *mini, char **env);
t_env			*set_export(char *value);
char			*env_on_str(t_env *env);
void			show_env(t_env *env, t_env *export);
int				is_valid_env(char *env);
char			*get_env_value(char *arg, t_env *env);
int				env_char(int c);
int				is_valid_arg(t_token *token);
void			multiple_arg(t_mini *mini);
char			*check_env(char *line);
int				export_search_destroy(char *cmp, t_mini *mini,
					t_env *tmp, t_env *tmp_2);
char			*strchr_ret(const char *str, char c);
int				in_export(char **args, t_mini *mini, int arg_nb);

/*
** FREE
*/
void			free_env(t_env *env);
void			free_all_export(t_env *export);
void			free_array(char **array);
void			free_token(t_token *token);
void			free_export(t_mini *mini, t_env *export);
int				last_export(t_mini *mini, t_env *export);
/*
** FD
*/
void			ft_close(int fd);
void			close_fd(t_mini *mini);
void			reset_fd(t_mini *mini);
void			reset_std(t_mini *mini);
/*
** EXEC
*/
void			exec_cmd(t_mini *mini, t_token *token);
int				exec_bin(char **args, t_mini *mini, t_env *env);
int				child2(int ret);
/*
** BUILTINS
*/
int				is_builtins(char *cmd);
int				exec_builtins(t_mini *mini, char **cmd);
int				env_add(char *value, t_env *env);
char			*name_env(char *dest, char *src);
int				in_env(char *args, t_env *env);
void			mini_exit(t_mini *mini, char **cmd);
int				mini_pwd(t_env *env);
int				mini_echo(char **args);
int				mini_env(t_env *env);
int				mini_cd(char **args, t_env *env);
int				mini_export(char **args, t_mini *mini, t_env *env, t_env *export);
char			*ex_arg(char **args, char *arg, int arg_nb);
int				exa(char **args, t_env *env, t_env *export);
int				unset_export(char **args, t_mini *mini, int arg);
int				mini_unset(char **args, t_mini *mini);
char			*get_path(t_env *env, char *var, size_t len);
char			*path2(char *env_path, t_env *env);
int				update_oldpath(t_env *env);
int				check_echo(char *line);
char			*remove_back(char *line);
int				remove_backk(char *line);
/*
** REDIR
*/
void			redir(t_mini *mini, t_token *token, int type);
void			open_chev(t_mini *mini, t_token *token);
int				pipee(t_mini *mini);
char			*expansion(char *arg, t_env *env, int ret);

extern t_sig	g_sig;

#endif
