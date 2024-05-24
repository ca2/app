//
// Created by camilo on 2024-05-22 03:06 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "acid/primitive/string/string.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <errno.h>


cstring::cstring() :
string_pointer(nullptr)
{


}


cstring::cstring(const char *psz) :
string_pointer(::is_set(psz)? ::strdup(psz):nullptr)
{



}


cstring::cstring(const char *psz, strsize s)
{

    m_psz = (char*) ::malloc(s+1);

    strncpy(m_psz, psz, s);

    m_psz[s] = '\0';

}


cstring::cstring(const cstring & str) :
string_pointer(::is_set(str.m_psz)? ::strdup(str.m_psz):nullptr)
{



}


cstring::cstring(transfer_t, char *psz) :
string_pointer(psz)
{


}


cstring::~cstring()
{

    destroy();

}



void cstring::destroy()
{

    if(::is_set(m_psz))
    {


        ::free(m_psz);

        m_psz = nullptr;

    }

}


cstring & cstring::operator = (const cstring & str)
{

    destroy();

    if(::is_set(str.m_psz))
    {

        m_psz = ::strdup(str.m_psz);

    }

    return *this;

}


cstring & cstring::operator += (const cstring & str)
{

    if(::is_set(str.m_psz))
    {

        auto size = this->size() + str.size();

        auto psz = (char *) ::malloc(size + 1);

        ::strcpy(psz, m_psz);

        ::free(m_psz);

        ::strcpy(psz, str.m_psz);

        m_psz = psz;

    }

    return *this;

}


cstring & cstring::operator /= (const cstring & str)
{

    if(::is_set(str.m_psz))
    {

        auto size = this->size() + str.size() + 1;

        auto psz = (char *) ::malloc(size);

        ::strcpy(psz, m_psz);

        auto pszLeftEdge = psz + this->size();

        while(pszLeftEdge>psz && (pszLeftEdge[-1] == '/'
            || pszLeftEdge[-1] == '\\'))
        {

            pszLeftEdge--;

        }

        auto pszRightEdge = str.m_psz;

        auto pszEnd = pszRightEdge + str.size();

        while(pszRightEdge <pszEnd && (*pszRightEdge == '/'
            ||*pszRightEdge == '\\'))
        {

            pszRightEdge--;

        }
        strcpy(pszLeftEdge, "/");
        strcat(pszLeftEdge, pszRightEdge);
        ::free(m_psz);

        m_psz = psz;

    }

    return *this;

}


void cstring::assign(const char * psz, strsize s)
{

    destroy();

    if(::is_null(psz))
    {

        return;

    }

    strsize len;

    if(s<0)
    {

        s = strlen(psz) + s + 1;

        if(s <= 0)
        {

            return;

        }

    }

    m_psz = (char *) ::malloc(s+1);

    ::memcpy(m_psz, psz, s);

    m_psz[s] = '\0';

}


void cstring::assign(const char * psz)
{

    destroy();

    m_psz = ::strdup(psz);

}


void cstring::truncate(const char * psz)
{

    auto s = psz-m_psz;

    truncate(s);

}


void cstring::truncate(strsize s)
{

    if(s <= 0)
    {

        destroy();

        return;

    }

    auto len = this->size();

    if(s >= len)
    {

        return;

    }

    m_psz[s]='\0';


}


void cstring::trim_quotes()
{

    auto iLen = this->size();

    if(*m_psz == '\"' && m_psz[iLen - 1] == '\"')
    {

        char * pszTrimmed = (char*)malloc (iLen - 2 + 1);

        strncpy(pszTrimmed, m_psz + 1, iLen - 2);

        m_psz[iLen - 2] ='\0';

    }

}


cstring cstring_formatf_arguments(const char *format, va_list args)
{

    va_list args2;

    va_copy(args2, args);

    auto len = vsnprintf(nullptr, 0, format, args2);

    va_end(args2);

    auto psz = (char *) malloc(len +1);

    len = vsnprintf(psz, len+1, format, args);

    return {transfer_t{}, psz};

}


void cstring::formatf(const char *format, ...)
{

    va_list  args;

    va_start(args, format);
    this->operator=(cstring_formatf_arguments(format, args));
    va_end(args);

}


void cstring::append_formatf(const char *format, ...)
{

    va_list  args;

    va_start(args, format);
    this->operator+=(cstring_formatf_arguments(format, args));
    va_end(args);

}


void cstring::slash_formatf(const char *format, ...)
{

    va_list  args;

    va_start(args, format);
    this->operator/=(cstring_formatf_arguments(format, args));
    va_end(args);

}

//
//     void cstring::find_replace_character(char chSource, char chTarget)
//     {
//
//         auto p = m_psz;
//
//         while(*p)
//         {
//
// if(*p == chSource)
// {
//
//
// *p = chTarget;
//
// }
//
// p++;
//
//         }
//
//
//     }

//
// bool cstring::case_insensitive_equals(const char * psz) const
// {
//
//     if(::is_null(m_psz))
//     {
//
//         return false;
//
//     }
//
//     if(::is_null(psz))
//     {
//
//         return false;
//
//     }
//
//     return !strcasecmp(m_psz, psz);
//
// }

//
// ::acid::cstring cstring::case_insensitive_begins_eat_and_return(const char * pszPrefix)
// {
//
//     auto iLenPrefix = strlen(pszPrefix);
//     if(strncmp(m_psz, pszPrefix, iLenPrefix) == 0)
//     {
//         return m_psz + iLenPrefix;
//
//     }
//     return nullptr;
//
// }
//


cstring cstring::case_insensitive_if_begins_eat_and_return(const string_pointer & strpointerPrefix) const
{

    auto iLenPrefix = strpointerPrefix.size();

    if(case_insensitive_order(strpointerPrefix, 0, iLenPrefix) == 0)
    {
        return m_psz + iLenPrefix;

    }
    return nullptr;

}


cstring get_line(const string_pointer & strpointer, string_pointer & next)
{

    auto psz = strpointer.m_psz;
    if(!psz)
        return nullptr;

   auto start = strpointer.m_psz;
   while(*psz && *psz != '\n' && *psz != '\r')
   {

      psz++;

   }
   if(*psz=='\n')
   {
      next = psz+1;

   }
    else if(*psz=='\r')
    {
        if(*(psz+1) == '\n')
        {
            next = psz+2;
        }
        else
        {
        next = psz+1;
        }


    }
    else
   {
      next = nullptr;

   }

   return {strpointer.m_psz, psz - strpointer.m_psz};

}



