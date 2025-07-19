/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_func2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:35:20 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/01 11:41:22 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ra(t_list **stack_a, int silent)
{
	t_list	*stack_tmp;

	if (!*stack_a || !(*stack_a)->next)
		return ;
	stack_tmp = (*stack_a)->next;
	(*stack_a)->next = NULL;
	(ft_lstlast(stack_tmp))->next = *stack_a;
	*stack_a = stack_tmp;
	if (!silent)
		ft_printf("ra\n");
}

void	rb(t_list **stack_b, int silent)
{
	t_list	*stack_tmp;

	if (!*stack_b || !(*stack_b)->next)
		return ;
	stack_tmp = (*stack_b)->next;
	(*stack_b)->next = NULL;
	(ft_lstlast(stack_tmp))->next = *stack_b;
	*stack_b = stack_tmp;
	if (!silent)
		ft_printf("rb\n");
}

void	rr(t_list **stack_a, t_list **stack_b)
{
	rb(stack_b, 1);
	ra(stack_a, 1);
	ft_printf("rr\n");
}

void	rra(t_list **stack_a, int silent)
{
	t_list	*last;
	t_list	*prev;

	if (!stack_a || !*stack_a || !(*stack_a)->next)
		return ;
	prev = *stack_a;
	while (prev->next->next)
		prev = prev->next;
	last = prev->next;
	prev->next = NULL;
	last->next = *stack_a;
	*stack_a = last;
	if (!silent)
		ft_printf("rra\n");
}

void	rrb(t_list **stack_b, int silent)
{
	t_list	*last;
	t_list	*prev;

	if (!stack_b || !*stack_b || !(*stack_b)->next)
		return ;
	prev = *stack_b;
	while (prev->next->next)
		prev = prev->next;
	last = prev->next;
	prev->next = NULL;
	last->next = *stack_b;
	*stack_b = last;
	if (!silent)
		ft_printf("rrb\n");
}
