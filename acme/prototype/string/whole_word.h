#pragma once


class CLASS_DECL_ACME whole_word
{
public:


   bool contains(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrFind);
   bool whole_word_find(string_array_base & stra, const ::scoped_string & scopedstr);
   bool whole_word_erase(string & str, const ::scoped_string & scopedstrFind);


};



