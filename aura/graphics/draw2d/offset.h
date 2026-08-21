// Created by camilo on 2025-07-14 00:41 <3ThomasBorregaardSørensen!!   
#pragma once


namespace draw2d
{


   class target_scope;


   class CLASS_DECL_AURA target_rectangle
   {
   protected:
      friend class target_scope;
      ::f64_point       m_pointTarget;
      ::f64_size        m_sizeTarget;
      bool m_bTargetRectangleModified = false;
   public:

      const ::f64_point & target_origin() const
      {
         return m_pointTarget;

      }
      const ::f64_size & target_size() const
      {
         return m_sizeTarget;

      }


      virtual ::f64_rectangle get_target_rectangle() const;

      virtual void set_target_rectangle(const ::f64_rectangle & rectangle);

      ///virtual void reset_target_rectangle();



      virtual void on_target_rectangle_update()
      {


      }

      virtual void defer_on_target_rectangle_update()
      {

         if (m_bTargetRectangleModified)
         {

            m_bTargetRectangleModified = false;

            on_target_rectangle_update();

         }

      }


      ::draw2d::target_scope target_scope();

      // virtual ::draw2d::offset_context offset_context()
      // {
      //
      //    return this;
      //
      // }
      //
      // virtual void _get(::draw2d::offset_context* poffsetcontext) = 0;
      // virtual void _set(::draw2d::offset_context* poffsetcontext) = 0;
      // virtual void x_offset(::f64 dx) = 0;
      // virtual void y_offset(::f64 dy) = 0;
      // virtual void offset(::f64 dx, ::f64 dy) = 0;
      // virtual void shift_impact_area(::f64 dx, ::f64 dy, ::f64 w, ::f64 h) = 0;
      // //virtual void _set_impact_area(::f64 w, ::f64 h) = 0;
      // //virtual void _apply_offset() = 0;

   };



   // class offsetable;
   //
   //
   // class x_offsetable
   // {
   // public:
   //
   //
   //    virtual void x_offset(::f64 dx) = 0;
   //
   // };
   //
   //
   // class y_offsetable
   // {
   // public:
   //
   //    virtual void y_offset(::f64 dy) = 0;
   //
   // };

   //
   // class x_offset
   // {
   // public:
   //
   //    x_offsetable* m_pxoffsetable;
   //
   //
   //    x_offset(x_offsetable* pxoffsetable) :
   //       m_pxoffsetable(pxoffsetable)
   //    {
   //
   //    }
   //
   //    template < prototype_number NUMBER>
   //    x_offset& operator +=(NUMBER dx)
   //    {
   //       m_pxoffsetable->x_offset((::f64) dx);
   //       return *this;
   //    }
   //
   //    template < prototype_number NUMBER>
   //    x_offset& operator -=(NUMBER dx)
   //    {
   //       m_pxoffsetable->x_offset(-(::f64) dx);
   //       return *this;
   //    }
   //
   // };
   //
   //
   // class y_offset
   // {
   // public:
   //
   //    y_offsetable* m_pyoffsetable;
   //
   //    y_offset(y_offsetable* pyoffsetable) :
   //       m_pyoffsetable(pyoffsetable)
   //    {
   //
   //    }
   //
   //
   //    template < prototype_number NUMBER>
   //    y_offset& operator +=(NUMBER dy)
   //    {
   //       m_pyoffsetable->y_offset((::f64) dy);
   //       return *this;
   //    }
   //
   //
   //    template < prototype_number NUMBER>
   //    y_offset& operator -=(NUMBER dy)
   //    {
   //       m_pyoffsetable->y_offset(-(::f64) dy);
   //       return *this;
   //    }
   //
   // };
   //

   class CLASS_DECL_AURA target_scope
      //:
      //public x_offsetable,
      //public y_offsetable
   {
   public:

      target_rectangle * m_ptargetrectangle;
      ::f64_point m_pointTargetBefore;
      ::f64_size m_sizeTargetBefore;

      target_scope(target_rectangle* ptargetrectangle):
      m_ptargetrectangle(ptargetrectangle),
         m_pointTargetBefore(ptargetrectangle->m_pointTarget),
         m_sizeTargetBefore(ptargetrectangle->m_sizeTarget)
      {


      }
      ~target_scope()
      {

         m_ptargetrectangle->m_pointTarget = m_pointTargetBefore;
         m_ptargetrectangle->m_sizeTarget = m_sizeTargetBefore;

         m_ptargetrectangle->on_target_rectangle_update();

      }

      void offset_x(::f64 f)
      {

         m_ptargetrectangle->m_pointTarget.x += f;
         m_ptargetrectangle->m_bTargetRectangleModified = true;

      }

      void offset_y(::f64 f)
      {

         m_ptargetrectangle->m_pointTarget.y += f;
         m_ptargetrectangle->m_bTargetRectangleModified = true;

      }

      void defer_update()
      {

         if (m_ptargetrectangle->m_bTargetRectangleModified)
         {

            m_ptargetrectangle->defer_on_target_rectangle_update();

         }

      }


      // ::draw2d::x_offset Δx()
      // {
      //    return this;
      // }
      //
      // ::draw2d::y_offset Δy()
      // {
      //    return this;
      // }
      //
      // virtual void x_offset(::f64 dx);
      // virtual void y_offset(::f64 dy);
      // virtual void offset(::f64 dx, ::f64 dy);
      // virtual void shift_impact_area(::f64 dx, ::f64 dy, ::f64 w, ::f64 h);
      //
      target_scope& operator +=(const ::f64_size& size)
      {

         m_ptargetrectangle->m_pointTarget += size;

         m_ptargetrectangle->m_bTargetRectangleModified = true;

         return *this;

      }

      target_scope& operator -=(const ::f64_size& size)
      {

         m_ptargetrectangle->m_pointTarget -= size;

         m_ptargetrectangle->m_bTargetRectangleModified = true;

         return *this;

      }


      target_scope& offset_and_set_size(const ::f64_rectangle& rectangle)
      {

         m_ptargetrectangle->m_pointTarget += rectangle.origin();
         m_ptargetrectangle->m_sizeTarget = rectangle.size();
         m_ptargetrectangle->m_bTargetRectangleModified = true;

         return *this;

      }



   };




} // namespace draw2d



