// Created by camilo on 2023-06-10 19:46 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "print_formatting.h"


print_formatting::print_formatting()
{

   //m_fmtflags = ::file::nofmtflags;
   //m_precision = 0;

   m_fmtflags = ::file::nofmtflags;
   m_width = 2;
   m_precision = 2;

}


void print_formatting::set_format_flags(::file::fmtflags efmtflags)
{

   m_fmtflags = (::file::fmtflags) (m_fmtflags | efmtflags);

}



