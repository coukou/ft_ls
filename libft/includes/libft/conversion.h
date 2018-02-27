/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 16:55:00 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/12 20:09:38 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_CONVERSION_H
# define LIBFT_CONVERSION_H

# define FT_CHAR_BASE "0123456789ABCDEF"

# include <wchar.h>

int			ft_atoi(const char *str);
long long	ft_atoll(const char *str, int base);
char		*ft_itoa(int n);
void		ft_lltoa(long long n, int base, char out[]);
void		ft_ulltoa(unsigned long long n, int base, char out[]);
void		ft_wctoa(wchar_t wc, char out[]);
void		ft_wstrtoa(const wchar_t *wstr, char out[]);
void		ft_wstrtoa_n(const wchar_t *wstr, size_t n, char out[]);

#endif
