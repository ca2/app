#pragma once


class CLASS_DECL_AURA os_history :
   virtual public ::apex::history
{
public:


   os_history(::object * pobject);
         
   
   virtual bool hist(const ::string &psz);


};



