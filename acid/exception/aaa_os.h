#pragma once


class CLASS_DECL_ACID os_exception :
   public ::exception
{
public:


   os_exception(const ::scoped_string & scopedstrMessage = nullptr);
   virtual ~os_exception();


};

