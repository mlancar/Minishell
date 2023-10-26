#include "pipex.h"
#include "minishell.h"

int	check_builtins(t_cmd *cmd)
{
	if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "echo"))
		return (1);
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "pwd"))
		return (1);
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "export"))
		return (1);
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "env"))
		return (1);
	else
		return (0);
}

int	exec_builtins(t_cmd *cmd, t_struct_env *s)
{
	if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "echo"))
		g_exit = builtins_echo(cmd);
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "pwd"))
		g_exit = builtins_pwd(cmd);
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "export"))
		g_exit = builtins_export(cmd->argv, s);
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "env"))
		g_exit = builtins_env(cmd, s->lst_env);
	else
		return (0);
	return (1);
}
