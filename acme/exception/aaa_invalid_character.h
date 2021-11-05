#pragma once




class CLASS_DECL_ACME invalid_character :
   public ::exception
{
public:


   invalid_character(const char * pszMessage = nullptr);
   virtual ~invalid_character();


};
