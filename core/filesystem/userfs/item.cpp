#include "framework.h"
#include "core/user/user/shell.h"
#include "_data.h"
#include "_userfs.h"
#include "core/user/user/_tree.h"


namespace userfs
{

   item::item(::userfs::tree * ptree) :
      ::object(ptree->get_context_application()),
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
      return m_flags.has(::file::FlagFolder);
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

      UNREFERENCED_PARAMETER(pobject);

      return m_strName;

   }


   index item::data_item_get_image(object * pobject) const
   {

      if(m_ptree->is_selected(this))
      {

         return User.shell()->get_file_image(m_filepathFinal, ::user::shell::file_attribute_directory, ::user::shell::icon_open);

      }
      else
      {

         return User.shell()->get_file_image(m_filepathFinal, ::user::shell::file_attribute_directory, ::user::shell::icon_normal);

      }

   }


   image_list * item::data_item_get_image_list(object * pobject) const
   {

      return m_ptree->m_pimagelist;

   }


} // namespace userfs





