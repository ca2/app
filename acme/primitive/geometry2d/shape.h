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
   e_shape_lined,
   e_shape_lines,
   e_shape_linesd,
   e_shape_rect,
   e_shape_rectd,
   e_shape_oval,
   e_shape_ovald,
   e_shape_polygon,
   e_shape_polygond,
   e_shape_text_out,
   e_shape_draw_text,

};


class CLASS_DECL_ACME ___shape :
   virtual public matter
{
protected:


   enum_shape     m_eshape;

   ___shape(enum_shape eshape) : m_eshape(eshape) { }


public:


   inline enum_shape eshape() const { return m_eshape; }
   virtual void * raw_type() const {return nullptr;}


   template < typename SHAPE >
   SHAPE & shape() { return *(SHAPE *)raw_type(); }


   template < typename SHAPE >
   const SHAPE & shape() const { return *(SHAPE *)raw_type(); }


   virtual bool expand_bounding_rect(RECTD* prect) const;

   virtual bool expand_bounding_rect(RECT32* prect) const;

   virtual bool get_bounding_rect(RECTD* prect) const;

   virtual bool get_bounding_rect(RECT32* prect) const;

   virtual bool contains(const ::pointd& point) const;

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


   virtual void * raw_type() const { return (void*) &m_shape; }


   virtual bool expand_bounding_rect(RECTD* prect) const;


   virtual bool expand_bounding_rect(RECT32* prect) const;


   virtual bool get_bounding_rect(RECTD* prect) const;


   virtual bool get_bounding_rect(RECT32* prect) const;


   virtual bool contains(const ::POINT32 & point) const;


   virtual bool contains(const ::POINTD & point) const;


};


using arc_shape = _shape < ::arc, e_shape_arc>;
using line_shape = _shape < ::line, e_shape_line >;
using lined_shape = _shape < ::lined, e_shape_lined >;
using rect_shape = _shape < ::rect, e_shape_rect >;
using rectd_shape = _shape < ::rectd, e_shape_rectd >;
using oval_shape = _shape < ::oval, e_shape_oval >;
using ovald_shape = _shape < ::ovald, e_shape_ovald >;


template < typename GEOMETRY >
inline ___shape* __new_shape(const GEOMETRY& geometry);


template < >
inline ___shape* __new_shape(const enum_shape& eshape);


template < >
inline ___shape* __new_shape(const ::line & line)
{

   return new line_shape(line);

}


template < >
inline ___shape* __new_shape(const ::lined& line)
{

   return new lined_shape(line);

}


template < >
inline ___shape* __new_shape(const ::lines& lines);


template < >
inline ___shape* __new_shape(const ::linesd& lines);


template < >
inline ___shape* __new_shape(const ::rect& rect)
{

   return new rect_shape(rect);

}

template < >
inline ___shape* __new_shape(const ::rectd& rect)
{

   return new rectd_shape(rect);

}



