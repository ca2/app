#pragma once


class CLASS_DECL_AURA hresult_exception :
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
