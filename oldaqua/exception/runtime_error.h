#pragma once


class CLASS_DECL_AQUA runtime_error :
   public ::exception::error
{
   // aqua class for resource-critical aqua API exceptions
   // handles composite and initialization of an error message
public:


   runtime_error(const char * pszMessage = nullptr);
   virtual ~runtime_error();

};
