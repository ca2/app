#include "framework.h"
#include "item.h"
#include "tree_data.h"
#include "acme/constant/message.h"
#include "acme/primitive/data/listener.h"
#include "acme/primitive/data/tree_item.h"
#include "aura/user/user/shell.h"
#include "aura/user/user/interaction_array.h"
#include "base/user/user/user.h"
#include "core/user/user/tree.h"
#include "core/platform/session.h"


namespace userfs
{


   item::item(::userfs::tree_data * ptreedata) :
      m_ptreedata(ptreedata)
   {
      
      //m_iImage = -1;
      //m_iImageSelected = -1;

   }


   item::~item()
   {

   }



   ::std::strong_ordering item::CompareArrangeByName(const ::pointer<::data::tree_item>& pitem1, const ::pointer<::data::tree_item> pitem2)
   {

      if(pitem1->m_ptree == pitem2->m_ptree)
      {

         return pitem1->m_pdataitem.cast < item >()->m_strName.case_insensitive_order(pitem2->m_pdataitem.cast < item >()->m_strName);

      }
      else
      {

         return ansi_cmp(typeid(pitem1).name(), typeid(pitem2).name()) <=> 0;

      }

   }

   i32 item::get_index() const
   {
      return m_iIndex;
   }

   bool item::is_folder() const
   {
      return m_flags.has(::file::e_flag_folder);
   }



   string item::data_item_get_text(::particle * pparticle) const
   {

      UNREFERENCED_PARAMETER(pparticle);

      return m_strName;

   }


   index item::data_item_get_image(::particle * pparticle) const
   {

      ::user::shell::enum_file_attribute efileattribute;

      if (m_flags & ::file::e_flag_folder)
      {

         efileattribute = ::user::shell::e_file_attribute_directory;

      }
      else
      {

         efileattribute = ::user::shell::e_file_attribute_normal;

      }

      ::user::shell::enum_icon eicon;

      if (m_ptreedata->is_selected(this))
      {

         eicon = ::user::shell::e_icon_open;

      }
      else
      {

         eicon = ::user::shell::e_icon_normal;

      }

      auto psession = m_ptreedata->get_session();

      auto puser = psession->user();

      auto pshell = puser->shell();

      auto iImage = pshell->get_file_image(user_path(), efileattribute, eicon);

      if (iImage >= 0)
      {

         return iImage;

      }

      pshell->warn_when_ok(user_path(), m_ptreedata->m_usertreea);

      iImage = pshell->get_file_image(final_path(), efileattribute, eicon);

      if(iImage < 0)
      {

         pshell->warn_when_ok(final_path(), m_ptreedata->m_usertreea);

      }

      return iImage;

   }


   ::image_list * item::data_item_get_image_list(::particle * pparticle) const
   {

      return m_ptreedata->m_pimagelist;

   }


} // namespace userfs





