#pragma once


class CLASS_DECL_ACME resource_exception :
   public ::exception
{
public:


   resource_exception(const char * pszMessage = nullptr);
   virtual ~resource_exception();


};
