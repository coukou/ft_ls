/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 13:40:13 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/13 15:00:51 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UNICODE_H
# define FT_UNICODE_H

# include <wchar.h>
# include <stdlib.h>

# define WCHAR_1_MIN 0x00
# define WCHAR_1_MAX 0x7F

# define WCHAR_2_MIN 0x80
# define WCHAR_2_MAX 0x7FF

# define WCHAR_3_MIN 0x800
# define WCHAR_3_MAX 0xFFFF

# define WCHAR_4_MIN 0x10000
# define WCHAR_4_MAX 0x10FFFF

size_t		ft_wclen(wchar_t c);
size_t		ft_wstrlen(const wchar_t *wstr);
size_t		ft_wstrtoa_len(const wchar_t *wstr);
size_t		ft_wstrtoa_len_n(const wchar_t *wstr, size_t n);
wchar_t		*ft_wstrdup(const wchar_t *wstr);
wchar_t		*ft_wstrndup(const wchar_t *wstr, size_t n);

#endif
