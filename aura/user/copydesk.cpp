#include "framework.h"
#include "aura/user/_user.h"


namespace user
{


   copydesk::copydesk()
   {

      m_pwindow = nullptr;

   }


   copydesk::~copydesk()
   {

   }


   ::e_status copydesk::initialize_copydesk(::windowing::window * pwindow)
   {

      auto estatus = ::object::initialize(pwindow);

      if (!estatus)
      {

         return estatus;

      }

      m_pwindow = pwindow;

      auto psystem = get_system()->m_paurasystem;

      auto pnode = psystem->node();
      
      auto pdraw2d = psystem->draw2d();
      
      auto pwritetext = pdraw2d->write_text();

      m_pfont = pwritetext->point_font(pnode->font_name(e_font_sans), 14.0);

      return true;

   }


   ::e_status copydesk::destroy()
   {

      auto estatus = ::object::destroy();

      return estatus;

   }


   ::e_status copydesk::string_to_filea(::file::patha  * ppatha, const ::string & str)
   {

      string_array stra;

      stra.add_lines(str);

      auto pcontext = get_context();

      for (auto & strPath : stra)
      {

         if (strPath.has_char() && (pcontext->m_papexcontext->dir().is(strPath) || pcontext->m_papexcontext->file().exists(strPath)))
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

         return ::success;

      }

      return error_failed;

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

         auto estatus = _get_plain_text(str);

         if(::succeeded(estatus))
         {

            estatus = string_to_filea(nullptr, str);

            if(::succeeded(estatus))
            {

               return true;

            }

         }

      }

      return false;

   }


   ::e_status copydesk::get_filea(::file::patha & patha, e_op & eop)
   {

      auto estatus = _get_filea(patha, eop);

      if(::succeeded(estatus))
      {

         return estatus;

      }

      string str;

      estatus = _get_plain_text(str);

      if(::succeeded(estatus))
      {

         estatus = string_to_filea(&patha, str);

         if(::succeeded(estatus))
         {

            return estatus;

         }

      }

      return estatus;

   }


   ::e_status copydesk::set_filea(const ::file::patha & patha, e_op eop)
   {

      return _set_filea(patha, eop);

   }


   ::e_status copydesk::set_plain_text(const ::string & str, bool bForceSetIfEmpty)
   {

      if(str.is_empty() && !bForceSetIfEmpty)
      {

         return error_failed;

      }

      return _set_plain_text(str);

   }


   ::e_status copydesk::get_plain_text(string & str, enum_flag eflag)
   {

      if (!(eflag & flag_prevent_data_blob) && _has_image())
      {

         ::image_pointer pimage;

         auto estatus = desk_to_image(pimage);

         if(::succeeded(estatus))
         {

            memory mem;

            auto psaveimage = __new(save_image);

            if (pimage->frames() && pimage->frames()->count() >= 2)
            {

               psaveimage->m_eformat = ::draw2d::format_gif;

            }
            else
            {

               psaveimage->m_eformat = ::draw2d::format_png;

            }

            __pointer(::aura::application) papplication = get_application();

            auto psystem = m_psystem->m_paurasystem;

            auto pcontext = m_pcontext->m_pauracontext;

            auto pcontextimage = pcontext->context_image();

            if (pcontextimage->save_image(mem, pimage, psaveimage))
            {

               auto psystem = m_psystem;

               auto pbase64 = psystem->base64();

               str = pbase64->encode(mem);

               if (psaveimage->m_eformat == ::draw2d::format_png)
               {

                  str = "data:image/png;base64;" + str;

               }
               else if (psaveimage->m_eformat == ::draw2d::format_gif)
               {

                  str = "data:image/gif;base64;" + str;

               }

               return ::success;

            }

         }

         if (_has_plain_text())
         {

            string strPlainText;

            auto estatus = get_plain_text(strPlainText, flag_prevent_data_blob);

            if(::succeeded(estatus))
            {

               string_array straLines;

               straLines.add_lines(strPlainText);

               index iFind = straLines.predicate_find_first([](auto strLine)
                  {

                     return (strLine.begins_ci("http://")
                        || strLine.begins_ci("https://"))
                        && strLine.ends_ci(".gif");
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

                     pcontext->m_papexcontext->file().as_memory(payloadFile, mem);

                     auto psystem = m_psystem;

                     auto pbase64 = psystem->base64();

                     string strBase64 = pbase64->encode(mem);

                     str = "data:image/gif;base64," + strBase64;

                     return ::success;

                  }

               }

            }

         }

      }

      if (_has_filea())
      {

         e_op eop = op_copy;

         ::file::patha patha;

         auto estatus = get_filea(patha, eop);

         if(::succeeded(estatus))
         {

            str = patha.implode("\r\n");

            return estatus;

         }

      }

      auto estatus = _get_plain_text(str);

      if(::succeeded(estatus))
      {

         return estatus;

      }

      return estatus;

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


   ::e_status copydesk::desk_to_image(::image_pointer & pimage)
   {

      if (_has_image())
      {

         m_pwindow->__construct(pimage);

         auto estatus = _desk_to_image(pimage);

         if (::succeeded(estatus))
         {

            pimage->set_ok();

         }

         return estatus;

      }

      if (has_plain_text())
      {

         string str;

         auto estatus = get_plain_text(str);

         if(::succeeded(estatus))
         {

            auto pmemory = create_memory();

            {

               ::payload payloadFile;

               payloadFile["url"] = str;
               payloadFile["http_set"]["raw_http"] = true;
               payloadFile["http_set"]["disable_common_name_cert_check"] = true;

               auto pcontext = get_context();

               pcontext->m_papexcontext->file().as_memory(payloadFile, *pmemory);

            }

            auto pcontext = m_pcontext->m_pauracontext;

            auto pcontextimage = pcontext->context_image();

            if (!pcontextimage->_load_image(pimage, pmemory))
            {

               // Couldn't load image from file/URL path...
               // ... gonna create image with the text.

               // need a graphics context to measure the text extent
               // create image (1x1) with a graphics context for measuring the text extent
               // (the image raw allocation can be reused when the image
               //
               auto estatus = __construct(pimage);

               if(estatus.succeeded())
               {

                  estatus = pimage->create({ 1, 1 });

                  if (is_status_ok())
                  {

                     auto pfont = m_pfont;

                     pimage->g()->set(pfont);

                     size_f64 s = pimage->g()->get_text_extent(str);

                     if (s.area() > 0.)
                     {

                        estatus = __construct(pimage);

                        if(estatus.succeeded())
                        {

                           estatus = pimage->create({ (int)ceil(s.cx), (int)ceil(s.cy) });

                           if (is_status_ok())
                           {

                              pimage->fill_byte(0);

                              pimage->g()->set(pfont);

                              pimage->g()->set_text_color(argb(255, 0, 0, 0));

                              pimage->g()->draw_text(str, ::rectangle_i32(pimage->get_size()), e_align_bottom_left);

                              return estatus;

                           }

                        }

                     }

                  }

               }

            }

         }

      }

      return error_failed;

   }


   ::e_status copydesk::image_to_desk(const ::image * pimage)
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

      throw ::interface_only_exception();

      return 0;

   }


   ::e_status copydesk::_get_filea(::file::patha & stra, e_op & eop)
   {

      __UNREFERENCED_PARAMETER(stra);

      throw ::interface_only_exception();

      return false;

   }


   ::e_status copydesk::_set_filea(const ::file::patha & patha, e_op eop)
   {

      __UNREFERENCED_PARAMETER(patha);

      throw ::interface_only_exception();

      return false;

   }


   ::e_status copydesk::_set_plain_text(const ::string & str)
   {

      __UNREFERENCED_PARAMETER(str);

      throw ::interface_only_exception();

      return false;

   }


   ::e_status copydesk::_get_plain_text(string & str)
   {

      throw ::interface_only_exception();

      return false;

   }


   bool copydesk::_has_plain_text()
   {

      throw ::interface_only_exception();

      return 0;

   }


   ::e_status copydesk::_desk_to_image(::image * pimage)
   {

      __UNREFERENCED_PARAMETER(pimage);

      throw ::interface_only_exception();

      return false;

   }


   ::e_status copydesk::_image_to_desk(const ::image * pimage)
   {

      __UNREFERENCED_PARAMETER(pimage);

      throw ::interface_only_exception();

      return false;

   }


   bool copydesk::_has_image()
   {

      throw ::interface_only_exception();

      return 0;

   }


} // namespace user



