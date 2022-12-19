#pragma once


class CLASS_DECL_ACME operation_canceled_exception :
   public ::exception
{
public:


   operation_canceled_exception(const scoped_string & strMessage = nullptr);
   virtual ~operation_canceled_exception();


};

