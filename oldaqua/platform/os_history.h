#pragma once

class CLASS_DECL_AQUA os_history :
   virtual public ::aqua::history
{
public:

   os_history(::object * pobject);
         
   
   virtual bool hist(const char *psz);

};


