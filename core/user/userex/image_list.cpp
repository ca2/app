#include "framework.h"
#include "image_list.h"
#include "top_edit_impact.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/platform/message.h"
#include "acme/filesystem/filesystem/listing.h"
#include "apex/database/_binary_stream.h"
#include "apex/filesystem/filesystem/dir_context.h"
#include "aura/graphics/image/context_image.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/array.h"
#include "aura/message/user.h"
#include "base/user/user/document.h"
#include "base/user/user/impact.h"
#include "base/user/user/impact_system.h"
#include "base/platform/application.h"
#include "core/platform/session.h"


namespace userex
{


   image_list_impact::image_list_impact() 
   {


   }


   image_list_impact::~image_list_impact()
   {
   }


   string_array image_list_impact::get_ls_pattern_stra() const
   {

      string_array stra;

      for (auto & filedialogfilter : m_filedialogfiltera)
      {

         string_array straPattern;

         straPattern.explode(";", filedialogfilter.m_strPatternList);

         straPattern.trim();

         stra.append_unique(straPattern);

      }

      return stra;

   }


   string image_list_impact::get_link_prefix()
   {

      if (m_strLinkPrefix.has_char())
      {

         return m_strLinkPrefix;

      }

      return string(m_pathFolder.name()) + "/";

   }


   ::file::path image_list_impact::get_link_path(string strLink)
   {

      if (strLink.case_insensitive_begins_eat(get_link_prefix()))
      {

         return m_pathFolder / strLink;

      }

      return "";

   }


   void image_list_impact::update_data(bool bSaveAndValidate)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (bSaveAndValidate)
      {

         return;

      }
      else
      {

         synchronous_lock synchronouslock(this->synchronization());

         m_pimageaThumb->m_imagea.clear();

         m_pimagea->m_imagea.clear();

         auto pcontext = m_pcontext;

         auto papp = get_app();

         if (m_pathFolder.has_char())
         {

            __defer_construct_new(m_plisting);

            m_plisting->erase_all();

            m_plisting->set_pattern_file_listing(m_pathFolder, get_ls_pattern_stra());

            dir()->enumerate(*m_plisting);

         }

         load_images();

         ::user::image_list::update_data(false);

      }

   }


   void image_list_impact::load_images()
   {

      m_iForkAddDib++;

      fork([this]()
      {

         synchronous_lock synchronouslock(this->synchronization());

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

                  pimageSmall = m_pcontext->m_pauracontext->create_image({256,  256 * pimage1->height() / pimage1->width()});

                  image_source imagesource(pimage1);

                  image_drawing_options imagedrawingoptions(pimageSmall->rectangle());

                  image_drawing imagedrawing(imagedrawingoptions, imagesource);

                  pimageSmall->g()->draw(imagedrawing);

                  pimage1 = pimageSmall;

               }

               if (pimage1->is_set())
               {

                  pimage1->get_extension()->payload("read_only_link") = get_link_prefix() + path.name();

                  synchronouslock.lock();

                  i++;

                  m_pimagea->add_image(pimage1);

                  set_need_layout();

               }
               else
               {

                  synchronouslock.lock();

                  information("(2) Could not pimage->load_from_file.file=" + m_plisting->element_at(i));

                  m_plisting->erase_at(i);

               }

            }
            else
            {

               synchronouslock.lock();

               information("Could not pimage->load_from_file.file=" + m_plisting->element_at(i));

               m_plisting->erase_at(i);

            }

         }

      });

   }

   //void image_list_impact::assert_ok() const
   //{
   //   ::user::image_list_impact::assert_ok();
   //}

   //void image_list_impact::dump(dump_context & dumpcontext) const
   //{
   //   ::user::image_list_impact::dump(dumpcontext);
   //}


   void image_list_impact::install_message_routing(::channel * pchannel)
   {

      ::user::image_list_impact::install_message_routing(pchannel);

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &image_list_impact::on_message_create);
      MESSAGE_LINK(MESSAGE_DESTROY, pchannel, this, &image_list_impact::on_message_destroy);
//      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &image_list_impact::on_message_left_button_down);
      //    MESSAGE_LINK(e_message_mouse_move, pchannel, this, &image_list_impact::on_message_mouse_move);
      //  MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &image_list_impact::on_message_mouse_leave);

   }


   //void image_list_impact::on_message_left_button_down(::message::message * pmessage)
   //{

   //   auto pmouse = pmessage->m_union.m_pmouse;

   //   const ::point_i32 & point = pmouse->m_point;

   //   screen_to_client()(point);

   //   int iMenuSel;

   //   int iCommandSel;

   //   int iHover = hit_test(point, iMenuSel, iCommandSel);

   //   if (iCommandSel >= 0)
   //   {

   //      m_iMenuSel = iMenuSel;

   //      m_iCommandSel = iCommandSel;

   //   }

   //}


   //void image_list_impact::on_message_mouse_move(::message::message * pmessage)
   //{

   //   auto pmouse = pmessage->m_union.m_pmouse;

   //   const ::point_i32 & point = pmouse->m_point;

   //   screen_to_client()(point);

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


   //void image_list_impact::on_message_mouse_leave(::message::message * pmessage)
   //{

   //auto psession = get_session();

   //auto puser = psession->user();

   //auto pwindowing = puser->windowing();

   //pwindowing->release_capture();

   //   m_iMenuHover = -1;

   //   m_iCommandHover = -1;

   //}


   void image_list_impact::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      ::atom atom = get_document()->m_pimpactsystem->m_atom;

      string strText;

      auto papp = get_app();

      papp->datastream()->get(m_atom + ".cur_text", strText);

   }


   void image_list_impact::on_message_destroy(::message::message * pmessage)
   {

   }


   void image_list_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::image_list_impact::handle(ptopic, pcontext);

      if (ptopic->m_atom == id_after_change_text)
      {

         auto * peditimpact = _001TypedWindow < ::userex::top_edit_impact >();

         if (peditimpact != nullptr && ptopic->m_puserelement == peditimpact)
         {

            string strText;

            peditimpact->_001GetText(strText);

         }

      }

   }


   void image_list_impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {


      ::user::image_list_impact::on_layout(pgraphics);

   }


   bool image_list_impact::_001GetItemText(string & str, index iItem)
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


