#pragma once


class CLASS_DECL_ACME overflow_exception :
   public ::exception
{
   // acme class for resource-critical acme API exceptions
   // handles composite and initialization of an error message
public:


   overflow_exception(const ::scoped_string & scopedstrMessage = nullptr);
   virtual ~overflow_exception();


};



