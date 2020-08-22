#pragma once


class CLASS_DECL_AURA misc_exception :
   public ::exception::exception
{
public:


   misc_exception(const char * pszMessage = nullptr);
   virtual ~misc_exception();

};
