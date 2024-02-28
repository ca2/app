#pragma once


class CLASS_DECL_ACME invalid_argument_exception :
   public ::exception
{
public:


   invalid_argument_exception(const ::scoped_string & scopedstrMessage = nullptr);
   virtual ~invalid_argument_exception();


};

