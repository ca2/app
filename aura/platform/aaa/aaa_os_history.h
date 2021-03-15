#pragma once


class CLASS_DECL_AURA os_history :
   virtual public ::apex::history
{
public:


   os_history(::context_object * pcontextobject);
         
   
   virtual bool hist(const char *psz);


};



