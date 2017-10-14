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

#include "exception.hpp"
#include <vector>
#include <iostream>

void f1();
void f2();
void f3();
void f();

void f3()
{
    try {
        f2();
    } catch(tidm::exception &ox) {
        ox.add_msg(__FILE__, __FUNCTION__, "excption in % % to %", "f3", 5, 12.4);
        throw ox;
    }
}
void f2()
{
    try {
        f1();
    } catch(tidm::exception &ox) {
        ox.add_msg(__FILE__, __FUNCTION__, "excption in % % to % more params", "f2", 5, 12.4, 30000);
        throw ox;
    }
}

void f1()
{
    try {
        f();
    } catch(tidm::exception &ox) {
        ox.add_msg(__FILE__, __FUNCTION__, "ino percentage but  params", 5, 12.4);
        throw ox;
    }
}

void f()
{
    std::vector<int> v;
    try {
        v.at(10)++;
    } catch(std::exception &ex) {
        tidm::exception ox("std", "exception", ex.what());
        std::string str = " no params";
        ox.add_msg(__FILE__, __FUNCTION__, str);
        throw ox;
    }
}

int main()
{

    try {
        f3();
    } catch(tidm::exception &os) {
        std::cerr << os.what() << std::endl;
    }
    return 0;
}
