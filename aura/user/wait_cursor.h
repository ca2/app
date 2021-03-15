#pragma once


class CLASS_DECL_AURA wait_cursor :
   virtual public ::object
{
public:


   wait_cursor(::context_object * pcontextobject);
   virtual ~wait_cursor();


   void restore();


};



