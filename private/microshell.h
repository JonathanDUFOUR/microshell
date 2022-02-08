/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 07:05:22 by jodufour          #+#    #+#             */
/*   Updated: 2022/02/08 14:43:31 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MICROSHELL_H
# define MICROSHELL_H

# include <stddef.h>

int	cd(char const **av)
	__attribute__((nonnull));
int	exec(char const **av, char const **ep, int const save,
		int const *const tube)
	__attribute__((nonnull));
int	pipeline(char const **av, char const **ep)
	__attribute__((nonnull));
int	redirect(int const redirin, int const redirout);

#endif
