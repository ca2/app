#pragma once


class CLASS_DECL_ACME range_exception :
   public ::exception::exception
{
   // acme class for resource-critical acme API exceptions
   // handles composite and initialization of an error message
public:


   range_exception(const char * pszMessage = nullptr);
   virtual ~range_exception();


};



