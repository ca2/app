#pragma once


class CLASS_DECL_ACME runtime_exception :
   public ::exception::exception
{
   // acme class for resource-critical acme API exceptions
   // handles composite and initialization of an error message
public:


   runtime_exception(const char * pszMessage = nullptr);
   virtual ~runtime_exception();

};
