#pragma once




class CLASS_DECL_ACME invalid_character :
   public ::exception
{
public:


   invalid_character(const scoped_string & strMessage = nullptr);
   virtual ~invalid_character();


};
