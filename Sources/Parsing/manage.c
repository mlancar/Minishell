#include "minishell.h"
#include "pipex.h"

int	init_lst(t_lst_cmd **cmd)
{
	t_lst_cmd	*lst_new;

	lst_new = NULL;
	lst_new = ft_lst_new_cmd();
	if (!lst_new)
		return (0);
	ft_lst_add_back_cmd(lst_new, cmd);
	return (1);
}

void	test_pipex(t_lst_cmd *cmd, char **env, t_lst_env *lst_env)
{
	int	i;
	int	y;
	int	x;

	(void) env;
	(void) lst_env;
	i = 1;
	y = 1;
	x = 1;
	while (cmd != NULL)
	{
		printf("_______________________\n");
		printf("Maillon numero %d cmd\n\n", i);
		while (cmd->arg != NULL)
		{
			printf("Maillon numero %d arg\n\n", y);
			printf("name = %s\n", cmd->arg->name);
			printf("arg = %s\n", cmd->arg->arg);
			cmd->arg = cmd->arg->next;
			y++;
		}
		while (cmd->file != NULL)
		{
			printf("Maillon numero %d file\n\n", x);
			printf("infile = %s\n", cmd->file->infile);
			printf("outfile = %s\n", cmd->file->outfile);
			printf("outfile_type = %d\n", cmd->file->outfile_type);
			printf("limiter = %s\n", cmd->file->limiter);
			cmd->file = cmd->file->next;
			x++;
		}
		cmd = cmd->next;
		i++;
		y = 1;
		x = 1;
	}
}

void	manage(char *prompt, char **env, t_lst_env **lst_env)
{
	t_lst_cmd	*cmd;

	cmd = NULL;
	if (!check_prompt(prompt, cmd))
		return ;
	if (!init_lst(&cmd))
		return ;
	if (!fill_lst(prompt, cmd, *lst_env))
		return (free_all(&cmd));
	//test_pipex(cmd, env, *lst_env);
	main_exec(cmd, env, lst_env); 
	free_all(&cmd);
	return ;
}
