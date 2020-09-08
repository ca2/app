#pragma once


class CLASS_DECL_ACME overflow_error :
   public ::exception::error
{
   // acme class for resource-critical acme API exceptions
   // handles composite and initialization of an error message
public:


   overflow_error(const char * pszMessage = nullptr);
   virtual ~overflow_error();


};



