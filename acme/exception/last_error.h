#pragma once

#ifdef WINDOWS
class CLASS_DECL_ACME last_error_exception :
   virtual public hresult_exception
{
public:

   
   last_error_exception();
   ~last_error_exception();


};


#endif