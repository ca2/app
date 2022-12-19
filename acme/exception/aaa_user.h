#pragma once


class CLASS_DECL_ACME user_exception :
   public ::exception   // general ::account::user visible alert
{
public:


   user_exception(::enum_status estatus, const scoped_string & strMessage = nullptr);
   virtual ~user_exception();


};


