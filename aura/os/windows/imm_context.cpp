#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif
#include "imm_context.h"


imm_context::imm_context(::user::interaction * pinteraction) :
   m_pinteraction(pinteraction)
{

   HWND hwnd = m_pinteraction->get_handle();

   m_himc = ImmGetContext(hwnd);

}


imm_context::~imm_context()
{

   HWND hwnd = m_pinteraction->get_handle();

   ImmReleaseContext(hwnd, m_himc);

}



bool imm_context::close()
{

   return ImmSetOpenStatus(m_himc, false) != FALSE;

}


bool imm_context::is_opened() const
{

   return ImmGetOpenStatus(m_himc) != FALSE;

}


bool imm_context::close_candidate(index iIndex)
{

   return ImmNotifyIME(m_himc, NI_CLOSECANDIDATE, 0, (DWORD)iIndex) != FALSE;

}


string imm_context::get_string(int iStr)
{

   int iLen = ImmGetCompositionStringW(m_himc, iStr, nullptr, 0);

   wstring wstr;

   unichar * point = wstr.get_string_buffer(iLen);

   ImmGetCompositionStringW(m_himc, iStr, point, iLen);

   wstr.release_string_buffer();

   return wstr;

}


string imm_context::_get_candidate(int iList)
{

   memory mem;

   DWORD dwCount = 0;

   DWORD dwSize = ImmGetCandidateListW(m_himc, iList, 0, 0);

   if (dwSize == 0)
   {

      DWORD dw = GetLastError();

      output_debug_string("error " + __str(dw));

   }

   mem.set_size(dwSize);

   LPCANDIDATELIST pc = (LPCANDIDATELIST)mem.get_data();

   if (::is_null(pc))
   {

      return "";

   }

   ImmGetCandidateListW(m_himc, iList, pc, (DWORD)mem.get_size());

   int iTest = pc->dwOffset[0];

   auto iTest2 = (byte *)& pc->dwOffset[pc->dwCount] - (u8 *)pc;

   unichar * pwsz = (unichar *)(mem.get_data() + pc->dwOffset[pc->dwSelection]);

   return pwsz;

}


string imm_context::get_candidate()
{

   for (index i = 3; i >= 0; i--)
   {

      string str = _get_candidate((int)i);

      if (str.has_char())
      {

         return str;

      }

   }

   return "";

}




