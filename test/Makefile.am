ACLOCAL_AMFLAGS= ${ACLOCAL_FLAGS} -I m4
AM_CXXFLAGS = -Wall -Werror --pedantic
AM_CPPFLAGS = -I../src/

check_PROGRAMS= test_except
test_except_SOURCES= main.cpp
test_except_LDADD = ../src/libtidm_exception.la

TESTS=$(check_PROGRAMS)


