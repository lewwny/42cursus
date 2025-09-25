/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticExec.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:28:21 by mcauchy-          #+#    #+#             */
/*   Updated: 2025/09/12 13:50:49 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATIC_EXEC_HPP

#define STATIC_EXEC_HPP

#include "Router.hpp"
#include "Response.hpp"
#include "ConfigParse.hpp"


// Static file execution (in-Router, no blocking I/O):
class StaticExec 
{
					public:
						// Produce a static file response (no blocking I/O):
						static Response makeRedirect(const Router::Decision& d);
						static Response makeError(const Router::Decision& d, const Config &cfg);
						static Response serveStatic(const Router::Decision& d, Config &cfg);
};

#endif
