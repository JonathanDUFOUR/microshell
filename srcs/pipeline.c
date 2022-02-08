/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 07:30:58 by jodufour          #+#    #+#             */
/*   Updated: 2022/02/08 09:30:25 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "microshell.h"

static int	__redirect(int const redirin, int const redirout)
{
	if (redirin != STDIN_FILENO && dup2(redirin, STDIN_FILENO) == -1)
		return (EXIT_FAILURE);
	if (redirout != STDOUT_FILENO && dup2(redirout, STDOUT_FILENO) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	__exec(char const **av, int *const tube, int const save,
	char const **ep)
{
	__pid_t	id;

	id = fork();
	if (id == -1)
		return (EXIT_FAILURE);
	else if (!id)
	{
		if (__redirect(save, tube[1]))
			return (EXIT_FAILURE);
		close(tube[0]);
		close(tube[1]);
		close(save);
		if (execve(av[0], (char *const *)av, (char *const *)ep))
			return (EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

static int	__exec_last(char const **av, int const save, char const **ep)
{
	__pid_t	id;

	id = fork();
	if (id == -1)
		return (EXIT_FAILURE);
	else if (!id)
	{
		if (__redirect(save, STDOUT_FILENO))
			return (EXIT_FAILURE);
		close(save);
		if (execve(av[0], (char *const *)av, (char *const *)ep))
			return (EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

static int	__wait_all(int i)
{
	while (i--)
		if (waitpid(0, NULL, 0) == -1)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	pipeline(char const **av, char const **ep)
{
	char const	**next;
	int			tube[2];
	int			save;
	int			i;

	save = dup(STDIN_FILENO);
	if (save == -1)
		return (EXIT_FAILURE);
	i = 0;
	while (*av)
	{
		++i;
		next = av;
		while (*next && strcmp(*next, "|"))
			++next;
		if (*next)
		{
			*next++ = NULL;
			if (pipe(tube) == -1
				|| __exec(av, tube, save, ep)
				|| dup2(tube[0], save) == -1)
				return (EXIT_FAILURE);
			close(tube[0]);
			close(tube[1]);
		}
		else if (__exec_last(av, save, ep))
			return (EXIT_FAILURE);
		av = next;
	}
	if ((dup2(save, STDIN_FILENO) | close(save)) == -1)
		return (__wait_all(i) | EXIT_FAILURE);
	return (__wait_all(i));
}
