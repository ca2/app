//
//  shape.hpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 01/10/20.
//  Copyright © 2020 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#pragma once


template < typename HOLDEE >
class ___shape :
   virtual public element
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


   virtual bool expand_bounding_rect(RECTANGLE_F64* prectangle) const;

   virtual bool expand_bounding_rect(RECTANGLE_I32* prectangle) const;

   virtual bool get_bounding_rectangle(RECTANGLE_F64* prectangle) const;

   virtual bool get_bounding_rectangle(RECTANGLE_I32* prectangle) const;

   virtual bool contains(const ::point_f64& point) const;

};


template < typename HOLDEE >
class begin_clip_shape :
virtual public ___shape < HOLDEE >
{
public:

   begin_clip_shape():___shape< HOLDEE>(e_shape_begin_clip) {}

   ::element * clone() const override
   {

      return memory_new begin_clip_shape();

   }

};


template < typename HOLDEE >
class intersect_clip_shape :
virtual public ___shape < HOLDEE >
{
public:


   intersect_clip_shape():___shape< HOLDEE>(e_shape_intersect_clip) {}


   ::element * clone() const override
   {

      return memory_new intersect_clip_shape();

   }

};


template < typename HOLDEE >
class begin_figure_shape :
   virtual public ___shape < HOLDEE >
{
public:

   begin_figure_shape() :___shape< HOLDEE>(e_shape_begin_figure) {}

   ::element * clone() const override
   {

      return memory_new begin_figure_shape();

   }

};


template < typename HOLDEE >
class close_figure_shape :
   virtual public ___shape < HOLDEE >
{
public:

   close_figure_shape() :___shape< HOLDEE>(e_shape_close_figure) {}

   ::element * clone() const override
   {

      return memory_new close_figure_shape();

   }

};


template < typename HOLDEE >
class end_figure_shape :
   virtual public ___shape < HOLDEE >
{
public:

   end_figure_shape() :___shape< HOLDEE>(e_shape_end_figure) {}

   ::element * clone() const override
   {

      return memory_new end_figure_shape();

   }


};



template < typename SHAPE, enum_shape ESHAPE, typename HOLDEE >
class _shape :
virtual public ___shape < HOLDEE >
{
public:


   SHAPE                m_shape;

   __pointer(HOLDEE)    m_pholdee;


   _shape():___shape< HOLDEE>(ESHAPE) {}
   _shape(const SHAPE & shape) : ___shape< HOLDEE>(ESHAPE), m_shape(shape) {}
   ~_shape() override {}


   HOLDEE * holdee() override { return m_pholdee; }
   const HOLDEE * holdee() const override { return m_pholdee; }
   void holdee(HOLDEE * pholdee) override { m_pholdee = pholdee; }


   virtual void * raw_type() const override { return (void*) &m_shape; }


   virtual bool expand_bounding_rect(RECTANGLE_F64* prectangle) const override;


   virtual bool expand_bounding_rect(RECTANGLE_I32* prectangle) const override;


   virtual bool get_bounding_rectangle(RECTANGLE_F64* prectangle) const override;


   virtual bool get_bounding_rectangle(RECTANGLE_I32* prectangle) const override;


   virtual bool contains(const ::POINT_I32 & point) const;


   virtual bool contains(const ::POINT_F64 & point) const;

   ::element * clone() const override
   {

      return memory_new _shape(m_shape);

   }
};




//using line = ::line_f64;
//using rectangle = ::rectangle_f64;
//using ellipse = ::ellipse_f64;
//using lines = ::lines_f64;
//using polygon = ::polygon_f64;


//using arc_shape = _shape < ::arc, e_shape_arc>;
//using line_shape = _shape < ::line, e_shape_line >;
//using rectangle_shape = _shape < ::rectangle, e_shape_rectangle >;
//using ellipse_shape = _shape < ::ellipse, e_shape_ellipse >;
//using lines_shape = _shape < ::lines, e_shape_lines >;
//using polygon_shape = _shape < ::polygon, e_shape_polygon >;


// template < typename GEOMETRY >
// inline __pointer(___shape) __create_shape(const GEOMETRY& geometry);

// template < typename HOLDE >
// class shape_factory
// {
// public:
// // template < typename GEOMETRY >
// // inline __pointer(___shape) __create_shape(const GEOMETRY& geometry);

// };




template < typename GEOMETRY, typename HOLDEE >
inline __pointer(___shape < HOLDEE >) __create_shape(const GEOMETRY& geometry, holdee < HOLDEE >)
{

   throw interface_only();

   return nullptr;

}

template < typename HOLDEE >
inline __pointer(___shape < HOLDEE >) __create_shape(const enum_shape& eshape);


template < typename HOLDEE >
bool ___shape <HOLDEE>::expand_bounding_rect(RECTANGLE_F64* prectangle) const
{

   rectangle_f64 r;

   if (!get_bounding_rectangle(&r))
   {

      return false;

   }

   expand_rect(prectangle, r);

   return true;

}


template < typename HOLDEE >
bool ___shape<HOLDEE>::expand_bounding_rect(RECTANGLE_I32* prectangle) const
{

   rectangle_f64 r;

   if (!expand_bounding_rect(&r))
   {

      return false;

   }

   expand_rect(prectangle, r);

   return true;

}


template < typename HOLDEE >
bool ___shape<HOLDEE>::get_bounding_rectangle(RECTANGLE_F64* prectangle) const
{

   ::null_rect(prectangle);

   return false;

}


template < typename HOLDEE >
bool ___shape<HOLDEE>::get_bounding_rectangle(RECTANGLE_I32* prectangle) const
{

   ::null_rect(prectangle);

   return false;

}


template < typename HOLDEE >
bool ___shape<HOLDEE>::contains(const ::point_f64& point) const
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::rectangle_f64 r;

   if (!get_bounding_rectangle(r))
   {

      return false;

   }

   return r.contains(point);

}






template < typename HOLDEE >
using arc_shape = _shape < ::arc, e_shape_arc, HOLDEE >;

template < typename HOLDEE >
using line_shape = _shape < ::line, e_shape_line, HOLDEE >;

template < typename HOLDEE >
using rectangle_shape = _shape < ::rectangle, e_shape_rectangle, HOLDEE >;

template < typename HOLDEE >
using ellipse_shape = _shape < ::ellipse, e_shape_ellipse, HOLDEE >;

template < typename HOLDEE >
using lines_shape = _shape < ::lines, e_shape_lines, HOLDEE >;

template < typename HOLDEE >
using polygon_shape = _shape < ::polygon, e_shape_polygon, HOLDEE >;




