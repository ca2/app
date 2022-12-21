#pragma once


class CLASS_DECL_ACME temporary_exception :
   public ::exception
{
public:


   temporary_exception(const ::scoped_string & scopedstrMessage = nullptr);
   virtual ~temporary_exception();


};


