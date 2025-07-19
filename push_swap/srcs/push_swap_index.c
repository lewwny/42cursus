/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:47:32 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/04 22:11:31 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	partition(int *tab, int size)
{
	int	pivot;
	int	i;
	int	j;
	int	tmp;

	pivot = tab[size - 1];
	i = -1;
	j = 0;
	while (j < size - 1)
	{
		if (tab[j] < pivot)
		{
			i++;
			tmp = tab[i];
			tab[i] = tab[j];
			tab[j] = tmp;
		}
		j++;
	}
	tmp = tab[i + 1];
	tab[i + 1] = tab[size - 1];
	tab[size - 1] = tmp;
	return (i + 1);
}

static void	sort_int_tab(int *tab, int size)
{
	int	p;

	if (size <= 1)
		return ;
	p = partition(tab, size);
	sort_int_tab(tab, p);
	sort_int_tab(tab + p + 1, size - p - 1);
}

static int	index_recup(int *tab, int c, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (tab[i] == c)
			return (i);
		i++;
	}
	return (i);
}

static void	replace_lst_index(t_list *stack_a, int *tab, int size)
{
	while (stack_a)
	{
		(stack_a)->content = index_recup(tab, (stack_a)->content, size);
		(stack_a) = (stack_a)->next;
	}
}

void	init_index(t_list **stack_a, char **argv, int a)
{
	int		*list;
	t_pair	*asize;

	asize = malloc(sizeof(t_pair));
	if (!asize)
		error_program_free(stack_a, argv, a);
	asize->size = ft_lstsize(*stack_a);
	asize->a = a;
	list = fill_list(*stack_a, asize->size, argv, asize->a);
	sort_int_tab(list, asize->size);
	test_double(list, stack_a, argv, asize);
	replace_lst_index(*stack_a, list, asize->size);
	free(list);
	free(asize);
}
