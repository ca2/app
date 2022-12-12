#include "framework.h"
#include "copydesk.h"
#include "acme/exception/interface_only.h"
#include "acme/primitive/string/base64.h"
#include "apex/filesystem/filesystem/dir_context.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/image/save_image.h"
#include "aura/graphics/image/frame_array.h"
#include "aura/graphics/image/context_image.h"
#include "aura/windowing/window.h"
#include "aura/platform/node.h"
#include "aura/platform/application.h"


namespace user
{


   copydesk::copydesk()
   {

      m_pwindow = nullptr;

   }


   copydesk::~copydesk()
   {

   }


   void copydesk::initialize_copydesk(::windowing::window * pwindow)
   {

      //auto estatus = 
      
      ::object::initialize(pwindow);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pwindow = pwindow;

      auto psystem = acmesystem()->m_paurasystem;

      auto pnode = psystem->node();
      
      auto pdraw2d = psystem->draw2d();
      
      auto pwritetext = pdraw2d->write_text();

      m_pfont = pwritetext->point_font(pnode->font_name(e_font_sans), 14.0);

      //return true;

   }


   void copydesk::destroy()
   {

      //auto estatus = 
      
      ::object::destroy();

      //return estatus;

   }


   bool copydesk::string_to_filea(::file::path_array * ppatha, const ::string & str)
   {

      string_array stra;

      stra.add_lines(str);

      auto pcontext = get_context();

      for (auto & strPath : stra)
      {

         if (strPath.has_char() && (dir()->is(strPath) || pcontext->m_papexcontext->file()->exists(strPath)))
         {

            if (ppatha == nullptr)
            {

               return true;

            }

            ppatha->add(::file::path(strPath));

         }

      }

      if (ppatha != nullptr && ppatha->has_elements())
      {

         return true;

      }

      return false;

   }


   bool copydesk::has_filea()
   {

      if (_has_filea())
      {

         return true;

      }

      if (_has_plain_text())
      {

         string str;

         if(_get_plain_text(str))
         {

            if(string_to_filea(nullptr, str))
            {

               return true;

            }

         }

         return true;

      }

      return false;

   }


   bool copydesk::get_filea(::file::path_array & patha, enum_op & eop)
   {

      if(_get_filea(patha, eop))
      {

         return true;

      }

      string str;

      if (!_get_plain_text(str))
      {

         return false;

      }

      if(!string_to_filea(&patha, str))
      {

         return false;

      }

      return true;

   }


   bool copydesk::set_filea(const ::file::path_array & patha, enum_op eop)
   {

      return _set_filea(patha, eop);

   }


   bool copydesk::set_plain_text(const ::string & str, bool bForceSetIfEmpty)
   {

      if(str.is_empty() && !bForceSetIfEmpty)
      {

         return false;

      }

      return _set_plain_text(str);

   }


   bool copydesk::get_plain_text(string & str, enum_flag eflag)
   {

      if (!(eflag & e_flag_prevent_data_blob) && _has_image())
      {

         ::image_pointer pimage;

         if(desk_to_image(pimage))
         {

            memory mem;

            auto psaveimage = __new(save_image);

            if (pimage->frames() && pimage->frames()->count() >= 2)
            {

               psaveimage->m_eformat = ::draw2d::e_format_gif;

            }
            else
            {

               psaveimage->m_eformat = ::draw2d::e_format_png;

            }

            ::pointer<::aura::application>papp = get_app();

            auto psystem = acmesystem()->m_paurasystem;

            auto pcontext = m_pcontext->m_pauracontext;

            auto pcontextimage = pcontext->context_image();

            pcontextimage->save_image(mem, pimage, psaveimage);

            auto pbase64 = psystem->base64();

            str = pbase64->encode(mem);

            if (psaveimage->m_eformat == ::draw2d::e_format_png)
            {

               str = "data:image/png;base64;" + str;

            }
            else if (psaveimage->m_eformat == ::draw2d::e_format_gif)
            {

               str = "data:image/gif;base64;" + str;

            }

            return true;

         }

         if (_has_plain_text())
         {

            string strPlainText;

            if(get_plain_text(strPlainText, e_flag_prevent_data_blob))
            {

               string_array straLines;

               straLines.add_lines(strPlainText);

               index iFind = straLines.predicate_find_first([](auto strLine)
                  {

                     return (strLine.case_insensitive_begins("http://")
                        || strLine.case_insensitive_begins("https://"))
                        && strLine.case_insensitive_ends(".gif");
                  });

               if (iFind >= 0)
               {

                  ::file::path path = straLines[iFind];

                  ::payload payloadFile;

                  payloadFile["url"] = path;
                  payloadFile["raw_http"] = true;
                  payloadFile["disable_common_name_cert_check"] = true;

                  auto pcontext = m_pcontext->m_pauracontext;

                  auto pcontextimage = pcontext->context_image();

                  auto pimage = pcontextimage->load_image(payloadFile, { .cache = false });

                  if (pimage)
                  {

                     ::memory mem;

                     auto pcontext = get_context();

                     pcontext->m_papexcontext->file()->as_memory(payloadFile, mem);

                     auto psystem = acmesystem();

                     auto pbase64 = psystem->base64();

                     string strBase64 = pbase64->encode(mem);

                     str = "data:image/gif;base64," + strBase64;

                     return true;

                  }

               }

            }

         }

      }

      if (_has_filea())
      {

         enum_op eop = e_op_copy;

         ::file::path_array patha;

         if(get_filea(patha, eop))
         {

            str = patha.implode("\r\n");

            return true;

         }

      }

      if(!_get_plain_text(str))
      {

         return false;

      }

      return true;

   }


   bool copydesk::has_plain_text()
   {

      if (_has_plain_text())
      {

         return true;

      }

      if (_has_filea())
      {

         return true;

      }

      return false;

   }


   bool copydesk::desk_to_image(::image_pointer & pimage)
   {

      if (_has_image())
      {

         m_pwindow->__construct(pimage);

         if (_desk_to_image(pimage))
         {

            pimage->set_ok_flag();

            return true;

         }

      }

      if (has_plain_text())
      {

         string str;

         if(get_plain_text(str))
         {

            auto pmemory = create_memory();

            {

               ::payload payloadFile;

               payloadFile["url"] = str;
               payloadFile["http_set"]["raw_http"] = true;
               payloadFile["http_set"]["disable_common_name_cert_check"] = true;

               auto pcontext = get_context();

               pcontext->m_papexcontext->file()->as_memory(payloadFile, *pmemory);

            }

            auto pcontext = m_pcontext->m_pauracontext;

            auto pcontextimage = pcontext->context_image();

            pcontextimage->_load_image(pimage, pmemory);
            //{

               // Couldn't load image from file/URL path...
               // ... gonna create image with the text.

               // need a graphics context to measure the text extent
               // create image (1x1) with a graphics context for measuring the text extent
               // (the image raw allocation can be reused when the image
               //
               //auto estatus = 
            
            __construct(pimage);

               //if(estatus.succeeded())
               //{

                  //estatus = 
            
            pimage->create({ 1, 1 });

                  //if (is_status_ok())
                  //{

                     auto pfont = m_pfont;

                     pimage->g()->set(pfont);

                     size_f64 s = pimage->g()->get_text_extent(str);

                     if (s.area() > 0.)
                     {

                         __construct(pimage);

                        //if(estatus.succeeded())
                        {

                           pimage->create({ (int)ceil(s.cx), (int)ceil(s.cy) });

                           //if (is_status_ok())
                           //{

                              pimage->fill_byte(0);

                              pimage->g()->set(pfont);

                              pimage->g()->set_text_color(argb(255, 0, 0, 0));

                              pimage->g()->draw_text(str, ::rectangle_i32(pimage->get_size()), e_align_bottom_left);

                              return true;

                           //}

                        }

                     //}

                  }

               //}

            }

         //}

      }

      return false;

   }


   bool copydesk::image_to_desk(const ::image * pimage)
   {

      return _image_to_desk(pimage);

   }


   bool copydesk::has_image()
   {

      if (_has_image())
      {

         return true;

      }

      if (has_plain_text())
      {

         return true;

      }

      return false;

   }


   bool copydesk::_has_filea()
   {

      throw ::interface_only();

      return 0;

   }


   bool copydesk::_get_filea(::file::path_array & stra, enum_op & eop)
   {

      __UNREFERENCED_PARAMETER(stra);

      throw ::interface_only();

      return false;

   }


   bool copydesk::_set_filea(const ::file::path_array & patha, enum_op eop)
   {

      __UNREFERENCED_PARAMETER(patha);

      throw ::interface_only();

      return false;

   }


   bool copydesk::_set_plain_text(const ::string & str)
   {

      __UNREFERENCED_PARAMETER(str);

      throw ::interface_only();

      return false;

   }


   bool copydesk::_get_plain_text(string & str)
   {

      throw ::interface_only();

      return false;

   }


   bool copydesk::_has_plain_text()
   {

      throw ::interface_only();

      return 0;

   }


   bool copydesk::_desk_to_image(::image * pimage)
   {

      __UNREFERENCED_PARAMETER(pimage);

      throw ::interface_only();

      return false;

   }


   bool copydesk::_image_to_desk(const ::image * pimage)
   {

      __UNREFERENCED_PARAMETER(pimage);

      throw ::interface_only();

      return false;

   }


   bool copydesk::_has_image()
   {

      throw ::interface_only();

      return 0;

   }


} // namespace user



