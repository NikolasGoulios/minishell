#ifndef SEELA_H
# define SEELA_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include "libft/libft.h"

void	ft_command(char **envp, char *cmd);
void	ft_print_err(char *cmd, int c);
void	ft_free_array(char **array);
void	redirection_outfile_emptied(char *file);
void	redirection_infile(char *file);
void	redirection_outfile_append(char *file);
void    handle_heredoc(char *limiter);

#endif
