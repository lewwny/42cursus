/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:47:12 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/05 17:17:27 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"

typedef struct s_pair
{
	int	a;
	int	size;
}	t_pair;

void	test_argument(int argc, char **argv, int a);
void	ft_lstprint(t_list *lst);
void	sa(t_list *stack_a);
void	sb(t_list *stack_b);
void	ss(t_list *stack_a, t_list *stack_b);
void	pa(t_list **stack_a, t_list **stack_b);
void	pb(t_list **stack_a, t_list **stack_b);
void	ra(t_list **stack_a, int silent);
void	rb(t_list **stack_b, int silent);
void	rr(t_list **stack_a, t_list **stack_b);
void	rra(t_list **stack_a, int silent);
void	rrb(t_list **stack_b, int silent);
void	rrr(t_list **stack_a, t_list **stack_b);
void	error_program(void);
void	init_index(t_list **stack_a, char **argv, int a);
void	set_chunk(int n, int *nb_chunk, int *size_chunk);
void	push_all_chunks(t_list **a, t_list **b, int nb_chunks, int chunk_size);
void	test_double(int *tab, t_list **stack_a, char **argv, t_pair *asize);
void	push_back_to_a(t_list **a, t_list **b);
void	error_program_free(t_list **stack_a, char **argv, int a);
void	free_split(char **tab);
void	sort_five(t_list **a, t_list **b);
void	sort_three(t_list **stack);

int		*fill_list(t_list *stack_a, int size, char **argv, int a);
int		find_pos_of_index(t_list *stack, int index);
int		find_max_index(t_list *stack_b);

t_list	*init_stack(int argc, char **argv, int a);

#endif
