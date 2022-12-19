#pragma once


class CLASS_DECL_ACME temporary_exception :
   public ::exception
{
public:


   temporary_exception(const scoped_string & strMessage = nullptr);
   virtual ~temporary_exception();


};


