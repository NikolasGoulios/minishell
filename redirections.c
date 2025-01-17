/*
HANDLNG REDIRECTIONS:

HEREDOC/<< :
Works like this: << LIMITER (writes to temp_fd until LIMITER is written to terminal, then temp_fd becomes STDIN)
Function that handles this: handle_heredoc(char *limiter) takes the limiter as parameter
stops writing to file when the LIMITER is written to terminal

< :
Works like this: < infile (infile BECOMES STDIN)
Function that handles this: redirection_infile(char *file)
takes the file that we want to change to STDIN as parameter

> :
Works like this: > outfile (outfile becomes STDOUT)
Function that handles this: redirection_outfile_emptied(char *file)
Takes the file that we want to change to STDIN as parameter. 
Empties the file if it exists, else creates one with correct permissions

>> : 
Works like this: >> outfile (outfile becomes STDOUT)
Function that handles this: redirection_outfile_append(char *file)
Takes the file that we want to change to STDIN as parameter. 
Writes to the endoffile,if file does not exist, creates one with correct permissions

****FOR EXAMPLE****
> infile cat | "ls -la" | "grep error" >> outfile

BASICALLY IDEA IS (what i think we should maybe do, if im correct)
1. FIRST CALL FOR REDIRECTION_INFILE() WITH INFILE
2. SECOND CALL REDIRECTION_OUTFILE_APPEND() WITH INFILE
3. THEN CALL FOR FT_PIPE() WITH (3=cmd_amount, CMD_ARRAY, ENVP)
CMD_ARRAY[0] = "CAT", CMD_ARRAY[1] = "LS -LA", CMD_ARRAY[2] = "GREP ERROR", CMD_ARRAY[3] = NULL;

*/

#include "seela.h"

void handle_heredoc(char *limiter)
{
    char    buffer[1024];
    size_t  len;
    ssize_t bytes_read;
    int     temp_fd;

    len = 0;
    temp_fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (temp_fd < 0)
        exit(1);
    while (1)
    {
        write(STDOUT_FILENO, "heredoc> ", 9);
        len = 0;
        bytes_read = read(STDIN_FILENO, buffer + len, 1);
        while (bytes_read > 0)
        {
            if (buffer[len] == '\n')
            {
                buffer[len] = '\0';
                break;
            }
            len++;
            bytes_read = read(STDIN_FILENO, buffer + len, 1);
        }
        if (bytes_read < 0)
            exit(1);
        if (ft_strcmp(buffer, limiter) == 0)
            break;
        write(temp_fd, buffer, len);
        write(temp_fd, "\n", 1);
    }
    close(temp_fd);
}

static void	check_access(char *checking, int c)
{
	if (c == 1)
	{
		if (access(checking, F_OK) == -1)
		{
			ft_printf("zsh: No such file or directory: %s\n", checking);
			exit(0);
		}
		if (access(checking, R_OK) == -1)
		{
			ft_printf("zsh: Permission denied: %s\n", checking);
			exit(0);
		}
	}
	else
	{
		if (access(checking, W_OK) == -1)
		{
			ft_printf("zsh: Permission denied: %s\n", checking);
			exit(1);
		}
	}
}

void	redirection_outfile_append(char *file)
{
	int		file2;

	file2 = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file2 < 0)
		exit(1);
	check_access(file, 0);
    if (dup2(file2, STDOUT_FILENO) == -1)
    {
        close(file2);
        exit(1);
    }
    close(file2);
}

void	redirection_infile(char *file)
{
	int		file1;

	check_access(file, 1);	
	file1 = open(file, O_RDONLY);
    if (file1 < 0)
	    exit(1);
    if (dup2(file1, STDIN_FILENO) == -1)
    {
        close(file1);
        exit(1);
    }
    close(file1);
}

void	redirection_outfile_emptied(char *file)
{
	int		file2;

	file2 = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file2 < 0)
		exit(1);
	check_access(file, 0);
    if (dup2(file2, STDOUT_FILENO) == -1)
    {
        close(file2);
        exit(1);
    }
    close(file2);
}

