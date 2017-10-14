/*
 * libtidm_exception - Exception Management Library
 * Copyright (C) 2017 TIDM Co.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 */

/**
 * @file
 * @author Ashkan Ghassemi <aghasemi@tidm.tosanltd.com>
 * @editor Ardeshir Baharian <baharian@tosanidm.net>
 * @version 6
 *
 * @section LICENSE
 *
 * Copyright (C) 2014-2017 Tosan Intelligent Data Miners
 *
 * @section DESCRIPTION
 *
 * OI server exception class to effectively
 * report errors, system wide.
 */

#include <sstream>
#include "exception.hpp"

void tidm::exception::reset()
{
    _error_code = 0;
}

std::string tidm::exception::driver(const char *fmt)
{
    return fmt;
}

tidm::exception::exception(const char *file,
                           const char *function,
                           const char *message)
{
    reset();
    append_oi_msg(file, function, message);
}

tidm::exception::exception(const char *file,
                           const char *function,
                           const std::string &message):
    exception(file, function, message.c_str())
{

}


void tidm::exception::add_msg(const char *file,
                              const char *function,
                              const char *message) throw()
{
    append_oi_msg(file, function, message);
}

void tidm::exception::add_msg(const char *file,
                        const char *function,
                        const std::string &msg) throw()
{
    add_msg(file, function, msg.c_str());
}

void tidm::exception::append_oi_msg(const char *file,
                                    const char *function,
                                    const char *message) throw()
{
    if(_errmsg.size() + strlen(message) < OI_MAX_ERR_MSG_LEN) {
        std::stringstream sstr;
        sstr << "(" << file << "::" << function << ") " << message << "\n";
        _errmsg += sstr.str();
    }
}


const char *tidm::exception::what() const throw()
{
    /*
     * Returning previously set error message.
     */
    return _errmsg.c_str();
}
