// Created by camilo on 2021-01-16 03:42 BRT <3ThomasBorregaardSorensen!!
#pragma once


template < typename TYPE >
void destroy_pointer(TYPE * p)
{

   delete p;
   //cairo_surface_destroy(p);

}
template < typename TYPE >
TYPE * copy_pointer(const TYPE * p)
{

   return new TYPE(*p);

}


template < typename TYPE >
class holder
{

   TYPE *         m_p;

public:



   holder() :
      m_p(nullptr)
   {

   }


   holder(TYPE * p) :
      m_p(p)
   {

   }

   holder(const holder & holder)
   {

      m_p = copy_pointer(holder.m_p);

   }

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


   holder& operator = (TYPE * p)
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

   holder & operator = (const holder & holder)
   {

      destroy();

      m_p = copy_pointer(holder.m_p);

      return *this;

   }

   operator TYPE *() { return m_p; }

   operator const TYPE * () const { return m_p; }

   TYPE * operator -> () { return m_p; }

   const TYPE * operator -> () const { return m_p; }

   TYPE & operator *() { return *m_p; }

   const TYPE & operator *() const { return *m_p; }

};


//using cairo_surface_holder = pointer_holder < cairo_surface_t* >;



//template < typename TYPE >
//class heap_object
//{
//   TYPE        m_p;
//
//
//public:
//
//   heap_object(nullptr_t)
//   {
//      m_p = nullptr;
//   }
//
//   heap_object()
//   {
//      m_p = new TYPE;
//   }
//
//
//   heap_object(TYPE * p)
//   {
//
//      m_p = p;
//
//   }
//
//   heap_object(const heap_object & object)
//   {
//
//      m_p = new heap_object(object);
//
//   }
//
//
//   heap_object(heap_object && object) :
//      m_p(object.m_p)
//   {
//
//      object.m_p = nullptr;
//
//   }
//
//   ~heap_object()
//   {
//
//      destroy();
//
//   }
//
//
//   void destroy()
//   {
//
//      if (m_p)
//      {
//
//         delete m_p;
//
//         m_p = nullptr;
//
//      }
//
//   }
//
//
//   heap_object & operator = (TYPE * p)
//   {
//
//      if (m_p != p)
//      {
//
//         destroy();
//
//         m_p = p;
//
//      }
//
//      return *this;
//
//   }
//
//   heap_object & operator = (heap_object && object)
//   {
//
//      if (m_p != holder.m_p)
//      {
//
//         m_p = holder.m_p;
//
//         holder.m_p = nullptr;
//
//      }
//
//      return *this;
//
//   }
//
//   operator TYPE *() { return m_p; }
//
//};
//
//
//

//
//template < typename TYPE >
//class pointer_object
//{
//
//   TYPE * m_p;
//
//public:
//
//
//   pointer_object() :
//      m_p(nullptr)
//   {
//
//   }
//
//
//   pointer_object(TYPE * p) :
//      m_p(p)
//   {
//
//   }
//
//   pointer_object(const pointer_object & pointerobject)
//   {
//
//      m_p = copy_pointer(pointerobject.m_p);
//
//   }
//
//   pointer_object(pointer_object && pointerobject) :
//      m_p(pointerobject.m_p)
//   {
//
//      pointerobject.m_p = nullptr;
//
//   }
//
//   ~pointer_object()
//   {
//
//      destroy();
//
//   }
//
//
//   void destroy()
//   {
//
//      if (m_p)
//      {
//
//         destroy_pointer(m_p);
//
//         m_p = nullptr;
//
//      }
//
//   }
//
//
//   pointer_object & operator = (TYPE * p)
//   {
//
//      if (m_p != p)
//      {
//
//         destroy();
//
//         m_p = p;
//
//      }
//
//      return *this;
//
//   }
//
//   pointer_object & operator = (pointer_object && pointerobject)
//   {
//
//      if (m_p != pointerobject.m_p)
//      {
//
//         m_p = pointerobject.m_p;
//
//         pointerobject.m_p = nullptr;
//
//      }
//
//      return *this;
//
//   }
//
//   pointer_object & operator = (const pointer_object & pointerobject)
//   {
//
//      destroy();
//
//      m_p = copy_pointer(pointerobject.m_p);
//
//      return *this;
//
//   }
//
//   operator TYPE & () { return *m_p; }
//
//   operator const TYPE & () const { return *m_p; }
//
//};


//using cairo_surface_holder = pointer_holder < cairo_surface_t* >;



//template < typename TYPE >
//class heap_object
//{
//   TYPE        m_p;
//
//
//public:
//
//   heap_object(nullptr_t)
//   {
//      m_p = nullptr;
//   }
//
//   heap_object()
//   {
//      m_p = new TYPE;
//   }
//
//
//   heap_object(TYPE * p)
//   {
//
//      m_p = p;
//
//   }
//
//   heap_object(const heap_object & object)
//   {
//
//      m_p = new heap_object(object);
//
//   }
//
//
//   heap_object(heap_object && object) :
//      m_p(object.m_p)
//   {
//
//      object.m_p = nullptr;
//
//   }
//
//   ~heap_object()
//   {
//
//      destroy();
//
//   }
//
//
//   void destroy()
//   {
//
//      if (m_p)
//      {
//
//         delete m_p;
//
//         m_p = nullptr;
//
//      }
//
//   }
//
//
//   heap_object & operator = (TYPE * p)
//   {
//
//      if (m_p != p)
//      {
//
//         destroy();
//
//         m_p = p;
//
//      }
//
//      return *this;
//
//   }
//
//   heap_object & operator = (heap_object && object)
//   {
//
//      if (m_p != holder.m_p)
//      {
//
//         m_p = holder.m_p;
//
//         holder.m_p = nullptr;
//
//      }
//
//      return *this;
//
//   }
//
//   operator TYPE *() { return m_p; }
//
//};
//
//
//
