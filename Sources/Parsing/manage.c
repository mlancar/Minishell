#include "minishell.h"
#include "pipex.h"

int	init_lst(t_lst_cmd **argv)
{
	t_lst_cmd	*lst_new;

	lst_new = NULL;
	lst_new = ft_lst_new_cmd();
	if (!lst_new)
		return (0);
	ft_lst_add_back_cmd(lst_new, argv);
	return (1);
}

void	test_pipex(t_lst_cmd *argv, char **env)
{
	int	i;
	int	y;
	int	x;

	(void) env;
	i = 1;
	y = 1;
	x = 1;
	while (argv != NULL)
	{
		printf("_______________________\n");
		printf("Maillon numero %d argv\n\n", i);
		while (argv->info != NULL)
		{
			printf("Maillon numero %d arg\n\n", y);
			printf("name = %s\n", argv->info->name);
			printf("arg = %s\n", argv->info->arg);
			argv->info = argv->info->next;
			y++;
		}
		while (argv->file != NULL)
		{
			printf("Maillon numero %d file\n\n", x);
			printf("infile = %s\n", argv->file->infile);
			printf("outfile = %s\n", argv->file->outfile);
			printf("outfile_type = %d\n", argv->file->outfile_type);
			printf("limiter = %s\n", argv->file->limiter);
			argv->file = argv->file->next;
			x++;
		}
		argv = argv->next;
		i++;
		y = 1;
		x = 1;
	}
}

int	manage(char *prompt, char **env)
{
	t_lst_cmd	*argv;

	(void) env;
	argv = NULL;
	if (!check_prompt(prompt, argv))
		return (1);
	if (!init_lst(&argv))
		return (0);
	if (!fill_lst(prompt, argv) && argv)
		return (1);
	//test_pipex(argv, env);
	main_pipex(argv, env);
	//PAS OUBLIER DE FREE
	return (1);
}
