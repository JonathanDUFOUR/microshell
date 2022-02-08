/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:03:13 by jodufour          #+#    #+#             */
/*   Updated: 2022/02/08 14:46:19 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static size_t	__strlen(char const *str)
{
	register char const	*ptr = str;

	while (*ptr)
		++ptr;
	return (ptr - str);
}

int	cd(char const **av)
{
	if (!av[1] || av[2])
		write(STDERR_FILENO, "error: cd: bad arguments\n", 25);
	else if (chdir(av[1]) == -1)
	{
		write(STDERR_FILENO, "error: cd: cannot change directory to ", 38);
		write(STDERR_FILENO, av[1], __strlen(av[1]));
		write(STDERR_FILENO, "\n", 1);
	}
	return (EXIT_SUCCESS);
}
