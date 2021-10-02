#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif

#include "aura/update.h"
//#include "image_list.h"


namespace userex
{


   image_list_view::image_list_view() 
   {


   }


   image_list_view::~image_list_view()
   {
   }


   string_array image_list_view::get_ls_pattern_stra() const
   {

      string_array stra;

      for (auto & strPattern : m_straPattern)
      {

         string_array straPattern;

         straPattern.explode(";", strPattern);

         straPattern.trim();

         stra.add_unique(straPattern);

      }

      return stra;

   }


   string image_list_view::get_link_prefix()
   {

      if (m_strLinkPrefix.has_char())
      {

         return m_strLinkPrefix;

      }

      return string(m_pathFolder.name()) + "/";

   }


   ::file::path image_list_view::get_link_path(string strLink)
   {

      if (::str::begins_eat_ci(strLink, get_link_prefix()))
      {

         return m_pathFolder / strLink;

      }

      return "";

   }


   bool image_list_view::update_data(bool bSaveAndValidate)
   {

      synchronous_lock synchronouslock(mutex());

      if (bSaveAndValidate)
      {

         return true;

      }
      else
      {

         synchronous_lock synchronouslock(mutex());

         m_imageaThumb.erase_all();

         m_imagea.erase_all();

         auto pcontext = m_pcontext;

         auto papplication = get_application();

         if (m_pathFolder.has_char())
         {

            m_plisting->erase_all();

            pcontext->m_papexcontext->dir().ls_file_pattern(*m_plisting, m_pathFolder, get_ls_pattern_stra());

         }

         load_images();

         return ::user::image_list::update_data(false);

      }

   }


   void image_list_view::load_images()
   {

      m_iForkAddDib++;

      fork([this]()
      {

         synchronous_lock synchronouslock(mutex());

         int iForkDib = m_iForkAddDib;

         for (index i = 0; iForkDib == m_iForkAddDib && i < m_plisting->get_count();)
         {

            synchronouslock.unlock();

            ::image_pointer pimage1;

            ::file::path path = m_plisting->element_at(i);

            auto pcontext = m_pcontext->m_pauracontext;

            auto pcontextimage = pcontext->context_image();

            pimage1 = pcontextimage->load_image(path, { .cache = false });

            if (pimage1)
            {

               if (pimage1->width() > 256)
               {

                  ::image_pointer pimageSmall;

                  pimageSmall = m_pcontext->context_image()->create_image({256,  256 * pimage1->height() / pimage1->width()});

                  image_source imagesource(pimage1);

                  image_drawing_options imagedrawingoptions(pimageSmall->rectangle());

                  image_drawing imagedrawing(imagedrawingoptions, imagesource);

                  pimageSmall->g()->draw(imagedrawing);

                  pimage1 = pimageSmall;

               }

               if (pimage1->is_set())
               {

                  pimage1->extension()->payload("read_only_link") = get_link_prefix() + path.name();

                  synchronouslock.lock();

                  i++;

                  m_imagea.add(pimage1);

                  set_need_layout();

               }
               else
               {

                  synchronouslock.lock();

                  TRACE("(2) Could not pimage->load_from_file.file=" + m_plisting->element_at(i));

                  m_plisting->erase_at(i);

               }

            }
            else
            {

               synchronouslock.lock();

               TRACE("Could not pimage->load_from_file.file=" + m_plisting->element_at(i));

               m_plisting->erase_at(i);

            }

         }

      });

   }


   void image_list_view::assert_valid() const
   {
      ::user::image_list_view::assert_valid();
   }

   void image_list_view::dump(dump_context & dumpcontext) const
   {
      ::user::image_list_view::dump(dumpcontext);
   }

   void image_list_view::install_message_routing(::channel * pchannel)
   {

      ::user::image_list_view::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &image_list_view::on_message_create);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &image_list_view::on_message_destroy);
//      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &image_list_view::on_message_left_button_down);
      //    MESSAGE_LINK(e_message_mouse_move, pchannel, this, &image_list_view::on_message_mouse_move);
      //  MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &image_list_view::on_message_mouse_leave);

   }


   //void image_list_view::on_message_left_button_down(::message::message * pmessage)
   //{

   //   auto pmouse = pmessage->m_pmouse;

   //   const ::point_i32 & point = pmouse->m_point;

   //   screen_to_client(point);

   //   int iMenuSel;

   //   int iCommandSel;

   //   int iHover = hit_test(point, iMenuSel, iCommandSel);

   //   if (iCommandSel >= 0)
   //   {

   //      m_iMenuSel = iMenuSel;

   //      m_iCommandSel = iCommandSel;

   //   }

   //}


   //void image_list_view::on_message_mouse_move(::message::message * pmessage)
   //{

   //   auto pmouse = pmessage->m_pmouse;

   //   const ::point_i32 & point = pmouse->m_point;

   //   screen_to_client(point);

   //   int iMenuHover;

   //   int iCommandHover;

   //   int iHover = hit_test(point, iMenuHover, iCommandHover);

   //   if (iHover >= 0 && m_iHover < 0)
   //   {

   //      SetCapture();

   //   }

   //   m_iMenuHover = iMenuHover;

   //   m_iCommandHover = iCommandHover;

   //   m_iHover = iHover;

   //}


   //void image_list_view::on_message_mouse_leave(::message::message * pmessage)
   //{

   //auto psession = get_session();

   //auto puser = psession->user();

   //auto pwindowing = puser->windowing();

   //pwindowing->release_capture();

   //   m_iMenuHover = -1;

   //   m_iCommandHover = -1;

   //}


   void image_list_view::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      ::id id = get_document()->m_pimpactsystem->m_id;

      string strText;

      auto papplication = get_application();

      papplication->data_get(m_id + ".cur_text", strText);

   }


   void image_list_view::on_message_destroy(::message::message * pmessage)
   {

   }


   void image_list_view::handle(::subject * psubject, ::context * pcontext)
   {

      ::user::image_list_view::handle(psubject, pcontext);

      if (psubject->id() == id_after_change_text)
      {

         auto * peditview = _001TypedWindow < ::userex::top_edit_view >();

         if (peditview != nullptr && psubject->m_puserelement == peditview)
         {

            string strText;

            peditview->_001GetText(strText);

         }

      }

   }


   void image_list_view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {


      ::user::image_list_view::on_layout(pgraphics);

   }


   bool image_list_view::_001GetItemText(string & str, index iItem)
   {

      str = m_plisting->element_at(iItem).name();

      string strMap;

      string strLower = str;

      strLower.make_lower();

      if (m_mapName.lookup(strLower, strMap))
      {

         str = strMap;

      }

      return true;

   }



} // namespace userex


