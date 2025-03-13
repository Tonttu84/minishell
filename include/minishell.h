/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:39:37 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/13 16:45:41 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# ifndef MAX_VARS
#  define MAX_VARS (100)
# endif
# ifndef MAX_LENGTH
#  define MAX_LENGTH (400)
# endif
# include "../libft/libft.h"
# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# ifndef PATH_MAX			///Max path lenght
#  define PATH_MAX (500)
# endif
# define ENV_SIZE 4096
# ifndef MAX_SENT_SIZE
#  define MAX_SENT_SIZE (200)
# endif
# ifndef MAX_SENTENCES
#  define MAX_SENTENCES (50)
# endif

# ifndef USER
#  define USER minishell
# endif

# define PROMPT GREEN USER":"RESET

# define RED "\x1b[31m"
# define GREEN "\x1b[32m" // Used for variable expansion
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define WHITE "\x1b[37m"
# define BRIGHT_BLACK "\x1b[90m"
# define BRIGHT_RED "\x1b[91m"
# define BRIGHT_GREEN "\x1b[92m"
# define BRIGHT_YELLOW "\x1b[93m"
# define BRIGHT_BLUE "\x1b[94m"
# define BRIGHT_MAGENTA "\x1b[95m"
# define BRIGHT_CYAN "\x1b[96m"
# define BRIGHT_WHITE "\x1b[97m"
# define RESET "\x1b[0m"

const char		*token_to_string(t_token token);


typedef struct s_dir
{
	char 		*path;
	t_token		type;
	int			here_fd;
	
}	t_dir;

typedef struct s_sent
{
	char		*array[MAX_SENT_SIZE];
	bool		inpipe;
	t_dir		redirs[20];
	bool		outpipe;
	int			error; 			//error code here
	int			heredocs;
	int			argc;
}				t_sent;

typedef struct s_data
{
	char		**path;
	char		env[ENV_SIZE + 1][MAX_LENGTH + 1];
	int			env_count;
	t_list		tokens;
	t_sent		*page[MAX_SENT_SIZE];
	int			herecount;
	char		cwd[200];
}				t_data;

typedef struct s_point
{
	t_node		*node;
	int			start;
	int			end;
}				t_point;

/*
** BUILT' INS
 */
int builtin_cd(char *path);
void builtin_echo(char *str);
void builtin_pwd(void);
void builtin_exit(char *arg);
void builtin_env(t_data *data);
void builtin_export(t_data *data);


void			test(void);
typedef void	(*node_func)(t_list *list, t_node *node);
void			ft_exit(t_data *data, char *message, int exit_code);
void			*ft_xcalloc(size_t nmemb, size_t size);
size_t			ft_strlen(const char *s);
void			*ft_memset(void *s, int c, size_t n);
int				ft_isalpha(int c);
int				ft_isalnum(int c);
size_t			ft_wrdlen(t_char *str, t_data *data);
const char		*find_env(t_char *source, t_data *data);
void			create_list(t_data *data, t_char *line);
void			iterate_list(t_list *list, node_func func);
t_data			*get_data(void);
void			debug_print(t_char *array, t_data *data);
void			print_node(t_list *list, t_node *node);
size_t			ft_tcharlen(t_char *line);
t_node			*destroy_node(t_list *list, t_node *node);
int				copy_env_to_tchar(t_char *dst, int i, const char *env);
char			*cnvrt_to_char(t_char *line);
t_char			*lexify(char *line, t_data *data);
t_sent			**create_page(t_list *stack);
void			print_sentence(t_sent *sentence);
char		*create_heredoc(char *terminator, int expand);
char 			*test_infile(t_char *raw_path);
char 			*test_outfile(t_char *raw_path);
char 			*test_append(t_char *raw_path);
void 			prompt_input(void);
void  			add_redirection(t_node *node, t_sent *sentence, int i);
t_sent			*conv_linked_to_sentence(int i, int k, t_node *node, t_sent *sentence);
int				check_emp_arg(char *src, int i, t_char *dst, int *k);
void			remove_quotes(t_char *dst, char *src, int i, int k);
int 			execute(t_sent *sentence, int pfd[2], pid_t my_child, int state);
int				open_temp_heredocs(t_node *node, int expand);
void 			util_parse_args(t_data *data, int i);
int				cwd(void);
int 			run_builtin(int argc, char *argv[]);
int 			is_builtin(char *cmd);
int				bi_pwd(void);
int				bi_cd(int argc, char *argv[]);
void	bi_env(t_data *data);
int	bi_echo(int argc, char *argv[]);
int bi_unset(int argc, char *argv[]);
int	bi_export(int argc, char *argv[]);
const char	*ft_get_env(const char *target);
int	add_envvar(char env[ENV_SIZE + 1][MAX_LENGTH + 1], char *envvar, char *value);
const char	*find_env_char(char *source, t_data *data);
/*
** SIGNALS
 */
void block_signals_in_parent(void);
void set_signals(void);
void signal_handler(int sig_nbr);
void void_signal(int sig_nbr);
void unset_signals(void);
#endif
