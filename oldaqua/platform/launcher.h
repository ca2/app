#pragma once


class CLASS_DECL_AQUA launcher
{
public:


   int m_iStart;

   bool m_bPrivileged;

   launcher(int iStart = 11) { m_iStart = iStart; m_bPrivileged = false; }


   virtual bool ensure_executable() { return true; }

   virtual string get_executable_path() = 0;

   virtual string get_params() { return ""; }

   virtual bool start();

};






