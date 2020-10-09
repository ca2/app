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
   e_shape_rect,
   e_shape_rectd,
   e_shape_oval,
   e_shape_ovald,
   e_shape_polygon,
   e_shape_polygond
   
};

class CLASS_DECL_ACME ___shape :
   virtual public element
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


template < typename SHAPE, enum_shape ESHAPE >
class __shape :
virtual public ___shape
{
public:
   

   SHAPE       m_shape;
   
   
   __shape():___shape(ESHAPE) {}
   __shape(const SHAPE & shape) : ___shape(ESHAPE), m_shape(shape) {}
   
   
   virtual void * raw_type() const { return (void*) &m_shape; }
   
   
};


using rect_shape = __shape < ::rect, e_shape_rect >;
using rectd_shape = __shape < ::rectd, e_shape_rectd >;
using oval_shape = __shape < ::oval, e_shape_oval >;
using ovald_shape = __shape < ::ovald, e_shape_ovald >;
using polygon_shape = __shape < ::polygon, e_shape_polygon >;
using polygond_shape = __shape < ::polygond, e_shape_polygond >;


using shape_array = __pointer_array( ___shape );




