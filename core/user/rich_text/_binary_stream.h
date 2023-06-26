// Created by camilo on 2022-10-15 04:49 <3ThomasBorregaardSorensen!!
#pragma once


#include "core/user/rich_text/format.h"
#include "core/user/rich_text/span.h"
#include "core/user/rich_text/data.h"
#include "core/user/rich_text/edit_impl.h"


template < typename FILE >
::binary_stream < FILE > & operator <<(::binary_stream < FILE > & stream, const ::user::rich_text::format & format)
{

   stream << format.m_bItalic;
   stream << format.m_bUnderline;
   stream << format.m_strFontFamily;
   stream << format.m_dFontSize;
   stream << (u32)format.m_colorForeground;
   stream << (u32)format.m_colorBackground;
   stream << (i32)format.m_escript;
   stream << (i32)format.m_elineheight;

   return stream;

}


template < typename FILE >
::binary_stream < FILE > & operator <<(::binary_stream < FILE > & stream, ::user::rich_text::format &format)
{
             
   stream >> format.m_bItalic;
   stream >> format.m_bUnderline;
   stream >> format.m_strFontFamily;
   stream >> format.m_dFontSize;
   stream >> (u32 &)format.m_colorForeground;
   stream >> (u32 &)format.m_colorBackground;
   stream >> (i32 &)format.m_escript;
   stream >> (i32 &)format.m_elineheight;

   return stream;

}


template < typename FILE >
::binary_stream < FILE > & operator <<(::binary_stream < FILE > & stream, const ::user::rich_text::span & span)
{

   property_set set;

   set["align"] = (i32)span.m_ealignNewLine;
   set["text"] = span.m_str;
   index iFormatIndex = span.m_pdata->m_pformata->find_first(span.m_pformat);
   set["format_index"] = iFormatIndex;

   stream << set;

   return stream;

}


template < typename FILE >
::binary_stream < FILE > & operator >>(::binary_stream < FILE > & stream, ::user::rich_text::span & span)
{

   property_set set;

   stream >> set;

   span.m_ealignNewLine = set["align"].e< ::enum_align>();
   span.m_str = set["text"];
   ::index iFormatIndex;

   iFormatIndex = set["format_index"];
   if (iFormatIndex >= 0 && iFormatIndex < span.m_pdata->m_pformata->get_count())
   {
      span.m_pformat = span.m_pdata->m_pformata->element_at(iFormatIndex);
   }
   else
   {
      infomration("corruption... non fatal... partially recoverable...");
   }

   return stream;

}


template < typename FILE >
::binary_stream < FILE > & operator <<(::binary_stream < FILE > & stream, const ::user::rich_text::data & data)
{

   synchronous_lock synchronouslock(data.synchronization());

   stream << data.m_pformata;

   stream << data.m_spana;

   return stream;

}


template < typename FILE >
::binary_stream < FILE > & operator >>(::binary_stream < FILE > & stream, ::user::rich_text::data & data)
{

   synchronous_lock synchronouslock(data.synchronization());

   data.m_plinea->erase_all();

   data.m_pformata->erase_all();

   data.m_spana.erase_all();

   stream >> data.m_pformata;

   stream >> data.m_spana;

   return stream;

}



template < typename FILE >
::binary_stream < FILE > & operator <<(::binary_stream < FILE > & stream, ::user::rich_text::edit_impl & editimpl)
{

   stream << (const ::user::picture &) editimpl;

   stream << editimpl.m_pdata;

   ::rectangle_i32 rectangleWindow;

   rectangleWindow = editimpl.window_rectangle();

   if (((::user::rich_text::edit_impl & )editimpl).get_parent() != nullptr)
   {

      ((::user::rich_text::edit_impl&)editimpl).get_parent()->screen_to_client()(rectangleWindow);

   }

   stream << rectangleWindow;

   return stream;

}


template < typename FILE >
::binary_stream < FILE > & operator >>(::binary_stream < FILE > & stream, ::user::rich_text::edit_impl & editimpl)
{

   stream >> (const ::user::picture &)editimpl;

   stream >> editimpl.m_pdata;

   ::rectangle_i32 rectangleWindow;

   stream >> rectangleWindow;

   editimpl.place(rectangleWindow);

   editimpl.display(e_display_normal);

   editimpl.set_need_layout();

   return stream;

}



