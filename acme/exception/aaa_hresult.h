#pragma once

#ifdef WINDOWS
class CLASS_DECL_ACME hresult_exception :
   public ::exception::exception
{
public:


   HRESULT     m_hr;


   hresult_exception(HRESULT hr);
   virtual ~hresult_exception();


   operator HRESULT () const
   {

      return m_hr;

   }

};
#endif