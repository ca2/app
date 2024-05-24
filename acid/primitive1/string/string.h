//
// Created by camilo on 2024-05-22 03:04 <3ThomaasBorregaardSorensen!!
//
// From acid by camilo on 2024-05-22 11:16 <3ThomasBorregaardSorensen!!
#pragma once


#include "string_pointer.h"


/// allocated with malloc
/// utf8 null terminated string
/// due possible inline editing:
/// - may have actually more space allocated after null termination
/// - not safe to pass raw pointers to other strings without copy
/// (the source pointer maybe be edited - it is mutable)
class cstring :
    public string_pointer
{
public:


    cstring();
    cstring(const char *psz);
    cstring(const char *psz, strsize s);
    cstring(transfer_t, char *psz);
    cstring(const cstring & str);
    ~cstring();


    void destroy();


    cstring & operator = (const cstring & str);
    cstring & operator += (const cstring & str);
    cstring & operator /= (const cstring & str);


    void assign(const char * psz, strsize s);
    void assign(const char * psz);


    void truncate(const char *);
    void truncate(strsize s);

    void trim_quotes();

    char & operator [](strsize i) {return m_psz[i];}


    void formatf(const char *format, ...);
    void append_formatf(const char *format, ...);
    void slash_formatf(const char *format, ...);


    string_pointer operator ()(){return m_psz;}

    cstring case_insensitive_if_begins_eat_and_return(const string_pointer & strpointerPrefix) const;



};


cstring get_line(const string_pointer & strpointer, string_pointer & strpointerEnd);




