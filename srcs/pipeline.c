/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 07:30:58 by jodufour          #+#    #+#             */
/*   Updated: 2022/02/08 16:10:57 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "microshell.h"

static int	__to_pipe(char const **av, char const **ep, int const save)
{
	int	tube[2];

	if (pipe(tube)
		|| exec(av, ep, save, tube)
		|| (dup2(tube[0], save) | close(tube[0]) | close(tube[1])) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	__to_term(char const **av, char const **ep, int const save)
{
	if (exec(av, ep, save, (int const []){STDIN_FILENO, STDOUT_FILENO}) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	__end(int const save, int child_count)
{
	while (child_count--)
		if (waitpid(0, NULL, 0) == -1)
			return (EXIT_FAILURE);
	if ((dup2(save, STDIN_FILENO) | close(save)) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	pipeline(char const **av, char const **ep)
{
	char const	**next;
	int const	save = dup(STDIN_FILENO);
	int			child_count;

	if (save == -1)
		return (EXIT_FAILURE);
	child_count = 0;
	while (*av)
	{
		++child_count;
		next = av;
		while (*next && strcmp(*next, "|"))
			++next;
		if (*next)
		{
			*next++ = NULL;
			if (__to_pipe(av, ep, save))
				return (EXIT_FAILURE);
		}
		else if (!*next && __to_term(av, ep, save))
			return (EXIT_FAILURE);
		av = next;
	}
	return (__end(save, child_count));
}
