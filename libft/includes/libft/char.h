/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 16:50:28 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/11 18:31:01 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_CHAR_H
# define LIBFT_CHAR_H

# define FT_LOWER_UPPER_DIFF 32

int		ft_isalpha(int c);
int		ft_islower(int c);
int		ft_isupper(int c);
int		ft_isblank(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_isin(int c, unsigned char *charset);
int		ft_toupper(int c);
int		ft_tolower(int c);

#endif
