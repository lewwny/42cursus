/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:22:53 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/05 16:44:01 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	find_pos_of_index(t_list *stack, int index)
{
	int	pos;

	pos = 0;
	while (stack)
	{
		if (stack->content == index)
			return (pos);
		stack = stack->next;
		pos++;
	}
	return (-1);
}

int	find_max_index(t_list *stack_b)
{
	int	max;

	if (!stack_b)
		return (-1);
	max = stack_b->content;
	while (stack_b)
	{
		if (stack_b->content > max)
			max = stack_b->content;
		stack_b = stack_b->next;
	}
	return (max);
}

void	push_back_to_a(t_list **a, t_list **b)
{
	int	max;
	int	pos;
	int	size;

	while (*b)
	{
		max = find_max_index(*b);
		pos = find_pos_of_index(*b, max);
		size = ft_lstsize(*b);
		if (pos <= size / 2)
			while (pos-- > 0)
				rb(b, 0);
		else
		{
			pos = size - pos;
			while (pos-- > 0)
				rrb(b, 0);
		}
		pa(a, b);
		while (*b && (*b)->content == (*a)->content - 1)
			pa(a, b);
	}
}
