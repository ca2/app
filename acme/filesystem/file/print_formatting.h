// Created by camilo on 2023-06-10 19:42 <3ThomasBorregaardSorensen!!
#pragma once


#pragma pack(push, print_formatting, 1)


class CLASS_DECL_ACME print_formatting
{
public:


   ::file::fmtflags           m_fmtflags;
   ::i8                       m_width;
   ::i8                       m_precision;


   print_formatting();


   void set_format_flags(::file::fmtflags efmtflags);


   filesize precision() const { return m_precision; }

   filesize precision(i8 prec) { return m_precision = prec; }

   filesize width() const { return m_width; }

   filesize width(i8 wide) { return m_width = wide; }


   ::file::fmtflags setf(::file::fmtflags flagsAdd)
   {

      return m_fmtflags = (::file::fmtflags)((((::i32)m_fmtflags)) | ((::i32)flagsAdd));

   }


   ::file::fmtflags setf(::file::fmtflags flagsAdd, ::file::fmtflags flagsRemove)
   {

      setf(flagsAdd);

      return m_fmtflags = (::file::fmtflags)((((::i32)m_fmtflags)) & (~(::i32)flagsAdd));

   }



};


#pragma pack(pop, print_formatting)


