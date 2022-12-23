// X11Exception.h
// C++ exception that wraps X11 errors.
// Copyright (C) 2008 Jay Bromley <jbromley@gmail.com>
//
// $Id: X11Exception.h 26 2008-04-09 08:47:11Z jay $
#pragma once


// #include "acme/primitive/string/string.h"


class X11Exception
{
public:
    X11Exception() : _reason("unknown") {}
    X11Exception(const string& what) : _reason(what) {}
    virtual ~X11Exception() throw () {};
    virtual const char* what() const throw () { return _reason.c_str(); }

private:
    string _reason;
};


// Local Variables:
// mode: c++
// End:

