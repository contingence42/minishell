/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmetehri <bmetehri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:10:01 by bmetehri          #+#    #+#             */
/*   Updated: 2024/03/14 15:17:46 by bmetehri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_H
# define CONST_H

// Colors
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"

// Errors

# define ERR_MALLOC "Error: malloc failed\n"
# define ERR_OPEN "Error: open failed\n"
# define ERR_CLOSE "Error: close failed\n"
# define ERR_READ "Error: read failed\n"
# define ERR_WRITE "Error: write failed\n"
# define ERR_ARG "Error: invalid arguments\n"
# define ERR_FILE "Error: invalid file\n"

// Codes

# define SIGIGN 10 // Ignore signal

#endif