#pragma once


#include "acme/prototype/collection/comparable_list.h"



class CLASS_DECL_ACME string_list_base :
   public comparable_list_base < ::string >
{
public:


   using RANGE = typename ::list_base < ::string >::RANGE;


   string_list_base();
   ~string_list_base();


   void explode(const ::scoped_string & scopedstrSeparator, const ::scoped_string & scopedstr);

   void implode(string & str, const ::scoped_string & scopedstrSeparator = nullptr, ::collection::index iStart = 0, ::collection::count iCount = -1) const;

   string implode(const ::scoped_string & scopedstrSeparator = nullptr, ::collection::index iStart = 0, ::collection::count iCount = -1) const;

   void reverse_implode(string & str, const ::scoped_string & scopedstrSeparator = nullptr, ::collection::index iStart = 0, ::collection::count iCount = -1) const;

   string reverse_implode(const ::scoped_string & scopedstrSeparator = nullptr, ::collection::index iStart = 0, ::collection::count iCount = -1) const;

   void add_tail_tokens(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrSeparator, bool bAddEmpty);


   //virtual ::stream & read(::stream & stream) override;
   //virtual ::stream & write(::stream & stream) const override;


};



//template < typename TYPE >
//inline stream& operator <<(stream& stream, const string_list_base& list_base);
//
//
//template < typename TYPE >
//inline stream& operator >>(stream& stream, string_list_base& list_base);




