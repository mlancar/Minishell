
#include "pipex.h"

void	one_cmd(t_lst_cmd *argv, t_cmd *cmd, t_lst_env **env_list)
{
	//printf("\n one cmd : read = %d, write = %d, close = %d\n", cmd->fd.read, cmd->fd.write, cmd->fd.close);
	if (cmd->pid[cmd->index_pid] == 0)
	{
		if (dup2(cmd->fd.read, 0) != -1)
		{
			if (check_command(argv, cmd, env_list) == 0)
				error_access_cmd(cmd);
			check_close(cmd->fd.read);
			if (execve(cmd->path, cmd->argv, cmd->env))
				error_cmd(0, cmd);
		}
		else
			error_cmd(0, cmd);
	}
	check_close(cmd->fd.read);
	check_close(cmd->fd.write);
}

void	exec_one_cmd(t_lst_cmd *argv, t_cmd *cmd, t_lst_env **env_list)
{
	cmd->argv = convert_list(argv);
	cmd->fd.read = 0;
	cmd->fd.write = 1;
	cmd->fd.close = -1;
	set_files(argv, cmd);
	cmd->pid[cmd->index_pid] = fork();
	if (cmd->pid[cmd->index_pid] < 0)
		free_and_exit("fork", cmd);
	one_cmd(argv, cmd, env_list);
}

void	close_fd_child(t_lst_cmd *argv, t_cmd *cmd)
{
	(void)argv;
	//dprintf(2, "\n cmd%d : child : read = %d, write = %d, close = %d\n", cmd->index_pid, cmd->fd.read, cmd->fd.write, cmd->fd.close);
	if (cmd->index_pid == cmd->last)
		check_close(cmd->fd.read);
	else
	{
		//dprintf(2, "cmd%dICI LA\n", cmd->index_pid);
		check_close(cmd->fd.write);
		check_close(cmd->fd.read);
		check_close(cmd->fd.close);
	}
}

void	close_fd_parent(t_lst_cmd *argv, t_cmd *cmd)
{
	(void)argv;
	//printf("\nparent : read = %d, write = %d, close = %d\n", cmd->fd.read, cmd->fd.write, cmd->fd.close);
	if (cmd->index_pid == cmd->last)
	{
		check_close(cmd->fd.read);
		check_close(cmd->fd.write);
		check_close(cmd->fd.close);
	}
	else
	{
		check_close(cmd->fd.read);
		check_close(cmd->fd.write);
	}
}


void	new_exec_cmds(t_lst_cmd *argv, t_cmd *cmd, t_lst_env **env_list)
{
	set_fd(cmd);
	set_files(argv, cmd);
	//printf("read = %d, write = %d, close = %d\n", cmd->fd.read, cmd->fd.write, cmd->fd.close);
	cmd->pid[cmd->index_pid] = fork();
	if (cmd->pid[cmd->index_pid] < 0)
		free_and_exit("fork", cmd);
	if (cmd->pid[cmd->index_pid] == 0)
	{
		if ((dup2(cmd->fd.read, 0) != -1) && (dup2(cmd->fd.write, 1) != -1))
		{
			if (check_command(argv, cmd, env_list) == 0)
				error_access_cmd(cmd);
			close_fd_child(argv, cmd);
			if (execve(cmd->path, cmd->argv, cmd->env))
				error_cmd(0, cmd);
		}
		else
			error_cmd(0, cmd);
	}
	else
		close_fd_parent(argv, cmd);
}

void	pipex(t_lst_cmd *argv, t_cmd *cmd, t_lst_env **env_list)
{
	if (cmd->index_pid == cmd->nbr - 1)
		exec_one_cmd(argv, cmd, env_list);
	else
	{
		if (pipe(cmd->fd.pipe) == -1)
			free_and_exit("pipe", cmd);
		while (cmd->index_pid < cmd->nbr)
		{
			cmd->argv = convert_list(argv);
			cmd->fd.previous = cmd->fd.pipe[0];
			if ((cmd->index_pid != cmd->first)
				&& (cmd->index_pid != cmd->last))
			{
			if (pipe(cmd->fd.pipe) == -1)
				free_and_exit("pipe", cmd);
			}
			new_exec_cmds(argv, cmd, env_list);
			cmd->index++;
			cmd->index_pid++;
			if (argv != NULL)
				argv = argv->next;
		}
	}
}

//printf("name = %s\n", cmd->name[0]);
// if (cmd->if_here_doc == 1)
// {
// 	here_doc(cmd->argv[2], cmd);
// 	exec_argv(argv, cmd->fd_tmp, cmd->fd[1], cmd->fd[0], cmd);
// 	unlink(cmd->rand_name);
// }