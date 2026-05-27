//
// Created by camilo on 31/01/2022 21:27 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "context.h"
#include "acme/exception/interface_only.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "acme/graphics/image/pixmap.h"



namespace nano
{


   namespace graphics
   {


      context::context()
      {


      }


      context::~context()
      {


      }


      void context::set_smoothing_mode(enum_smoothing_mode esmoothingmode)
      {

         throw ::interface_only();

      }


      void context::set_text_rendering_hint(enum_text_rendering_hint etextrenderinghint)
      {

         throw ::interface_only();

      }


   void context::clear(const ::color::color & color) {


         throw ::interface_only();

      }


#ifdef HAS_X11

      void context::create_for_x11(const ::x11::handle_t & handle, ::i32 w, ::i32 h)
      {

         throw ::interface_only();

      }

#endif


      void context::resize(const ::i32_size & size)
      {


      }


      void context::create(::i32 cx, ::i32 cy)
      {

      }

      void context::attach(void * posdata, const ::i32_size & size, ::i32 iType)
      {


      }


      void context::on_begin_draw()
      {


      }


      void context::on_end_draw()
      {


      }


      void context::draw_text123(const ::scoped_string & scopedstr, const ::f64_rectangle & rectangleText, const ::e_align & ealign,
                                const ::e_draw_text & edrawtext, ::nano::graphics::brush * pnanobrushBack,
                                ::nano::graphics::brush * pnanobrushText, ::nano::graphics::font * pnanofont)
      {

         if (ealign & e_align_bottom_right_bias)
         {

            _draw_text(scopedstr, rectangleText, ealign, edrawtext, pnanobrushBack, pnanobrushText, pnanofont);

         } else
         {

            string_array_base straLines;

            straLines.add_lines(scopedstr);

            auto r = rectangleText;

            ::i32 iLastCy = 0;

            for (auto & strLine: straLines)
            {

               if (strLine.is_empty())
               {

                  r.top += iLastCy;

               }
               else
               {

                  _draw_text(strLine, r, ealign, edrawtext, pnanobrushBack, pnanobrushText, pnanofont);

                  auto size = get_text_extents(strLine, pnanofont);

                  r.top += size.cy;

                  iLastCy = size.cy;

               }

               if (r.top > rectangleText.bottom)
               {

                  break;

               }

            }

         }


      }


      void context::_draw_text(const ::scoped_string & scopedstr, const ::f64_rectangle & rectangleText, const ::e_align & ealign,
                              const ::e_draw_text & edrawtext, ::nano::graphics::brush * pnanobrushBack,
                              ::nano::graphics::brush * pnanobrushText, ::nano::graphics::font * pnanofont)
      {


      }


      ::i32_size context::get_text_extents(const ::scoped_string & scopedstr, ::nano::graphics::font * pnanofont)
      {

         return {};

      }


      void context::rectangle(const ::f64_rectangle & rectangle, ::nano::graphics::brush * pnanobrush,
                             ::nano::graphics::pen * pnanopen)
      {


      }

      void context::draw(::nano::graphics::icon * picon, ::i32 x, ::i32 y, ::i32 cx, ::i32 cy)
      {


      }

      ::pixmap context::pixmap()
      {

         return {};

      }
   
   
      void context::translate(::f64 x, ::f64 y)
      {
         
         
      }


      void context::fill_path(::nano::graphics::path* ppath, ::nano::graphics::brush* pbrush)
      {

         throw ::interface_only();

      }


      void context::draw_path(::nano::graphics::path* ppath, ::nano::graphics::pen* ppen)
      {

         throw ::interface_only();

      }





   } // namespace graphics


} // namespace nano


