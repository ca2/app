#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_userfs.h"
#endif
#include "item.h"
#include "acme/primitive/data/tree_item.h"
#include "aura/user/user/shell.h"
#include "tree.h"
#include "core/user/user/tree.h"
#include "core/platform/session.h"
#include "base/user/user/user.h"


namespace userfs
{


   item::item(::userfs::tree * ptree) :
      m_ptree(ptree)
   {
      //m_iImage = -1;
      //m_iImageSelected = -1;
   }


   item::~item()
   {

   }



   index item::CompareArrangeByName(const __pointer(::data::tree_item) & pitem1, const __pointer(::data::tree_item) & pitem2)
   {

      if(pitem1->m_ptree == pitem2->m_ptree)
      {

         return pitem1->m_pdataitem.cast < item >()->m_strName.compare_ci(pitem2->m_pdataitem.cast < item >()->m_strName);

      }
      else
      {

         return strcmp(typeid(pitem1).name(), typeid(pitem2).name());

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


   stream& item::write(stream& s) const
   {

      ::data::item::write(s);
      ::file::item::write(s);

      return s;

   }


   stream& item::read(stream& s)
   {

      ::data::item::read(s);
      ::file::item::read(s);

      return s;

   }


   string item::data_item_get_text(object * pobject) const
   {

      __UNREFERENCED_PARAMETER(pobject);

      return m_strName;

   }


   index item::data_item_get_image(object * pobject) const
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

      if (m_ptree->is_selected(this))
      {

         eicon = ::user::shell::e_icon_open;

      }
      else
      {

         eicon = ::user::shell::e_icon_normal;

      }

      auto psession = m_ptree->get_session();

      auto puser = psession->user();

      auto pshell = puser->shell();

      auto iImage = pshell->get_file_image(user_path(), efileattribute, eicon);

      if (iImage >= 0)
      {

         return iImage;

      }

      pshell->warn_when_ok(user_path(), m_ptree->m_usertreea);

      iImage = pshell->get_file_image(final_path(), efileattribute, eicon);

      if(iImage < 0)
      {

         pshell->warn_when_ok(final_path(), m_ptree->m_usertreea);

      }

      return iImage;

   }


   ::image_list * item::data_item_get_image_list(::object * pobject) const
   {

      return m_ptree->m_pimagelist;

   }


} // namespace userfs





