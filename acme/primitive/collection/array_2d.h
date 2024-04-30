// Created by camilo on 2023-07-08 17:02 <3ThomasBorregaardSorensen!!
#pragma once


template < class TYPE, class ARG_TYPE >
class row :
   public range < TYPE * >
{
public:


   using BASE_RANGE = range < TYPE * >;


   // FISC - Flaw in some compiler

   //inline operator TYPE * () { return this->m_begin; }
   //inline operator const TYPE * () const { return this->m_begin; }

   
   inline TYPE & operator[](::raw::index i) { return this->m_begin[i]; }
   inline const TYPE & operator [](::raw::index i) const { return this->m_begin[i]; }


   row(TYPE * pbegin, TYPE * pend):BASE_RANGE(pbegin, pend) {}

};


template < class TYPE, class ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
class array_2d :
   virtual public ::array_base < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >
{
public:


   using BASE_ARRAY = ::array_base < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >;
   using row = ::row < TYPE, ARG_TYPE >;


   // FISC - Flaw in some compiler

//protected:
//
//
//   using BASE_ARRAY::operator TYPE *;
//   using BASE_ARRAY::operator const TYPE *;
//
//
//public:


   ::i64    m_iWidth;


   ::raw::count set_size(::raw::count w, ::raw::count h)
   {

      m_iWidth = w;

      return BASE_ARRAY::set_size(w * h);

   }

   ::raw::count set_size(::size_i32 size)
   {

      return this->set_size(size.cx(), size.cy());

   }


   ::size_i32 size() const
   {

      return { m_iWidth, BASE_ARRAY::size() / m_iWidth };

   }


   row operator [](::raw::index iRowIndex)
   {

      auto prowdata = this->begin() + m_iWidth * iRowIndex;

      return { prowdata, prowdata + m_iWidth };

   }


   const row operator [](::raw::index iRowIndex) const
   {

      auto prowdata = this->begin() + m_iWidth * iRowIndex;

      return { prowdata, prowdata + m_iWidth };

   }


   TYPE & element_at(::raw::index x, ::raw::index y)
   {

      return this->m_begin + m_iWidth * y + x;

   }


   const TYPE & element_at(::raw::index x, ::raw::index y) const
   {

      return this->m_begin + m_iWidth * y + x;

   }


   void set_at(::raw::index x, ::raw::index y, ARG_TYPE t)
   {

      element_at(x, y) = t;

   }

};


using i32_array_2d = ::array_2d < ::i32, ::i32 >;


using f32_array_2d = ::array_2d < ::f32, ::f32 >;


using f64_array_2d = ::array_2d < ::f64, ::f64 >;





