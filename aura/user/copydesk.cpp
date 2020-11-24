#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


namespace user
{


   copydesk::copydesk()
   {


   }


   copydesk::~copydesk()
   {

   }


   ::estatus copydesk::initialize(::layered * pobjectContext)
   {

      auto estatus = ::object::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      m_pfont = ::draw2d::point_font(FONT_SANS, 14.0);

      return true;

   }


   void copydesk::finalize()
   {

      ::object::finalize();

   }


   bool copydesk::string_to_filea(::file::patha  * ppatha, const string & str)
   {

      string_array stra;

      stra.add_lines(str);

      for (auto & strPath : stra)
      {

         if (strPath.has_char() && (Context.dir().is(strPath) || Context.file().exists(strPath)))
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


   bool copydesk::set_plain_text(const string & str, bool bForceSetIfEmpty)
   {

      if(str.is_empty() && !bForceSetIfEmpty)
      {

         return false;

      }

      return _set_plain_text(str);

   }


   bool copydesk::get_plain_text(string & str, e_flag eflag)
   {

      if (!(eflag & flag_prevent_data_blob) && _has_image())
      {

         ::image_pointer pimage;

         if (desk_to_image(pimage))
         {

            memory mem;


            ::save_image si;

            if (pimage->frames() && pimage->frames()->count() >= 2)
            {

               si.m_eformat = ::draw2d::format_gif;

            }
            else
            {

               si.m_eformat = ::draw2d::format_png;

            }

            if (Application.image().save_image(mem, pimage, &si))
            {

               str = System.base64().encode(mem);

               if (si.m_eformat == ::draw2d::format_png)
               {

                  str = "data:image/png;base64;" + str;

               }
               else if (si.m_eformat == ::draw2d::format_gif)
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

               index iFind = straLines.pred_find_first([](auto strLine)
                  {

                     return (strLine.begins_ci("http://")
                        || strLine.begins_ci("https://"))
                        && strLine.ends_ci(".gif");
                  });

               if (iFind >= 0)
               {

                  ::file::path path = straLines[iFind];

                  payload varFile;

                  varFile["url"] = path;
                  varFile["raw_http"] = true;
                  varFile["disable_common_name_cert_check"] = true;

                  auto pimage = Application.image().load_image(varFile, false);

                  if (pimage)
                  {

                     ::memory mem;

                     Context.file().as_memory(varFile, mem);

                     string strBase64 = System.base64().encode(mem);

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

               payload varFile;

               varFile["url"] = str;
               varFile["http_set"]["raw_http"] = true;
               varFile["http_set"]["disable_common_name_cert_check"] = true;

               Context.file().as_memory(varFile, *pmemory);

            }

            if (!Application.image().load_image(pimage, pmemory))
            {

               // Couldn't load image from file/URL path...
               // ... gonna create image with the text.

               // need a graphics context to measure the text extent
               // create image (1x1) with a graphics context for measuring the text extent
               // (the image raw allocation can be reused when the image
               //
               auto estatus = __construct(pimage);

               if (estatus)
               {

                  estatus = pimage->create({ 1, 1 });

                  if (is_status_ok())
                  {

                     auto pfont = m_pfont;

                     pimage->g()->set(pfont);

                     sized s = pimage->g()->GetTextExtent(str);

                     if (s.area() > 0.)
                     {

                        estatus = __construct(pimage);

                        if (estatus)
                        {

                           estatus = pimage->create({ (int)ceil(s.cx), (int)ceil(s.cy) });

                           if (is_status_ok())
                           {

                              pimage->fill_byte(0);

                              pimage->g()->set(pfont);

                              pimage->g()->set_text_color(ARGB(255, 0, 0, 0));

                              pimage->g()->draw_text(str, rect(pimage->get_size()), e_align_bottom_left);

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


   bool copydesk::_set_plain_text(const string & str)
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


