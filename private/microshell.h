/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 07:05:22 by jodufour          #+#    #+#             */
/*   Updated: 2022/02/08 07:30:44 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MICROSHELL_H
# define MICROSHELL_H

# include <stddef.h>

int		pipeline(char const **av, char const **ep)
		__attribute__((nonnull));

size_t	msh_strlen(char const *str)
		__attribute__((nonnull));

#endif
