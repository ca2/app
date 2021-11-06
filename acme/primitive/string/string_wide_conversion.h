#pragma once


//class string;


class CLASS_DECL_ACME wtostring :
   public wstring
{
public:


   string * m_pstringUtf8;


   wtostring(string & str, i32 iAllocCount);
   ~wtostring();


   inline operator const widechar * () { return this->m_pdata; }
   inline operator widechar * () { return this->m_pdata; }


};



