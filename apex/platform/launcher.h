#pragma once


////#include "acme/primitive/primitive/object.h"


class CLASS_DECL_APEX launcher :
   virtual public ::object
{
public:


   int m_iStart;

   bool m_bPrivileged;

   launcher(int iStart = 11) { m_iStart = iStart; m_bPrivileged = false; }


   virtual bool ensure_executable() { return true; }

   virtual string get_executable_path() = 0;

   virtual string get_params() { return ""; }

   virtual void start();

};






