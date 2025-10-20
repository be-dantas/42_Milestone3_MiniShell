/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colletor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:00:29 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/10/20 11:17:38 by wedos-sa         ###   ########.fr       */
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
