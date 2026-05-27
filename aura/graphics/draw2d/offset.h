// Created by camilo on 2025-07-14 00:41 <3ThomasBorregaardSørensen!!   
#pragma once


namespace draw2d
{


   class offsetable;


   class x_offsetable
   {
   public:


      virtual void x_offset(::f64 dx) = 0;

   };


   class y_offsetable
   {
   public:

      virtual void y_offset(::f64 dy) = 0;

   };


   class x_offset
   {
   public:

      x_offsetable* m_pxoffsetable;


      x_offset(x_offsetable* pxoffsetable) :
         m_pxoffsetable(pxoffsetable)
      {

      }

      template < prototype_number NUMBER>
      x_offset& operator +=(NUMBER dx)
      {
         m_pxoffsetable->x_offset((::f64) dx);
         return *this;
      }

      template < prototype_number NUMBER>
      x_offset& operator -=(NUMBER dx)
      {
         m_pxoffsetable->x_offset(-(::f64) dx);
         return *this;
      }

   };


   class y_offset
   {
   public:

      y_offsetable* m_pyoffsetable;

      y_offset(y_offsetable* pyoffsetable) :
         m_pyoffsetable(pyoffsetable)
      {

      }


      template < prototype_number NUMBER>
      y_offset& operator +=(NUMBER dy)
      {
         m_pyoffsetable->y_offset((::f64) dy);
         return *this;
      }


      template < prototype_number NUMBER>
      y_offset& operator -=(NUMBER dy)
      {
         m_pyoffsetable->y_offset(-(::f64) dy);
         return *this;
      }

   };


   class CLASS_DECL_AURA offset_context :
      public x_offsetable,
      public y_offsetable
   {
   public:

      offsetable* m_poffsetable;
      ::f64_point m_point;
      ::f64_size m_size;

      offset_context(offsetable* poffsetable);
      ~offset_context();


      ::draw2d::x_offset Δx()
      {
         return this;
      }

      ::draw2d::y_offset Δy()
      {
         return this;
      }

      virtual void x_offset(::f64 dx);
      virtual void y_offset(::f64 dy);
      virtual void offset(::f64 dx, ::f64 dy);
      virtual void shift_impact_area(::f64 dx, ::f64 dy, ::f64 w, ::f64 h);

      offset_context& operator +=(const ::f64_size& size)
      {

         offset(size.cx, size.cy);

         return *this;

      }

      offset_context& operator -=(const ::f64_size& size)
      {

         offset(-size.cx, -size.cy);

         return *this;

      }


      offset_context& operator +=(const ::f64_rectangle& rectangle)
      {

         shift_impact_area(rectangle.left, rectangle.top, rectangle.width(), rectangle.height());

         return *this;

      }



   };

   class offsetable
   {
   public:


      virtual ::draw2d::offset_context offset_context()
      {

         return this;

      }

      virtual void _get(::draw2d::offset_context* poffsetcontext) = 0;
      virtual void _set(::draw2d::offset_context* poffsetcontext) = 0;
      virtual void x_offset(::f64 dx) = 0;
      virtual void y_offset(::f64 dy) = 0;
      virtual void offset(::f64 dx, ::f64 dy) = 0;
      virtual void shift_impact_area(::f64 dx, ::f64 dy, ::f64 w, ::f64 h) = 0;
      //virtual void _set_impact_area(::f64 w, ::f64 h) = 0;
      //virtual void _apply_offset() = 0;

   };



} // namespace draw2d



