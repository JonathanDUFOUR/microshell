/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:29:16 by jodufour          #+#    #+#             */
/*   Updated: 2022/02/08 14:38:17 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "microshell.h"

static size_t	__strlen(char const *str)
{
	register char const	*ptr = str;

	while (*ptr)
		++ptr;
	return (ptr - str);
}

int	exec(char const **av, char const **ep, int const save,
	int const *const tube)
{
	__pid_t const	id = fork();

	if (id == -1)
		return (EXIT_FAILURE);
	else if (!id)
	{
		if (redirect(save, tube[1]))
			return (EXIT_FAILURE);
		if (tube[0] != STDIN_FILENO)
			close(tube[0]);
		if (tube[1] != STDOUT_FILENO)
			close(tube[1]);
		close(save);
		if (execve(av[0], (char *const *)av, (char *const *)ep))
		{
			write(STDERR_FILENO, "error: cannot execute ", 22);
			write(STDERR_FILENO, av[0], __strlen(av[0]));
			write(STDERR_FILENO, "\n", 1);
		}
		exit(EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
