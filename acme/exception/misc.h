#pragma once


class CLASS_DECL_ACME misc_exception :
   public ::exception::exception
{
public:


   misc_exception(const char * pszMessage = nullptr);
   virtual ~misc_exception();

};
