#include "seela.h"

void    initialize_struct(char **envp)
{
    t_minishell minishell;

    minishell.exit_status = 0;
    minishell.envp = envp;
}   
