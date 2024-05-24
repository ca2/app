#pragma once




class CLASS_DECL_ACID invalid_character :
   public ::exception
{
public:


   invalid_character(const ::scoped_string & scopedstrMessage = nullptr);
   virtual ~invalid_character();


};
