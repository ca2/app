#pragma once


class CLASS_DECL_ACID user_exception :
   public ::exception   // general ::account::user visible alert
{
public:


   user_exception(::enum_status estatus, const ::scoped_string & scopedstrMessage = nullptr);
   virtual ~user_exception();


};


