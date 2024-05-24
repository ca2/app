//
// Created by camilo on 2024-05-22 03:06 <3ThomasBorregaardSorensen!!
//
// From string_pointer on 2024-05-22 23:22 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acid/primitive/string/string_pointer.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <errno.h>


namespace acid
{


    string_pointer::string_pointer() :
        m_psz(nullptr)
    {


    }


    string_pointer::string_pointer(const char *psz) :
    m_psz((char*) psz)
    {



    }


    strsize string_pointer::size() const
    {

        return ::is_set(m_psz) ? ::strlen(m_psz) : 0;

    }


    void string_pointer::find_replace_character(char chSource, char chTarget)
    {

        auto p = m_psz;

        while(*p)
        {

            if(*p == chSource)
            {


            *p = chTarget;

            }

            p++;

        }

    }


    bool string_pointer::case_insensitive_equals(const string_pointer & strpointer) const
    {

        return case_insensitive_order(strpointer) == 0;

    }


    ::std::strong_ordering string_pointer::case_insensitive_order(const string_pointer & strpointer) const
    {

        if(!strpointer)
        {

            if(is_null())
            {

                return ::std::strong_ordering::equal;

            }
            else
            {

                return ::std::strong_ordering::greater;

            }

        }
        else
        {

            if(is_null())
            {

                return ::std::strong_ordering::less;

            }

        }

        return strcasecmp(m_psz, strpointer.m_psz) <=> 0;

    }


    ::std::strong_ordering string_pointer::case_insensitive_order(const string_pointer & strpointer, strsize start, strsize count) const
    {

        if(!strpointer)
        {

            if(is_null())
            {

                return ::std::strong_ordering::equal;

            }
            else
            {

                return ::std::strong_ordering::greater;

            }

        }
        else
        {

            if(is_null())
            {

                return ::std::strong_ordering::less;

            }

        }

::std::strong_ordering ordering = ::std::strong_ordering::equal;
auto left = m_psz + start;
char * end;
if(count < 0)
{
end = m_psz+ this->size() +count+1;
}
else
{
end =left + count;
}
auto right = strpointer.m_psz;
while(left < end)
{

ordering = *left <=> *right;
if(ordering != 0)
{

    return ordering;

}
left++;
right++;
}
return ordering;
    }





    string_pointer string_pointer::find_character(char ch, strsize start) const
    {

        if(::is_null(m_psz))
        {

            return nullptr;

        }


        return strchr(m_psz + start, ch);

    }


    string_pointer string_pointer::skip_any_not_in(const string_pointer & strpointer) const
    {

        return m_psz + ::strspn(m_psz, strpointer.m_psz);

    }


    string_pointer string_pointer::find_any_in(const string_pointer & strpointer) const
    {

        return ::strpbrk(m_psz, strpointer.m_psz);

    }


    string_pointer string_pointer::find(const string_pointer & strpointer) const
    {

        return strstr(m_psz, strpointer.c_str());

    }


    bool string_pointer::contains(const string_pointer & strpointer) const
    {

        return this->find(strpointer);

    }


    string_pointer string_pointer::case_insensitive_find(const string_pointer & strpointer) const
    {

        return strcasestr(m_psz, strpointer.c_str());

    }


    bool string_pointer::case_insensitive_contains(const string_pointer & strpointer) const
    {

        return this->find(strpointer);

    }


} // namespace acid


