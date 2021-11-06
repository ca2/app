#pragma once


class CLASS_DECL_ACME overflow_exception :
   public ::exception
{
   // acme class for resource-critical acme API exceptions
   // handles composite and initialization of an error message
public:


   overflow_exception(const char * pszMessage = nullptr);
   virtual ~overflow_exception();


};



