// created by Camilo 2021-02-02 06:50 BRT <3CamiloSasukeThomasBorregaardSoerensen
#pragma once


template < typename TYPE >
class status :
   public TYPE
{
public:


   ::e_status              m_estatus;


   status() { m_estatus = error_not_initialized; }


   status(const TYPE & _, const ::e_status& estatus = ::success) :
      TYPE(_),
      m_estatus(estatus)
   {

   }

   status(const TYPE&& _, const ::e_status& estatus = ::success) :
      TYPE(::move(_)),
      m_estatus(estatus)
   {

   }

   status(const ::e_status& estatus)
   {

      if (estatus == error_not_initialized)
      {

         m_estatus = ::error_failed;

      }
      else
      {

         m_estatus = estatus;

      }

   }


   status(::enum_status estatus)
   {

      if (estatus == error_not_initialized)
      {

         estatus = ::error_failed;

      }

      m_estatus = estatus;

   }


   status(nullptr_t)
   {

      m_estatus = error_null_result;

   }


   operator int() const { return is_ok() != false; }

   ::e_status estatus() const { return m_estatus; }

   bool is_ok() const { return ::succeeded(m_estatus); }

   using TYPE::operator =;


};


template < typename OBJECT >
class transport :
   public status < __pointer (OBJECT) >
{
public:


   using status < __pointer(OBJECT) >::status;
   using status < __pointer(OBJECT) >::operator =;


};







