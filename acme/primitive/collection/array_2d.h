// Created by camilo on 2023-07-08 17:02 <3ThomasBorregaardSorensen!!
#pragma once


template < class TYPE, class ARG_TYPE >
class row :
   public range < TYPE * >
{
public:


   inline operator TYPE * () { return this->m_begin; }
   inline operator const TYPE * () const { return this->m_begin; }


};


template < class TYPE, class ARG_TYPE, class ALLOCATOR, ::enum_type m_etypeContainer >
class array_2d :
   virtual public ::array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >
{
protected:


   inline operator TYPE * () { return this->m_begin; }
   inline operator const TYPE * () const { return this->m_begin; }


public:


   using BASE_ARRAY = ::array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >;
   using row = ::row < TYPE >;


   ::i64    m_iWidth;


   ::count set_size(::count w, ::count h, ::count nGrowBy = -1)
   {

      return BASE_ARRAY::set_size(w * h, nGrowBy);

   }

   ::count set_size(::size_i32 size, ::count nGrowBy = -1)
   {

      return BASE_ARRAY::set_size(size.cx(), size.cy(), nGrowBy);

   }


   ::size_i32 size() const
   {

      return { m_iWidth, BASE_ARRAY::size() / m_iWidth };

   }


   row operator [](::index iRowIndex)
   {

      auto prowdata = this->begin + m_iWidth * iRowIndex;

      return { prowdata, prowdata + m_iWidth };

   }


   const row operator [](::index iRowIndex) const
   {

      auto prowdata = this->begin + m_iWidth * iRowIndex;

      return { prowdata, prowdata + m_iWidth };

   }


   TYPE & element_at(::index x, ::index y)
   {

      return this->m_begin + m_iWidth * y + x;

   }


   const TYPE & element_at(::index x, ::index y) const
   {

      return this->m_begin + m_iWidth * y + x;

   }


   void set_at(::index x, ::index y, ARG_TYPE t)
   {

      element_at(x, y) = t;

   }

};


using ::i32_array_2d = ::array_2d < ::i32 >;


using ::f32_array_2d = ::array_2d < ::f32 >;


using ::f64_array_2d = ::array_2d < ::f64 >;





