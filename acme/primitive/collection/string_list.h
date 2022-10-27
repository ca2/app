﻿#pragma once


#include "list.h"
#include "acme/primitive/string/string.h"


class CLASS_DECL_ACME string_list :
   public list < ::string >
{
public:


   string_list();
   ~string_list() override;


   void explode(const char * pcszSeparator, const char * psz);

   void implode(string & rwstr, const char * pcszSeparator = nullptr, index iStart = 0, ::count iCount = -1) const;

   string implode(const char * pcszSeparator = nullptr, index iStart = 0, ::count iCount = -1) const;

   void reverse_implode(string & rwstr, const char * pcszSeparator = nullptr, index iStart = 0, ::count iCount = -1) const;

   string reverse_implode(const char * pcszSeparator = nullptr, index iStart = 0, ::count iCount = -1) const;


   void add_tail_tokens(const char * pcsz, const char * pcszSeparator, bool bAddEmpty);


   //virtual ::stream & read(::stream & stream) override;
   //virtual ::stream & write(::stream & stream) const override;


};



//template < typename TYPE >
//inline stream& operator <<(stream& stream, const string_list& list);
//
//
//template < typename TYPE >
//inline stream& operator >>(stream& stream, string_list& list);




