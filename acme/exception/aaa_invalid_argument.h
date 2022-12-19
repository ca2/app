#pragma once


class CLASS_DECL_ACME invalid_argument_exception :
   public ::exception
{
public:


   invalid_argument_exception(const scoped_string & strMessage = nullptr);
   virtual ~invalid_argument_exception();


};

