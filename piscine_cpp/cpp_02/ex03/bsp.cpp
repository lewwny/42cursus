/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:25:15 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/13 21:28:43 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

//Formule mathématique pour calculer l'aire d'un triangle.
static Fixed	area(const Point &p1, const Point &p2, const Point &p3)
{
	Fixed result = ((p1.getX() * (p2.getY() - p3.getY())) +
					(p2.getX() * (p3.getY() - p1.getY())) +
					(p3.getX() * (p1.getY() - p2.getY()))) / Fixed(2);
	if (result < Fixed(0))
		result = result * Fixed(-1);
	return (result);
}

bool	bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed a0, a1, a2, a3;
	bool ret = false;

	a0 = area(a, b, c);
	a1 = area(a, b, point);
	a2 = area(b, c, point);
	a3 = area(c, a, point);

	if (a1 == Fixed(0) || a2 == Fixed(0) || a3 == Fixed(0))
		ret = false;
	else if (a0 == (a1 + a2 + a3))
		ret = true;
	return (ret);
}