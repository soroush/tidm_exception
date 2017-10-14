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

#ifndef TIDM_EXCEPTION_HPP
#define TIDM_EXCEPTION_HPP

#define OI_MAX_ERR_MSG_LEN 4000

#include <exception>
#include <cstring>
#include <string>
#include <sstream>

namespace tidm {

class exception: public std::exception {
    public:
        exception(const char *file,
                  const char *function,
                  const char *message);
        exception(const char *file,
                  const char *function,
                  const std::string &message);
        void reset();
        template<typename T, typename... Targs>
        exception(const char *file, const char *function, const char *fmt, T value, Targs... Fargs) {
            std::string str = driver(fmt, value, Fargs...);
            append_oi_msg(file, function, str.c_str());
        }
        void error_code(int err_code) {
            _error_code = err_code;
        }
        int error_code() {
            return _error_code ;
        }

        virtual void add_msg(const char *file,
                             const char *function,
                             const char *msg) throw();
        virtual void add_msg(const char *file,
                             const char *function,
                             const std::string &msg) throw();
        template<typename T, typename... Targs>
        void add_msg(const char *file,
                     const char *function,
                     const char *fmt,
                     T value, Targs... Fargs)throw() {
            std::string str = driver(fmt, value, Fargs...);
            add_msg(file, function, str.c_str());
        }

        virtual const char *what() const throw();
        std::string _errmsg;//[OI_MAX_ERR_MSG_LEN];
    private:
        void append_oi_msg(const char *file,
                           const char *function,
                           const char *msg) throw();
        int _error_code;

        std::string driver(const char *fmt);
        template<typename T, typename...Targs>
        std::string driver(const char *fmt, T value, Targs... Fargs) {
            std::stringstream sstr;
            try {
                for(; *fmt != '\0'; fmt++) {
                    if(*fmt == '%') {
                        sstr << value;
                        sstr << driver(fmt + 1, Fargs...);
                        return sstr.str();
                    }
                    sstr << *fmt;
                }
            } catch(...) {
                return "std::exception in exception class! THE SAULT PUTREFIED! ~\\o/~";
            }
            return sstr.str();
        }
};

} // namespace tidm

#endif /* TIDM_EXCEPTION_HPP */
