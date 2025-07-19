/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_func3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:17:26 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/05 16:36:20 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	rrr(t_list **stack_a, t_list **stack_b)
{
	rra(stack_a, 1);
	rrb(stack_b, 1);
	ft_printf("rrr\n");
}

void	set_chunk(int n, int *nb_chunk, int *size_chunk)
{
	if (n <= 100)
		*nb_chunk = 5;
	else if (n <= 500)
		*nb_chunk = 11;
	else
		*nb_chunk = 11 + (n / 70);
	if (!*nb_chunk)
		*nb_chunk = 1;
	*size_chunk = (n + *nb_chunk - 1) / *nb_chunk;
}
