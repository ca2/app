// Common/Exception.h
// from 7-zip on 2012-12-23, dawn
#pragma once

#ifdef WINDOWS
class CLASS_DECL_ACME system_exception :
   public ::exception
{
public:


   HRESULT m_hr;


   system_exception(HRESULT hr) :
      m_hr(hr)
   {

   }


};



#endif
