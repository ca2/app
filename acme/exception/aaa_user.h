#pragma once


class CLASS_DECL_ACME user_exception :
   public ::exception   // general ::account::user visible alert
{
public:


   user_exception(::enum_status estatus, const char * pszMessage = nullptr);
   virtual ~user_exception();


};


