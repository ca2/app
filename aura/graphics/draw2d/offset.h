// Created by camilo on 2025-07-14 00:41 <3ThomasBorregaardSørensen!!   
#pragma once


namespace draw2d
{


   class offsetable;


   class x_offsetable
   {
   public:


      virtual void x_offset(double dx) = 0;

   };


   class y_offsetable
   {
   public:

      virtual void y_offset(double dy) = 0;

   };


   class x_offset
   {
   public:

      x_offsetable* m_pxoffsetable;


      x_offset(x_offsetable* pxoffsetable) :
         m_pxoffsetable(pxoffsetable)
      {

      }

      template < primitive_number NUMBER>
      x_offset& operator +=(NUMBER dx)
      {
         m_pxoffsetable->x_offset((double) dx);
         return *this;
      }

      template < primitive_number NUMBER>
      x_offset& operator -=(NUMBER dx)
      {
         m_pxoffsetable->x_offset(-(double) dx);
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


      template < primitive_number NUMBER>
      y_offset& operator +=(NUMBER dy)
      {
         m_pyoffsetable->y_offset((double) dy);
         return *this;
      }


      template < primitive_number NUMBER>
      y_offset& operator -=(NUMBER dy)
      {
         m_pyoffsetable->y_offset(-(double) dy);
         return *this;
      }

   };


   class CLASS_DECL_AURA offset_context :
      public x_offsetable,
      public y_offsetable
   {
   public:

      offsetable* m_poffsetable;
      ::double_point m_point;
      ::double_size m_size;

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

      virtual void x_offset(double dx);
      virtual void y_offset(double dy);
      virtual void offset(double dx, double dy);
      virtual void shift_impact_area(double dx, double dy, double w, double h);

      offset_context& operator +=(const ::double_size& size)
      {

         offset(size.cx(), size.cy());

         return *this;

      }

      offset_context& operator -=(const ::double_size& size)
      {

         offset(-size.cx(), -size.cy());

         return *this;

      }


      offset_context& operator +=(const ::double_rectangle& rectangle)
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
      virtual void x_offset(double dx) = 0;
      virtual void y_offset(double dy) = 0;
      virtual void offset(double dx, double dy) = 0;
      virtual void shift_impact_area(double dx, double dy, double w, double h) = 0;
      //virtual void _set_impact_area(double w, double h) = 0;
      //virtual void _apply_offset() = 0;

   };



} // namespace draw2d



