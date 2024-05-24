#pragma once


class CLASS_DECL_ACID range_exception :
   public ::exception
{
   // acid class for resource-critical acid API exceptions
   // handles composite and initialization of an error message
public:


   range_exception(const ::scoped_string & scopedstrMessage = nullptr);
   virtual ~range_exception();


};



