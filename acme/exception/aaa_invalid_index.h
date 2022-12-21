#pragma once


class CLASS_DECL_ACME invalid_index_exception :
   public invalid_argument_exception
{
public:


   invalid_index_exception(const ::scoped_string & scopedstrMessage = nullptr);
   virtual ~invalid_index_exception();


};

