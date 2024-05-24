#pragma once


class CLASS_DECL_ACID overflow_exception :
   public ::exception
{
   // acid class for resource-critical acid API exceptions
   // handles composite and initialization of an error message
public:


   overflow_exception(const ::scoped_string & scopedstrMessage = nullptr);
   virtual ~overflow_exception();


};



