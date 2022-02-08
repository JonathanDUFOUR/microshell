/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:24:44 by jodufour          #+#    #+#             */
/*   Updated: 2022/02/08 13:29:04 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

int	redirect(int const redirin, int const redirout)
{
	if (redirin != STDIN_FILENO
		&& (close(STDIN_FILENO) == -1
			|| dup2(redirin, STDIN_FILENO) == -1))
		return (EXIT_FAILURE);
	if (redirout != STDOUT_FILENO
		&& (close(STDOUT_FILENO) == -1
			||dup2(redirout, STDOUT_FILENO) == -1))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
