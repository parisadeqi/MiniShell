/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 09:47:29 by svan-has      #+#    #+#                 */
/*   Updated: 2023/08/08 16:24:32 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_newline(char **cmd_table, int arguments)
{
	if (arguments >= 2 && !ft_strncmp(cmd_table[1], "-n", 2))
		return (1);
	else
		return (0);
}

int	echo_builtin(char **cmd_table)
{
	int	i;
	int	arguments;
	int	new_line;

	arguments = array_size(cmd_table);
	new_line = check_newline(cmd_table, arguments);
	i = 1 + new_line;
	while (i < arguments)
	{
		if (printf("%s", cmd_table[i]) < 0)
			return (1);
		if (cmd_table[i + 1] && printf(" ") < 0)
			return (1);
		i++;
	}
	if (!new_line && printf("\n") < 0)
		return (1);
	return (0);
}
