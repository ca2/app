#pragma once


////#include "acme/prototype/prototype/object.h"


class CLASS_DECL_APEX launcher :
   virtual public ::object
{
public:


   ::i32 m_iStart;

   bool m_bPrivileged;

   launcher(::i32 iStart = 11) { m_iStart = iStart; m_bPrivileged = false; }


   virtual bool ensure_executable() { return true; }

   virtual string get_executable_path() = 0;

   virtual string get_params() { return ""; }

   virtual void start();

};






