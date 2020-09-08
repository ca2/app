#pragma once


class CLASS_DECL_AQUA overflow_error :
   public ::exception::error
{
   // aqua class for resource-critical aqua API exceptions
   // handles composite and initialization of an error message
public:


   overflow_error(const char * pszMessage = nullptr);
   virtual ~overflow_error();


};



