#pragma once


class CLASS_DECL_ACME os_exception :
   public ::exception
{
public:


   os_exception(const scoped_string & strMessage = nullptr);
   virtual ~os_exception();


};

