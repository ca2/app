#pragma once


namespace aura
{


   template < class AXIS >
   void gudo < AXIS > ::gudo_get()
   {

      Application.gudo_get(m_strKey,*this);

   }


   template < class AXIS >
   void gudo < AXIS > ::gudo_set()
   {

      Application.gudo_set(m_strKey,*this);

   }


} // namespace aura







