/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:54:47 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/26 08:09:30 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	error_program(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

void	error_program_free(t_list **stack_a, char **argv, int a)
{
	if (*stack_a)
		ft_lstclear(stack_a);
	if (a)
		free_split(argv);
	write(2, "Error\n", 6);
	exit(1);
}

static int	test_argv(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		i++;
		count++;
	}
	if (str[i] || !count)
		return (0);
	return (1);
}

void	test_argument(int argc, char **argv, int a)
{
	int	i;

	i = 1;
	if (a)
		i = 0;
	while (i < argc)
	{
		if (!test_argv(argv[i]))
		{
			if (a)
				free_split(argv);
			error_program();
		}
		i++;
	}
}

void	test_double(int *tab, t_list **stack_a, char **argv, t_pair *asize)
{
	int	i;
	int	a;

	a = asize->a;
	i = 0;
	while (i < asize->size - 1)
	{
		if (tab[i] == tab[i + 1])
		{
			free(tab);
			free(asize);
			error_program_free(stack_a, argv, a);
		}
		i++;
	}
}
