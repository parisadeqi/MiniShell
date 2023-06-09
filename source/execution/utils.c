/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 09:22:36 by svan-has      #+#    #+#                 */
/*   Updated: 2023/07/11 12:37:23 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	close_pipes_files(t_exec *data)
{
	int	i;

	i = 0;
	while (i < data->num_commands - 1)
	{
		close (data->pipe_fd[i][0]);
		close (data->pipe_fd[i][1]);
		i++;
	}
	if (data->infile && i == 0)
		close(data->fdin);
	if (data->outfile && i == data->num_commands - 1)
		close(data->fdout);
}

void	waitpid_forks(t_exec *data)
{
	int	i;

	i = 0;
	while (i < data->num_commands)
	{
		waitpid(data->fork_pid[i], &data->exit_status, 0);
		if (WIFEXITED(data->exit_status))
        	data->exit_status = WEXITSTATUS(data->exit_status);
		i++;
	}
}

void	create_pipes(t_exec *data, int num_commands)
{
	int	i;

	i = 0;
	while (i < num_commands)
	{
		if (i < num_commands - 1)
		{
			if (pipe(data->pipe_fd[i]) < 0)
				exit (1);
		}
		i++;
	}
}

char	**copy_environment_list(char **env)
{
	int			i;
	char		**new_environ;

	i = 0;
	while (env[i])
		i++;
	new_environ = null_check(malloc ((i + 1) * sizeof (char *)));
	i = 0;
	while (env[i])
	{
		new_environ[i] = null_check(ft_strdup(env[i]));
		i++;
	}
	new_environ[i] = NULL;
	return (new_environ);
}

int	array_size(char **array)
{
	int	count;

	if (!array)
		return (-1);
	count = 0;
	int i = 0;
	while(array[i])
		i++;
	while (array[count])
		count++;
	return (count);
}
