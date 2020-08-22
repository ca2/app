#pragma once

class CLASS_DECL_AURA wait_cursor :
   virtual public ::object
{
public:
   wait_cursor(::object * pobject);
   virtual ~wait_cursor();

public:
   void Restore();
};
