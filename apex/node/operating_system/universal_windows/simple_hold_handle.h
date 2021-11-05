#pragma once


#ifdef WINDOWS

class CLASS_DECL_APEX simple_hold_handle
{
public:

   HANDLE m_handle;

   simple_hold_handle(HANDLE h)
   {
      m_handle = h;
   }

   ~simple_hold_handle()
   {
      ::CloseHandle(m_handle);
   }

};

#endif
