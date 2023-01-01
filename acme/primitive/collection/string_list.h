#pragma once


#include "comparable_list.h"
// #include "acme/primitive/string/string.h"


class CLASS_DECL_ACME string_list :
   public comparable_list < ::string >
{
public:


   using RANGE = typename ::list < ::string >::RANGE;


   string_list();
   ~string_list() override;


   void explode(::const_ansi_range rangeSeparator, ::const_ansi_range range);

   void implode(string & rwstr, ::const_ansi_range rangeSeparator = nullptr, index iStart = 0, ::count iCount = -1) const;

   string implode(::const_ansi_range rangeSeparator = nullptr, index iStart = 0, ::count iCount = -1) const;

   void reverse_implode(string & rwstr, ::const_ansi_range rangeSeparator = nullptr, index iStart = 0, ::count iCount = -1) const;

   string reverse_implode(::const_ansi_range rangeSeparator = nullptr, index iStart = 0, ::count iCount = -1) const;

   void add_tail_tokens(::const_ansi_range range, ::const_ansi_range rangeSeparator, bool bAddEmpty);


   //virtual ::stream & read(::stream & stream) override;
   //virtual ::stream & write(::stream & stream) const override;


};



//template < typename TYPE >
//inline stream& operator <<(stream& stream, const string_list& list);
//
//
//template < typename TYPE >
//inline stream& operator >>(stream& stream, string_list& list);




