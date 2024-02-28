#pragma once


class CLASS_DECL_ACME operation_canceled_exception :
   public ::exception
{
public:


   operation_canceled_exception(const ::scoped_string & scopedstrMessage = nullptr);
   virtual ~operation_canceled_exception();


};

