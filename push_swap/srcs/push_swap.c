/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:50:18 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/26 08:14:26 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	sort_stack(t_list **stack_a, t_list **stack_b)
{
	int	n;
	int	nb_chunk;
	int	size_chunk;

	n = ft_lstsize(*stack_a);
	if (n == 2)
	{
		if ((*stack_a)->content > (*stack_a)->next->content)
			sa(*stack_a);
	}
	else if (n == 3)
		sort_three(stack_a);
	else if (n <= 5)
		sort_five(stack_a, stack_b);
	else
	{
		set_chunk(n, &nb_chunk, &size_chunk);
		push_all_chunks(stack_a, stack_b, nb_chunk, size_chunk);
		push_back_to_a(stack_a, stack_b);
	}
}

static void	ajust_argc(int *argc, char **argv)
{
	int	i;

	i = 0;
	if (!argv[0])
	{
		free_split(argv);
		error_program();
	}
	while (argv[i])
		i++;
	*argc = i;
}

static int	is_sorted(t_list *stack)
{
	while (stack && stack->next)
	{
		if (stack->content >= stack->next->content)
			return (0);
		stack = stack->next;
	}
	return (1);
}

static void	free_end(int a, t_list **stack_a, char **argv)
{
	ft_lstclear(stack_a);
	if (a)
		free_split(argv);
}

int	main(int argc, char **argv)
{
	t_list	*stack_a;
	t_list	*stack_b;
	int		a;

	if (argc == 1)
		return (0);
	a = 0;
	stack_b = NULL;
	if (argc == 2)
	{
		argv = ft_split(argv[1], ' ');
		if (!argv)
			error_program();
		a = 1;
		ajust_argc(&argc, argv);
	}
	test_argument(argc, argv, a);
	stack_a = init_stack(argc, argv, a);
	if (!is_sorted(stack_a))
	{
		init_index(&stack_a, argv, a);
		sort_stack(&stack_a, &stack_b);
	}
	free_end(a, &stack_a, argv);
	return (0);
}
