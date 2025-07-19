/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:44:43 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/05 16:44:25 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	find_first_in_chunk(t_list *a, int min, int max)
{
	int	pos;

	pos = 0;
	while (a)
	{
		if (a->content >= min && a->content <= max)
			return (pos);
		pos++;
		a = a->next;
	}
	return (-1);
}

static int	find_last_in_chunk(t_list *a, int min, int max)
{
	int	pos;
	int	last;

	pos = 0;
	last = -1;
	while (a)
	{
		if (a->content >= min && a->content <= max)
			last = pos;
		pos++;
		a = a->next;
	}
	return (last);
}

static void	rotate_stack(int first, t_list **a, int size, int last)
{
	int	rot;

	if (first <= size - last)
	{
		rot = first;
		while (rot-- > 0)
			ra(a, 0);
	}
	else
	{
		rot = size - last;
		while (rot-- > 0)
			rra(a, 0);
	}
}

static void	push_chunk(t_list **a, t_list **b, int min, int max)
{
	int	first;
	int	last;
	int	size;

	first = find_first_in_chunk(*a, min, max);
	while (first != -1)
	{
		size = ft_lstsize(*a);
		last = find_last_in_chunk(*a, min, max);
		rotate_stack(first, a, size, last);
		pb(a, b);
		if ((*b)->content < min + (max - min) / 2)
			rb(b, 0);
		first = find_first_in_chunk(*a, min, max);
	}
}

void	push_all_chunks(t_list **a, t_list **b, int nb_chunks, int chunk_size)
{
	int	i;
	int	min;
	int	max;
	int	total;

	total = ft_lstsize(*a);
	i = 0;
	while (i < nb_chunks)
	{
		min = i * chunk_size;
		max = min + chunk_size - 1;
		if (max >= total)
			max = total - 1;
		push_chunk(a, b, min, max);
		i++;
	}
}
