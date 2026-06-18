// Created by camilo on 2026-06-04 19:22 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "GraphicsObject.h"
#include "subsystem/platform/Particle.h"
#include "acme/prototype/geometry2d/angle.h"


namespace innate_subsystem
{


   class PathInterface : 
      virtual public ::Particle
   {
   public:


      virtual void addArc(::f64 x, ::f64 y, ::f64 w, ::f64 h, const ::f64_angle &angleStart,
                           const ::f64_angle &angleSweep) = 0;

      virtual void closeFigure() = 0;


      //virtual void initialize_pen(enum_pen epen, ::f32 fWidth, const ::color::color &color) = 0;

      // virtual void destroyGObject() = 0;
      // protected:
      //    HPEN m_pen;
      //
      //    friend class Graphics;
   };


   class CLASS_DECL_INNATE_SUBSYSTEM PathComposite : virtual public Composite<PathInterface>
   {
   public:


      ImplementCompositeø(Path, path)

         // public:
         // Pen(::i32 type, ::i32 width, const ::color::color & color);
         // Pen();
         //~Pen() override;

         void addArc(::f64 x, ::f64 y, ::f64 w, ::f64 h, const ::f64_angle& angleStart,
            const ::f64_angle& angleSweep) override
      {

         m_ppath->addArc(x, y, w, h, angleStart, angleSweep);

      }

      void closeFigure() override
      {

         m_ppath->closeFigure();

      }

         // void * _HGDIOBJ() override;

      //   void initialize_pen(enum_pen epen, ::f32 fWidth, const ::color::color &color) override
      //{

      //   m_ppen->initialize_pen(epen, fWidth, color);
      //}

      //void destroyGraphicsObject() override { m_ppen->destroyGraphicsObject(); }

      // protected:
      //    HPEN m_pen;
      //
      //    friend class Graphics;
   };


   class CLASS_DECL_INNATE_SUBSYSTEM PathAggregate : virtual public Aggregate<PathComposite>
   {
   public:

      ImplementBaseø(Path);
   };

   class CLASS_DECL_INNATE_SUBSYSTEM Path : virtual public Object<PathAggregate>
   {
   public:

      ImplementObjectø(Path)
   };


} // namespace innate_subsystem
