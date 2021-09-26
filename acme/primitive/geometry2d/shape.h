//
//  shape.hpp
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 01/10/20.
//  Copyright © 2020 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


enum enum_shape
{

   e_shape_none,
   e_shape_begin_clip,
   e_shape_intersect_clip,
   e_shape_begin_figure,
   e_shape_close_figure,
   e_shape_end_figure,
   e_shape_arc,
   e_shape_line,
   e_shape_lines,
   e_shape_rectangle,
   e_shape_ellipse,
   e_shape_polygon,
   e_shape_text_out,
   e_shape_draw_text,

};


class CLASS_DECL_ACME ___shape :
   virtual public matter
{
protected:


   enum_shape     m_eshape;
   

   ___shape(enum_shape eshape) : m_eshape(eshape) { }
   ~___shape() override {}

public:


   inline enum_shape eshape() const { return m_eshape; }
   virtual void * raw_type() const {return nullptr;}


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


class CLASS_DECL_ACME begin_clip_shape :
virtual public ___shape
{
public:

   begin_clip_shape():___shape(e_shape_begin_clip) {}

};


class CLASS_DECL_ACME intersect_clip_shape :
virtual public ___shape
{
public:

   intersect_clip_shape():___shape(e_shape_intersect_clip) {}

};


class CLASS_DECL_ACME begin_figure_shape :
   virtual public ___shape
{
public:

   begin_figure_shape() :___shape(e_shape_begin_figure) {}

};


class CLASS_DECL_ACME close_figure_shape :
   virtual public ___shape
{
public:

   close_figure_shape() :___shape(e_shape_close_figure) {}

};


class CLASS_DECL_ACME end_figure_shape :
   virtual public ___shape
{
public:

   end_figure_shape() :___shape(e_shape_end_figure) {}

};



template < typename SHAPE, enum_shape ESHAPE >
class _shape :
virtual public ___shape
{
public:


   SHAPE       m_shape;


   _shape():___shape(ESHAPE) {}
   _shape(const SHAPE & shape) : ___shape(ESHAPE), m_shape(shape) {}
   ~_shape() override {}


   virtual void * raw_type() const { return (void*) &m_shape; }


   virtual bool expand_bounding_rect(RECTANGLE_F64* prectangle) const;


   virtual bool expand_bounding_rect(RECTANGLE_I32* prectangle) const;


   virtual bool get_bounding_rectangle(RECTANGLE_F64* prectangle) const;


   virtual bool get_bounding_rectangle(RECTANGLE_I32* prectangle) const;


   virtual bool contains(const ::POINT_I32 & point) const;


   virtual bool contains(const ::POINT_F64 & point) const;


};


using line = ::line_f64;
using rectangle = ::rectangle_f64;
using ellipse = ::ellipse_f64;
//using lines = ::lines_f64;
//using polygon = ::polygon_f64;


using arc_shape = _shape < ::arc, e_shape_arc>;
using line_shape = _shape < ::line, e_shape_line >;
using rectangle_shape = _shape < ::rectangle, e_shape_rectangle >;
using ellipse_shape = _shape < ::ellipse, e_shape_ellipse >;
//using lines_shape = _shape < ::lines, e_shape_lines >;
//using polygon_shape = _shape < ::polygon, e_shape_polygon >;


template < typename GEOMETRY >
inline __pointer(___shape) __create_shape(const GEOMETRY& geometry);


template < >
inline __pointer(___shape) __create_shape(const enum_shape& eshape);


//template < >
//inline __pointer(___shape) __create_shape(const ::line & line)
//{
//
//   return __new(line_shape(line));
//
//}


template < >
inline __pointer(___shape) __create_shape(const ::line & line)
{

   return __new(line_shape(line));

}


//template < >
//inline __pointer(___shape) __create_shape(const ::lines& lines);




//template < >
//inline __pointer(___shape) __create_shape(const ::rectangle_i32& rectangle)
//{
//
//   return __new(rect_shape(rectangle));
//
//}

template < >
inline __pointer(___shape) __create_shape(const ::rectangle & rectangle)
{

   return __new(rectangle_shape(rectangle));

}



