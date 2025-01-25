#include "seela.h"

void    initialize_struct(char **envp)
{
    t_ms ms;

    ms.exit_status = 0;
    ms.envp = copy_map(envp);
    ms.exported = copy_map(envp);
}   
