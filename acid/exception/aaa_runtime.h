#pragma once


class CLASS_DECL_ACID runtime_exception :
   public ::exception
{
   // acid class for resource-critical acid API exceptions
   // handles composite and initialization of an error message
public:


   runtime_exception(const ::scoped_string & scopedstrMessage = nullptr);
   virtual ~runtime_exception();

};
