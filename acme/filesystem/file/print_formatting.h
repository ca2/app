// Created by camilo on 2023-06-10 19:42 <3ThomasBorregaardSorensen!!
#pragma once


class CLASS_DECL_ACME print_formatting
{
public:


   ::file::fmtflags           m_fmtflags;
   char                       m_width;
   char                       m_precision;


   print_formatting();


   void set_format_flags(::file::fmtflags efmtflags);


   filesize precision() const { return m_precision; }

   filesize precision(char prec) { return m_precision = prec; }

   filesize width() const { return m_width; }

   filesize width(char wide) { return m_width = wide; }


   ::file::fmtflags setf(::file::fmtflags flagsAdd)
   {

      return m_fmtflags = (::file::fmtflags)((((int)m_fmtflags)) | ((int)flagsAdd));

   }


   ::file::fmtflags setf(::file::fmtflags flagsAdd, ::file::fmtflags flagsRemove)
   {

      setf(flagsAdd);

      return m_fmtflags = (::file::fmtflags)((((int)m_fmtflags)) & (~(int)flagsAdd));

   }



};


