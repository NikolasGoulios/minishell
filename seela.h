#ifndef SEELA_H
# define SEELA_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include "libft/libft.h"

typedef struct s_ms
{
    int     exit_status; // Store the last exit status
    char    **envp;     // Environment variables
    char    **exported;
} t_ms;

char	**copy_map(char **original_map);
void	ft_command(char **envp, char *cmd);
void    initialize_struct(char **envp);
void	ft_print_err(char *cmd, int c);
void	ft_free_array(char **array);
void    ft_pipe(int num_cmds, char **argv, t_ms *ms);
void	redirection_outfile_emptied(char *file);
void	redirection_infile(char *file);
void	redirection_outfile_append(char *file);
void    handle_heredoc(char *limiter);

#endif
