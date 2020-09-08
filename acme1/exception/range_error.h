#pragma once


class CLASS_DECL_ACME range_error :
   public ::exception::error
{
   // acme class for resource-critical acme API exceptions
   // handles composite and initialization of an error message
public:


   range_error(const char * pszMessage = nullptr);
   virtual ~range_error();


};



