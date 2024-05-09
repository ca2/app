// Created by camilo on 2022-10-15 04:49 <3ThomasBorregaardSorensen!!
#pragma once


#include "core/user/rich_text/format.h"
#include "core/user/rich_text/span.h"
#include "core/user/rich_text/data.h"
#include "core/user/rich_text/edit_impl.h"
#include "acme/primitive/collection/_array_binary_stream.h"
#include "base/user/user/_binary_stream.h"


// template < typename FILE >
::binary_stream & operator <<(::binary_stream & stream, const ::user::rich_text::format & format)
{

   stream << format.m_bItalic;
   stream << format.m_bUnderline;
   stream << format.m_strFontFamily;
   stream << format.m_dFontSize;
   stream << format.m_colorForeground.m_u32;
   stream << format.m_colorBackground.m_u32;
   stream << (i32)format.m_escript;
   stream << (i32)format.m_elineheight;

   return stream;

}


// template < typename FILE >
::binary_stream & operator >>(::binary_stream & stream, ::user::rich_text::format &format)
{
             
   stream >> format.m_bItalic;
   stream >> format.m_bUnderline;
   stream >> format.m_strFontFamily;
   stream >> format.m_dFontSize;
   stream >> format.m_colorForeground.m_u32;
   stream >> format.m_colorBackground.m_u32;
   stream >> (i32 &)format.m_escript;
   stream >> (i32 &)format.m_elineheight;

   return stream;

}


// template < typename FILE >
::binary_stream & operator <<(::binary_stream & stream, const ::user::rich_text::span & span)
{

   property_set set;

   set["align"] = (i32)span.m_ealignNewLine;

   set["text"] = span.m_str;

   ::collection::index iFormatIndex = span.m_pdata->find_first(span.m_pformat);

   set["format_index"] = iFormatIndex;

   stream << set;

   return stream;

}


// template < typename FILE >
::binary_stream & operator >>(::binary_stream & stream, ::user::rich_text::span & span)
{

   property_set set;

   stream >> set;

   span.m_ealignNewLine = set["align"].e< ::enum_align>();

   span.m_str = set["text"];

   ::collection::index iFormatIndex;

   iFormatIndex = set["format_index"];

   if (iFormatIndex >= 0 && iFormatIndex < span.m_pdata->get_count())
   {

      span.m_pformat = span.m_pdata->element_at(iFormatIndex);

   }
   else
   {

      stream.informationf("corruption... non fatal... partially recoverable...");

   }

   return stream;

}


// template < typename FILE >
::binary_stream & operator <<(::binary_stream & stream, const ::user::rich_text::data & data)
{

   synchronous_lock synchronouslock(data.synchronization());

   stream << (const ::pointer_array< ::user::rich_text::format > &) data;

   stream << data.m_spana;

   return stream;

}


// template < typename FILE >
::binary_stream & operator >>(::binary_stream & stream, ::user::rich_text::data & data)
{

   synchronous_lock synchronouslock(data.synchronization());

   //data.m_plinea->erase_all();

   data.::pointer_array< ::user::rich_text::format >::erase_all();

   data.m_spana.erase_all();

   stream >> (::pointer_array< ::user::rich_text::format > &) data;

   stream >> data.m_spana;

   return stream;

}

//
//// template < typename FILE >
//::binary_stream & operator <<(::binary_stream & stream, ::user::rich_text::edit_impl & editimpl)
//{
//
//   stream << (const ::user::picture &) editimpl;
//
//   stream << *editimpl.m_pdata;
//
//   ::rectangle_i32 rectangleWindow;
//
//   rectangleWindow = editimpl.window_rectangle();
//
//   if (((::user::rich_text::edit_impl & )editimpl).get_parent() != nullptr)
//   {
//
//      ((::user::rich_text::edit_impl&)editimpl).get_parent()->screen_to_client()(rectangleWindow);
//
//   }
//
//   stream << rectangleWindow;
//
//   return stream;
//
//}
//
//
//// template < typename FILE >
//::binary_stream & operator >>(::binary_stream & stream, ::user::rich_text::edit_impl & editimpl)
//{
//
//   stream >> (::user::picture &)editimpl;
//
//   stream >> *editimpl.m_pdata;
//
//   ::rectangle_i32 rectangleWindow;
//
//   stream >> rectangleWindow;
//
//   editimpl.place(rectangleWindow);
//
//   editimpl.display(e_display_normal);
//
//   editimpl.set_need_layout();
//
//   return stream;
//
//}



