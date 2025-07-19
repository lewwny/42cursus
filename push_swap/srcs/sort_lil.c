/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lil.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:26:57 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/05 10:43:51 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	find_min_index(t_list *stack)
{
	int	min;

	min = stack->content;
	while (stack)
	{
		if (stack->content < min)
			min = stack->content;
		stack = stack->next;
	}
	return (min);
}

void	sort_three(t_list **stack)
{
	int	a;
	int	b;
	int	c;

	a = (*stack)->content;
	b = (*stack)->next->content;
	c = (*stack)->next->next->content;
	if (a > b && b < c && a < c)
		sa(*stack);
	else if (a > b && b > c)
	{
		sa(*stack);
		rra(stack, 0);
	}
	else if (a > b && b < c && a > c)
		ra(stack, 0);
	else if (a < b && b > c && a < c)
	{
		sa(*stack);
		ra(stack, 0);
	}
	else if (a < b && b > c && a > c)
		rra(stack, 0);
}

void	sort_five(t_list **a, t_list **b)
{
	int	pos;
	int	min;
	int	size;

	size = ft_lstsize(*a);
	while (ft_lstsize(*a) > 3)
	{
		min = find_min_index(*a);
		pos = find_pos_of_index(*a, min);
		if (pos == 0)
			pb(a, b);
		else if (pos <= size / 2)
			ra(a, 0);
		else
			rra(a, 0);
	}
	sort_three(a);
	while (*b)
		pa(a, b);
}
