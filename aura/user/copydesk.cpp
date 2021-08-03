#include "framework.h"
#include "aura/user/_user.h"


namespace user
{


   copydesk::copydesk()
   {


   }


   copydesk::~copydesk()
   {

   }


   ::e_status copydesk::initialize(::object * pobject)
   {

      auto estatus = ::object::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

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


   bool copydesk::string_to_filea(::file::patha  * ppatha, const ::string & str)
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

         if (_get_plain_text(str))
         {

            if(string_to_filea(nullptr, str))
            {

               return true;

            }

         }

      }

      return false;

   }


   bool copydesk::get_filea(::file::patha & patha, e_op & eop)
   {

      if (_get_filea(patha, eop))
      {

         return true;

      }

      string str;

      if (_get_plain_text(str))
      {

         if (string_to_filea(&patha, str))
         {

            return true;

         }

      }

      return false;

   }


   bool copydesk::set_filea(const ::file::patha & patha, e_op eop)
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

      if (!(eflag & flag_prevent_data_blob) && _has_image())
      {

         ::image_pointer pimage;

         if (desk_to_image(pimage))
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

               return true;

            }

         }

         if (_has_plain_text())
         {

            string strPlainText;

            if (get_plain_text(strPlainText, flag_prevent_data_blob))
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

                  ::payload varFile;

                  varFile["url"] = path;
                  varFile["raw_http"] = true;
                  varFile["disable_common_name_cert_check"] = true;

                  auto pcontext = m_pcontext->m_pauracontext;

                  auto pcontextimage = pcontext->context_image();

                  auto pimage = pcontextimage->load_image(varFile, false);

                  if (pimage)
                  {

                     ::memory mem;

                     auto pcontext = get_context();

                     pcontext->m_papexcontext->file().as_memory(varFile, mem);

                     auto psystem = m_psystem;

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

         e_op eop = op_copy;

         ::file::patha patha;

         if (get_filea(patha, eop))
         {

            str = patha.implode("\r\n");

            return true;

         }

      }

      if (_get_plain_text(str))
      {

         return true;

      }

      return false;

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

         __construct(pimage);

         bool bOk = _desk_to_image(pimage);

         if (bOk)
         {

            pimage->set_ok();

         }

         return bOk;

      }

      if (has_plain_text())
      {

         string str;

         if (get_plain_text(str))
         {

            auto pmemory = create_memory();

            {

               ::payload varFile;

               varFile["url"] = str;
               varFile["http_set"]["raw_http"] = true;
               varFile["http_set"]["disable_common_name_cert_check"] = true;

               auto pcontext = get_context();

               pcontext->m_papexcontext->file().as_memory(varFile, *pmemory);

            }

            auto pcontext = m_pcontext->m_pauracontext;

            auto pcontextimage = pcontext->context_image();

            if (!pcontextimage->load_image(pimage, pmemory))
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

                              return true;

                           }

                        }

                     }

                  }

               }

            }

         }

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

      ::exception::throw_interface_only();

      return 0;

   }


   bool copydesk::_get_filea(::file::patha & stra, e_op & eop)
   {

      UNREFERENCED_PARAMETER(stra);

      ::exception::throw_interface_only();

      return false;

   }


   bool copydesk::_set_filea(const ::file::patha & patha, e_op eop)
   {

      UNREFERENCED_PARAMETER(patha);

      ::exception::throw_interface_only();

      return false;

   }


   bool copydesk::_set_plain_text(const ::string & str)
   {

      UNREFERENCED_PARAMETER(str);

      ::exception::throw_interface_only();

      return false;

   }


   bool copydesk::_get_plain_text(string & str)
   {

      ::exception::throw_interface_only();

      return false;

   }


   bool copydesk::_has_plain_text()
   {

      ::exception::throw_interface_only();

      return 0;

   }



   bool copydesk::_desk_to_image(::image * pimage)
   {

      UNREFERENCED_PARAMETER(pimage);
      ::exception::throw_interface_only();

      return false;

   }


   bool copydesk::_image_to_desk(const ::image * pimage)
   {

      UNREFERENCED_PARAMETER(pimage);
      ::exception::throw_interface_only();

      return false;

   }


   bool copydesk::_has_image()
   {

      ::exception::throw_interface_only();

      return 0;

   }



} // namespace user


