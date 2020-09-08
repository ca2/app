#pragma once


class CLASS_DECL_AQUA range_error :
   public ::exception::error
{
   // aqua class for resource-critical aqua API exceptions
   // handles composite and initialization of an error message
public:


   range_error(const char * pszMessage = nullptr);
   virtual ~range_error();


};



