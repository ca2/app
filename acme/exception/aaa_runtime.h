#pragma once


class CLASS_DECL_ACME runtime_exception :
   public ::exception
{
   // acme class for resource-critical acme API exceptions
   // handles composite and initialization of an error message
public:


   runtime_exception(const ::scoped_string & scopedstrMessage = nullptr);
   virtual ~runtime_exception();

};
