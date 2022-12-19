// Created by camilo on 2022-04-26 06:56 <3ThomasBorregaardS�rensen!!
#pragma once


class CLASS_DECL_ACME string_block :
   public block
{
public:

   string_block(const scoped_string & str, strsize length) : block(psz, length) { }
   string_block(const scoped_string & str) : block(psz, ::ansi_length(psz)) { }


   char first() const { return (char)m_pdata[0]; }
   char & first() { return (char &)m_pdata[0]; }
   char last() const { return (char)m_pdata[m_iSize - 1]; }
   char & last() { return (char &)m_pdata[m_iSize - 1]; }


   int compare(const scoped_string & str)const { return strncmp((const char*)m_pdata, psz, m_iSize); }
   int case_insensitive_order(const scoped_string & str)const { return strnicmp((const char *)m_pdata, psz, m_iSize); }
   bool operator == (const scoped_string & str)const { return compare(psz) == 0; }
   bool operator != (const scoped_string & str) const { return!operator==(psz); }




};



