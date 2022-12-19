#pragma once


class CLASS_DECL_ACME range_exception :
   public ::exception
{
   // acme class for resource-critical acme API exceptions
   // handles composite and initialization of an error message
public:


   range_exception(const scoped_string & strMessage = nullptr);
   virtual ~range_exception();


};



