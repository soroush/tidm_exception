ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4
AM_CXXFLAGS = -Werror -Wall --pedantic
lib_LTLIBRARIES = libtidm_exception.la
libtidm_exception_la_SOURCES = \
    exception.cpp
libtidm_exception_la_LDFLAGS = -version-info $(TIDM_EXCEPTION_SO_VERSION)
tidm_exception_includedir = $(includedir)/tidm/utils/exception
tidm_exception_include_HEADERS = \
    exception.hpp
