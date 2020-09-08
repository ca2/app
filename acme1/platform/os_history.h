#pragma once

class CLASS_DECL_ACME os_history :
   virtual public ::acme::history
{
public:

   os_history(::generic * pobject);
         
   
   virtual bool hist(const char *psz);

};


