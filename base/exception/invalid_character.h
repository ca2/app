#pragma once




class CLASS_DECL_AURA invalid_character :
   public ::exception::exception
{
public:


   invalid_character(const char * pszMessage = nullptr);
   virtual ~invalid_character();


};
