#pragma once


class CLASS_DECL_ACME user_exception :
   public ::exception::exception   // general ::account::user visible alert
{
public:


   user_exception(const ::e_status & estatus = error_failed, const char * pszMessage = nullptr);
   virtual ~user_exception();


};


