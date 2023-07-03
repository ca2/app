#pragma once


#include "comparable_list.h"



class CLASS_DECL_ACME string_list :
   public comparable_list < ::string >
{
public:


   using RANGE = typename ::list < ::string >::RANGE;


   string_list();
   ~string_list() override;


   void explode(const ::scoped_string & scopedstrSeparator, const ::scoped_string & scopedstr);

   void implode(string & str, const ::scoped_string & scopedstrSeparator = nullptr, index iStart = 0, ::count iCount = -1) const;

   string implode(const ::scoped_string & scopedstrSeparator = nullptr, index iStart = 0, ::count iCount = -1) const;

   void reverse_implode(string & str, const ::scoped_string & scopedstrSeparator = nullptr, index iStart = 0, ::count iCount = -1) const;

   string reverse_implode(const ::scoped_string & scopedstrSeparator = nullptr, index iStart = 0, ::count iCount = -1) const;

   void add_tail_tokens(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrSeparator, bool bAddEmpty);


   //virtual ::stream & read(::stream & stream) override;
   //virtual ::stream & write(::stream & stream) const override;


};



//template < typename TYPE >
//inline stream& operator <<(stream& stream, const string_list& list);
//
//
//template < typename TYPE >
//inline stream& operator >>(stream& stream, string_list& list);




