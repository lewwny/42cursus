/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_func1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:37:52 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/05 10:43:37 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	sa(t_list *stack_a)
{
	int		tmp1;
	int		tmp2;
	t_list	*stack_tmp;

	if (!stack_a || !stack_a->next)
		return ;
	tmp1 = stack_a->content;
	stack_tmp = stack_a->next;
	tmp2 = stack_tmp->content;
	stack_tmp->content = tmp1;
	stack_a->content = tmp2;
	ft_printf("sa\n");
}

void	sb(t_list *stack_b)
{
	int		tmp1;
	int		tmp2;
	t_list	*stack_tmp;

	if (!stack_b || !stack_b->next)
		return ;
	tmp1 = stack_b->content;
	stack_tmp = stack_b->next;
	tmp2 = stack_tmp->content;
	stack_tmp->content = tmp1;
	stack_b->content = tmp2;
	ft_printf("sb\n");
}

void	ss(t_list *stack_a, t_list *stack_b)
{
	int		tmp1;
	int		tmp2;
	t_list	*stack_tmp;

	if (stack_a && stack_a->next)
	{
		tmp1 = stack_a->content;
		stack_tmp = stack_a->next;
		tmp2 = stack_tmp->content;
		stack_tmp->content = tmp1;
		stack_a->content = tmp2;
	}
	if (stack_b && stack_b->next)
	{
		tmp1 = stack_b->content;
		stack_tmp = stack_b->next;
		tmp2 = stack_tmp->content;
		stack_tmp->content = tmp1;
		stack_b->content = tmp2;
	}
	ft_printf("ss\n");
}

void	pa(t_list **stack_a, t_list **stack_b)
{
	t_list	*stack_tmp;

	if (!*stack_b)
		return ;
	stack_tmp = *stack_b;
	*stack_b = (*stack_b)->next;
	stack_tmp->next = *stack_a;
	*stack_a = stack_tmp;
	ft_printf("pa\n");
}

void	pb(t_list **stack_a, t_list **stack_b)
{
	t_list	*stack_tmp;

	if (!*stack_a)
		return ;
	stack_tmp = *stack_a;
	*stack_a = (*stack_a)->next;
	stack_tmp->next = *stack_b;
	*stack_b = stack_tmp;
	ft_printf("pb\n");
}
