
#include "pipex.h"

void	one_cmd(t_lst_argv *argv, t_cmd *cmd)
{
	//printf("\n one cmd : read = %d, write = %d, close = %d\n", cmd->fd.read, cmd->fd.write, cmd->fd.close);
	if (cmd->pid[cmd->index_pid] == 0)
	{
		if (check_command(argv, cmd) == 0)
			error_access_cmd(cmd);
		if (dup2(cmd->fd.read, 0) != -1)
		{
			if (check_command(argv, cmd) == 0)
				error_access_cmd(cmd);
			check_close(cmd->fd.read);
			if (execve(cmd->path, cmd->argv, cmd->envp))
				error_cmd(0, cmd);
		}
		else
			error_cmd(0, cmd);
	}
	check_close(cmd->fd.read);
	check_close(cmd->fd.write);
}

void	exec_one_cmd(t_lst_argv *argv, t_cmd *cmd)
{
	cmd->argv = convert_list(argv);
	cmd->fd.read = 0;
	cmd->fd.write = 1;
	cmd->fd.close = -1;
	set_files(argv, cmd);
	cmd->pid[cmd->index_pid] = fork();
	if (cmd->pid[cmd->index_pid] < 0)
		free_and_exit("fork", cmd);
	one_cmd(argv, cmd);
}

void	close_fd_child(t_lst_argv *argv, t_cmd *cmd)
{
	(void)argv;
	dprintf(2, "\n cmd%d : child : read = %d, write = %d, close = %d\n", cmd->index_pid, cmd->fd.read, cmd->fd.write, cmd->fd.close);
	if (cmd->index_pid == cmd->last)
		check_close(cmd->fd.read);
	else
	{
		dprintf(2, "cmd%dICI LA\n", cmd->index_pid);
		check_close(cmd->fd.write);
		check_close(cmd->fd.read);
		check_close(cmd->fd.close);
	}
}

void	close_fd_parent(t_lst_argv *argv, t_cmd *cmd)
{
	(void)argv;
	printf("\nparent : read = %d, write = %d, close = %d\n", cmd->fd.read, cmd->fd.write, cmd->fd.close);
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


void	new_exec_cmds(t_lst_argv *argv, t_cmd *cmd)
{
	set_fd(cmd);
	set_files(argv, cmd);
	printf("read = %d, write = %d, close = %d\n", cmd->fd.read, cmd->fd.write, cmd->fd.close);
	cmd->pid[cmd->index_pid] = fork();
	if (cmd->pid[cmd->index_pid] < 0)
		free_and_exit("fork", cmd);
	if (cmd->pid[cmd->index_pid] == 0)
	{
		if ((dup2(cmd->fd.read, 0) != -1) && (dup2(cmd->fd.write, 1) != -1))
		{
			if (check_command(argv, cmd) == 0)
				error_access_cmd(cmd);
			close_fd_child(argv, cmd);
			if (execve(cmd->path, cmd->argv, cmd->envp))
				error_cmd(0, cmd);
		}
		else
			error_cmd(0, cmd);
	}
	else
		close_fd_parent(argv, cmd);
}

void	pipex(t_lst_argv *argv, t_cmd *cmd)
{
	if (cmd->index_pid == cmd->nbr - 1)
		exec_one_cmd(argv, cmd);
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
			new_exec_cmds(argv, cmd);
			cmd->index++;
			cmd->index_pid++;
			if (argv != NULL)
				argv = argv->next;
		}
	}
}