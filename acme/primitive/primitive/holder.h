// Created by camilo on 2021-01-16 03:42 BRT <3ThomasBorregaardSorensen!!
#pragma once


//void destroy_pointer(cairo_surface_t* p)
//{
//
//   cairo_surface_destroy(p);
//
//}


template < typename POINTER >
class holder
{
public:


   POINTER        m_p;


   holder() :
      m_p(nullptr)
   {

   }


   holder(POINTER p) :
      m_p(p)
   {

   }

   holder(const holder&) = delete;

   holder(holder&& holder) :
      m_p(holder.m_p)
   {

      holder.m_p = nullptr;

   }

   ~holder()
   {

      destroy();

   }


   void destroy()
   {

      if (m_p)
      {

         destroy_pointer(m_p);

         m_p = nullptr;

      }

   }


   holder& operator = (POINTER p)
   {

      if (m_p != p)
      {

         destroy();

         m_p = p;

      }

      return *this;

   }

   holder& operator = (holder && holder)
   {

      if (m_p != holder.m_p)
      {

         m_p = holder.m_p;

         holder.m_p = nullptr;

      }

      return *this;

   }

   operator POINTER() { return m_p; }

};


//using cairo_surface_holder = pointer_holder < cairo_surface_t* >;


CLASS_DECL_ACME void destroy_pointer(FILE * p);


using FILE_holder = holder < FILE * >;



