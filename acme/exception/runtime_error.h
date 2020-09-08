#pragma once


class CLASS_DECL_ACME runtime_error :
   public ::exception::error
{
   // acme class for resource-critical acme API exceptions
   // handles composite and initialization of an error message
public:


   runtime_error(const char * pszMessage = nullptr);
   virtual ~runtime_error();

};
