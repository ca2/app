#pragma once


//#include "exception.h"


class CLASS_DECL_ACID cancel_exception :
   public ::exception
{
public:


   cancel_exception(const ::scoped_string & scopedstrMessage = nullptr);
   virtual ~cancel_exception();


   //virtual bool get_error_message(string & str,P::u32 pnHelpContext = nullptr);


};


