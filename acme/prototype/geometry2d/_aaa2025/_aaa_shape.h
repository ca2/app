//
//  shape.hpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 01/10/20.
//  Copyright (c) 2020 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once


//#include "_geometry2d.h"
#include "../_collection.h"
//#include "_polygon.h"


//#include "acme/prototype/prototype/element.h"
#include "acme/exception/interface_only.h"


template < typename HOLDEE >
class ___shape :
virtual public ::particle
{
protected:


   enum_shape     m_eshape;
   

   ___shape(enum_shape eshape) : m_eshape(eshape) { }
   ~___shape() override {}

public:


   inline enum_shape eshape() const { return m_eshape; }
   virtual void * raw_type() const {return nullptr;}


   virtual HOLDEE * holdee() { return nullptr; }
   virtual const HOLDEE * holdee() const { return nullptr; }
   virtual void holdee(HOLDEE *) {}

   template < typename SHAPE >
   SHAPE & shape() { return *(SHAPE *)raw_type(); }


   template < typename SHAPE >
   const SHAPE & shape() const { return *(SHAPE *)raw_type(); }


   virtual bool expand_bounding_rect(::f64_rectangle & rectangle) const;

   virtual bool expand_bounding_rect(::i32_rectangle & rectangle) const;

   virtual bool get_bounding_box(::f64_rectangle & rectangle) const;

   virtual bool get_bounding_box(::i32_rectangle & prectangle) const;

   virtual bool contains(const ::i32_point & point) const;

   virtual bool contains(const ::f64_point & point) const;


};


template < typename HOLDEE >
class begin_clip_shape :
virtual public ___shape < HOLDEE >
{
public:

   begin_clip_shape():___shape< HOLDEE>(e_shape_begin_clip) {}

   ::particle * clone() const override
   {

      return ___new begin_clip_shape();

   }

};


template < typename HOLDEE >
class intersect_clip_shape :
virtual public ___shape < HOLDEE >
{
public:


   intersect_clip_shape():___shape< HOLDEE>(e_shape_intersect_clip) {}


   ::particle * clone() const override
   {

      return ___new intersect_clip_shape();

   }

};


template < typename HOLDEE >
class begin_figure_shape :
   virtual public ___shape < HOLDEE >
{
public:

   begin_figure_shape() :___shape< HOLDEE>(e_shape_begin_figure) {}

   ::particle * clone() const override
   {

      return ___new begin_figure_shape();

   }

};


template < typename HOLDEE >
class close_figure_shape :
   virtual public ___shape < HOLDEE >
{
public:

   close_figure_shape() :___shape< HOLDEE>(e_shape_close_figure) {}

   ::particle * clone() const override
   {

      return ___new close_figure_shape();

   }

};


template < typename HOLDEE >
class end_figure_shape :
   virtual public ___shape < HOLDEE >
{
public:

   end_figure_shape() :___shape< HOLDEE>(e_shape_end_figure) {}

   ::particle * clone() const override
   {

      return ___new end_figure_shape();

   }


};



template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
class _shape :
virtual public ___shape < HOLDEE >
{
public:


   SHAPE                m_shape;

   ::pointer<HOLDEE>   m_pholdee;


   _shape():___shape< HOLDEE>(ESHAPE) {}
   _shape(const SHAPE & shape) : ___shape< HOLDEE>(ESHAPE), m_shape(shape) {}
   ~_shape() override {}


   HOLDEE * holdee() override { return m_pholdee; }
   const HOLDEE * holdee() const override { return m_pholdee; }
   void holdee(HOLDEE * pholdee) override { m_pholdee = pholdee; }


   virtual void * raw_type() const override { return (void*) &m_shape; }


   bool expand_bounding_rect(::f64_rectangle & prectangle) const override;


   bool expand_bounding_rect(::i32_rectangle & prectangle) const override;


   bool get_bounding_box(::f64_rectangle & prectangle) const override;


   bool get_bounding_box(::i32_rectangle & prectangle) const override;


   bool contains(const ::i32_point & point) const override;


   bool contains(const ::f64_point & point) const override;


   ::particle * clone() const override
   {

      return ___new _shape(m_shape);

   }


};






//using arc_shape = _shape < ::arc, e_shape_arc>;
//using line_shape = _shape < ::line, e_shape_line >;
//using rectangle_shape = _shape < ::f64_rectangle, e_shape_rectangle >;
//using ellipse_shape = _shape < ::f64_ellipse, e_shape_ellipse >;
//using lines_shape = _shape < ::lines, e_shape_lines >;
//using polygon_shape = _shape < ::polygon, e_shape_polygon >;


// template < typename GEOMETRY >
// inline ::pointer<___shape>__create_shape(const GEOMETRY& geometry);

// template < typename HOLDE >
// class shape_factory
// {
// public:
// // template < typename GEOMETRY >
// // inline ::pointer<___shape>__create_shape(const GEOMETRY& geometry);

// };




template < typename GEOMETRY, typename HOLDEE >
inline pointer< ___shape < HOLDEE > > __create_shape(const GEOMETRY& geometry, holdee < HOLDEE >)
{

   throw interface_only();

   return nullptr;

}

template < typename HOLDEE >
inline pointer< ___shape < HOLDEE > > __create_shape(const enum_shape& eshape);


template < typename HOLDEE >
bool ___shape <HOLDEE>::expand_bounding_rect(::f64_rectangle & rectangle) const
{

   ::f64_rectangle r;

   if (!get_bounding_box(r))
   {

      return false;

   }

   expand_rect(rectangle, r);

   return true;

}


template < typename HOLDEE >
bool ___shape<HOLDEE>::expand_bounding_rect(::i32_rectangle & rectangle) const
{

   ::f64_rectangle r;

   if (!expand_bounding_rect(r))
   {

      return false;

   }

   expand_rect(rectangle, r);

   return true;

}


template < typename HOLDEE >
bool ___shape<HOLDEE>::get_bounding_box(::f64_rectangle & rectangle) const
{

   ::null(rectangle);

   return false;

}


template < typename HOLDEE >
bool ___shape<HOLDEE>::get_bounding_box(::i32_rectangle & rectangle) const
{

   ::null(rectangle);

   return false;

}


template < typename HOLDEE >
bool ___shape<HOLDEE>::contains(const ::i32_point & point) const
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::i32_rectangle r;

   if (!get_bounding_box(r))
   {

      return false;

   }

   return r.contains(point);

}



template < typename HOLDEE >
bool ___shape<HOLDEE>::contains(const ::f64_point & point) const
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::f64_rectangle r;

   if (!get_bounding_box(r))
   {

      return false;

   }

   return r.contains(point);

}






template < prototype_number NUMBER, typename HOLDEE >
using arc_shape = _shape < ::arc_type < NUMBER >, e_shape_arc, HOLDEE >;

template < prototype_number NUMBER, typename HOLDEE >
using line_shape = _shape < ::line_base < NUMBER >, e_shape_line, HOLDEE >;

template < prototype_number NUMBER, typename HOLDEE >
using rectangle_shape = _shape < ::rectangle_type < NUMBER >, e_shape_rectangle, HOLDEE >;

template < prototype_number NUMBER, typename HOLDEE >
using ellipse_shape = _shape < ::ellipse_base < NUMBER >, e_shape_ellipse, HOLDEE >;

template < prototype_number NUMBER, typename HOLDEE >
using lines_shape = _shape < ::lines_base < NUMBER >, e_shape_lines, HOLDEE >;

template < prototype_number NUMBER, typename HOLDEE >
using polygon_shape = _shape < ::polygon_base < NUMBER >, e_shape_polygon, HOLDEE >;


template < typename HOLDEE >
using arc_f64_shape = arc_shape < ::f64, HOLDEE >;

template < typename HOLDEE >
using f64_line_shape = line_shape < ::f64, HOLDEE >;

template < typename HOLDEE >
using f64_rectangle_shape = rectangle_shape < ::f64, HOLDEE >;

template < typename HOLDEE >
using ellipse_f64_shape = ellipse_shape < ::f64, HOLDEE >;

template < typename HOLDEE >
using lines_f64_shape = lines_shape < ::f64, HOLDEE >;

template < typename HOLDEE >
using f64_polygon_shape = polygon_shape < ::f64, HOLDEE >;



