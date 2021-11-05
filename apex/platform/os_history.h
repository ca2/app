#pragma once

class CLASS_DECL_APEX os_history :
   virtual public ::apex::history
{
public:

   os_history(::object * pobject);
         
   
   virtual bool hist(const char *psz);

};


