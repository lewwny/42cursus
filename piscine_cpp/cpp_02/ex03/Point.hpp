/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:20:59 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/13 21:25:22 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

#define RESET		"\033[0m"
#define RED			"\033[31m"
#define GREEN		"\033[32m"
#define YELLOW		"\033[33m"
#define CYAN		"\033[36m"
#define BOLD		"\033[1m"
#define CHECKMARK	"\u2714"
#define CROSS		"\u2716"

class Point
{
private:
	Fixed const _x;
	Fixed const _y;
public:
	Point();
	Point(float const x, float const y);
	Point(Point const &src);
	~Point();
	Point &operator=(Point const &other);
	Fixed getX() const;
	Fixed getY() const;
};

bool bsp(Point const a, Point const b, Point const c, Point const point);