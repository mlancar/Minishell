#include "exec.h"

int	builtin_env(t_cmd *cmd, t_lst_env *env_list)
{
	if (cmd->argv[1])
	{
		if (its_option(cmd->argv))
			return (error("minishell: env: invalid option\n"), 1);
		return (error("minishell: env: invalid argument\n"), 1);
	}
	while (env_list)
	{
		ft_putstr_fd(env_list->line, cmd->fd.write);
		ft_putstr_fd("\n", cmd->fd.write);
		env_list = env_list->next;
	}
	return (1);
}
