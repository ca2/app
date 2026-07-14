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
   
   
   void context::set_blend_mode(enum_blend_mode eblendmode)
   {

      throw ::interface_only();

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


      void context::create(const ::i32_size & size)
      {


      }


      void context::attach(void * posdata, const ::i32_size & size, ::i32 iType)
      {


      }


      void * context::detach(::i32 iType)
      {

         return nullptr;

      }


      void context::on_begin_draw()
      {


      }


      void context::on_end_draw()
      {


      }


      void context::draw_text123(const ::scoped_string & scopedstr, const ::f64_rectangle & rectangleText
         , const ::e_draw_text & edrawtext, const ::e_align & ealign)
      {

         if (ealign & e_align_bottom_right_bias)
         {

            _draw_text(scopedstr, rectangleText, edrawtext, ealign);

         }
         else
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

                  _draw_text(strLine, r, edrawtext, ealign);

                  auto size = get_text_extents(strLine);

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


      void context::_draw_text(const ::scoped_string & scopedstr, const ::f64_rectangle & rectangleText
         , const ::e_draw_text & edrawtext, const ::e_align & ealign)
      {


      }


      ::f64_size context::get_text_extents(const ::scoped_string & scopedstr)
      {

         throw ::interface_only();

         return {};

      }
   
   ::pointer < ::nano::graphics::image > context::create_bitmap_context(void * pdata,
                                                              const ::i32_size & size, int iBytesPerRow)
   {
      
      throw ::interface_only();
      
      return {};
      
   }
   
   
   void context::update_bitmap_context_image(::pointer < ::nano::graphics::image > & pimage)
   {
      
      throw ::interface_only();
      
   }
   
   
      void context::set_pen(::nano::graphics::pen * ppen)
      {
      
         throw ::interface_only();
         
      }
   
   
      void context::set_brush(::nano::graphics::brush * pbrush)
      {
         
         throw ::interface_only();
         
      }
   
   
      void context::set_font(::nano::graphics::font * pfont)
      {
      
         throw ::interface_only();
         
      }


      void context::rectangle(const ::f64_rectangle & rectangle)
      {

         throw ::interface_only();

      }


            void context::ellipse(const ::f64_rectangle &rectangle)
      {

               throw ::interface_only();
      }

            void context::line(const ::f64_point& point1, const ::f64_point& point2)
            {

               throw ::interface_only();

                     }


      void context::draw_icon(::f64 x, ::f64 y, ::f64 cx, ::f64 cy, ::nano::graphics::icon * picon)
      {
         throw ::interface_only();

      }
   
   
   void context::draw_image(const ::f64_rectangle &rectangle, ::nano::graphics::image * pimage)
   {
      
      throw ::interface_only();
      
   }

   void context::draw_image(const ::f64_point & point, const ::f64_rectangle &rectangle, ::nano::graphics::image * pimage)
   {
      
      throw ::interface_only();
      
   }


      ::pixmap context::pixmap()
      {

         return {};

      }
   
   
      void context::translate(::f64 x, ::f64 y)
      {
         
         
      }


      void context::do_path(::nano::graphics::path *ppath)
      {

         throw ::interface_only();

      }


      //void context::draw_path(::nano::graphics::path* ppath, ::nano::graphics::pen* ppen)
      //{

      //   throw ::interface_only();

      //}





   } // namespace graphics


} // namespace nano


