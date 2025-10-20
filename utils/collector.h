/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:00:29 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/10/20 13:36:00 by bedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLECTOR_H
# define COLLECTOR_H

#include "../libft/libft.h"

typedef struct s_collect
{
	struct s_collect	*next;
	void				*data;
}	t_collect;

#endif
