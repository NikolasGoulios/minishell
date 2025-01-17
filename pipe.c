/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalorin <ssalorin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:32:44 by ssalorin          #+#    #+#             */
/*   Updated: 2025/01/15 15:53:31 by ssalorin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Idea is to replicate the functionality of Unix pipes,
where commands are chained together with |, passing the output of one command as input to the next
ft_ppe function takes command amount, commands as **array and envp as arguments
EXAMPLE:if you need it to work like ls -l | grep "Error" | sort
send these as arguments to ft_pipe
int num_cmds = 3;
char **cmds = cmds[0]="ls -l", cmds[1] ="grep Error", cmds[2] ="sort", cmds[3]=NULL
char **envp = environmental variables

FUNCTIONALITY:
Creates pipes and forks child processes for each command.
Fork splits the process to child and parent process, child processes execute the commands,
The parent process waits for all the child processes to complete.
Pipe makes the pipe.
Pipe allows fle descriptors to communicate.
A process writes data to the pipe_fd's write-end (pipe_fd[1]),
which can then be read by another process from the pipe_fd's read-end (pipe_fd[0].
In a typical shell pipeline (e.g., cmd1 | cmd2):
The output of cmd1 is sent to cmd2 through a pipe.
cmd1 writes its output to the write end of the pipe.
cmd2 reads from the read end of the pipe.
*/

#include "seela.h"

static void	ft_child_process(int *prev_pipe, int *next_pipe, char *cmd, char **envp)
{
	if (prev_pipe)
	{
		if (dup2(prev_pipe[0], STDIN_FILENO) == -1) //It duplicates previous pipes read-end to stadard input
			exit(1);
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	if (next_pipe)
	{
		if (dup2(next_pipe[1], STDOUT_FILENO) == -1) //It duplicates the next pipes write-end to standard output
			exit(1);
		close(next_pipe[0]);
		close(next_pipe[1]);
	}
	ft_command(envp, cmd); //execute command
}

void	ft_pipe(int num_cmds, char **cmds, char **envp)
{
	int		pipe_fd[num_cmds - 1][2];
	int		i;
	pid_t	pid;
    pid_t   last_pid;
    pid_t   wpid;
    int     status;
    int     exit_status;

    i = 0;
    last_pid = -1;
	exit_status = 0;
	while (i < num_cmds)
	{
		if (i < num_cmds - 1)
		{
			if (pipe(pipe_fd[i]) == -1)
		        	exit(1);
		}
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0) // Child process
		{
			if (i == 0) // first command
				ft_child_process(NULL, pipe_fd[i], cmds[i], envp);
			else if (i == num_cmds - 1) // last command
				ft_child_process(pipe_fd[i - 1], NULL, cmds[i], envp);
			else //any commands in between
				ft_child_process(pipe_fd[i - 1], pipe_fd[i], cmds[i], envp);
		}
		if (i > 0)
		{
			close(pipe_fd[i - 1][0]);
			close(pipe_fd[i - 1][1]);
		}
        last_pid = pid;
		i++;
	}
	i = 0;
	while (i < num_cmds - 1)
	{
		close(pipe_fd[i][0]);
 		close(pipe_fd[i][1]);
		i++;
	}
	i = 0;
	while (i < num_cmds)
	{
        wpid = wait(&status);
		if (wpid == last_pid && WIFEXITED(status))
        {
            exit_status = WEXITSTATUS(status);
            exit(exit_status);
        }
		i++;
	}
}
