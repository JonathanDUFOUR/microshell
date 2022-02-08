/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 07:04:01 by jodufour          #+#    #+#             */
/*   Updated: 2022/02/08 16:28:19 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "microshell.h"

int	main(int const ac __attribute__((unused)), char const **av, char const **ep)
{
	char const	**next;

	++av;
	while (*av && !strcmp(*av, ";"))
		++av;
	while (*av)
	{
		next = av;
		while (*next && strcmp(*next, ";"))
			++next;
		if (*next)
		{
			*next++ = NULL;
			while (*next && !strcmp(*next, ";"))
				++next;
		}
		if ((!strcmp(*av, "cd") && cd(av))
			|| (strcmp(*av, "cd") && pipeline(av, ep)))
		{
			write(STDERR_FILENO, "error: fatal\n", 13);
			return (EXIT_FAILURE);
		}
		av = next;
	}
	return (EXIT_SUCCESS);
}
