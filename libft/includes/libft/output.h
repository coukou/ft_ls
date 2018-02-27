/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 16:53:41 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/09 16:59:22 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_OUTPUT_H
# define LIBFT_OUTPUT_H

# include <unistd.h>

void	ft_putchar(char c);
void	ft_putendl(char *s);
void	ft_putnbr(int n);
void	ft_putstr(char *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);

#endif
