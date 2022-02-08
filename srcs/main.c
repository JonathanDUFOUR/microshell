/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 07:04:01 by jodufour          #+#    #+#             */
/*   Updated: 2022/02/08 09:30:15 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "microshell.h"

static int	__usage_err(void)
{
	write(STDERR_FILENO, "Error: wrong usage\n", 19);
	write(STDERR_FILENO, "Usage: ./microshell.out <input>\n", 32);
	return (EXIT_FAILURE);
}

int	main(int const ac, char const **av, char const **ep)
{
	char const	**next;

	(void)ep;
	if (ac < 2)
		return (__usage_err());
	++av;
	while (*av)
	{
		next = av;
		while (*next && strcmp(*next, ";"))
			++next;
		if (*next)
			*next++ = NULL;
		if (pipeline(av, ep))
		{
			write(STDERR_FILENO, "error: fatal\n", 13);
			return (EXIT_FAILURE);
		}
		av = next;
	}
	return (EXIT_SUCCESS);
}
