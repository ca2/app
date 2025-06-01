// Created by camilo on 2023-02-21 04:00 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "file_dialog.h"
#include "acme/user/user/element.h"
#include "acme/platform/node.h"
//#include "path.h"
////#include "acme/prototype/prototype/payload.h"
////#include "acme/prototype/collection/numeric_array.h"
//

//CLASS_DECL_ACME string ::url::decode(const string & str);

//CLASS_DECL_ACME::file::path __xxxnode_full_file_path(file::path path);


namespace file
{


   //CLASS_DECL_ACME string_array get_pattern_list(const file_dialog_filter & filedialogfiltera)
   //{

   //   ::string_array stra;

   //   for (auto & filedialogfilter : filedialogfiltera)
   //   {

   //      ::string_array straPattern;

   //      straPattern.explode(";", filedialogfilter.m_strPatternList);

   //      straPattern.trim();

   //      stra.append_unique(straPattern);


   //   }

   //   return stra;

   //}


   ::string_array file_dialog_filter_item::get_preserve_extensions() const
   {

      ::string_array stra;

      stra.explode(";", m_strPatternList, false);

      stra.trim();

      stra.erase_empty();

      if (stra.is_empty())
      {

         return {};

      }

      for (auto& str : stra)
      {

         str.begins_eat("*.");

      }

      stra.erase_empty();

      return stra;

   }


   ::string file_dialog_filter_item::get_main_extension() const
   {

      auto stra = get_preserve_extensions();

      if (stra.is_empty())
      {

         return {};

      }

      auto strFirst = stra.first();

      if (strFirst == "*")
      {

         return {};

      }

      return strFirst;

   }


   ::collection::index file_dialog_filter::find_first_with_extension(const ::scoped_string & scopedstrExtension)
   {

      ::string_array stra;
      
      ::collection::index i = 0;

      for (auto& item : *this)
      {

         auto straItem = item.get_preserve_extensions();

         if(straItem.case_insensitive_contains(scopedstrExtension))
         {
            
            return i;
            
         }
         
         i++;

      }

      return -1;

   }


   ::string_array file_dialog_filter::get_all_related_extensions() const
   {

      ::string_array stra;

      for (auto& item : *this)
      {

         auto straItem = item.get_preserve_extensions();

         for (auto& strItem : straItem)
         {

            stra.case_insensitive_add_unique(strItem);

         }

      }

      stra.erase("*");

      return ::transfer(stra);

   }


   file_dialog::file_dialog()
   {


   }


   file_dialog::~file_dialog()
   {


   }


   void file_dialog::pick_single_file(
      ::user::element* puserelement,
      const file_dialog_filter& filedialogfilter,
      const ::function < void(::pointer<file_dialog>) >& function,
      bool bSave,
      const ::file::path& pathStartFolder)
   {

      //      auto functionHere = [function](::pointer<::operating_system_file_dialog> pdialog)
      //      {
      //
      //         if (stra.size() <= 0)
      //         {
      //
      //            function("");
      //
      //         }
      //         else
      //         {
      //
      //            function(stra.first());
      //
      //         }
      //
      //      };
      //
            //auto pdialog = __allocate < ::operating_system_file_dialog >(this,

      m_puserelement = puserelement;
      m_filedialogfilter.copy(filedialogfilter);
      m_function = function;
      m_pathStartFolder = pathStartFolder;
      m_bSave = bSave;
      m_bMultiple = false;

      call();
      //                                                        poswindow,
      //                                                        nullptr,
      //                                                        filetypes, functionHere, pathStartFolder, save, false));
      //
      //      operating_system_file_dialog(pdialog);
      //
      ////      operating_system_file_dialog(
      ////         poswindow,
      ////         filetypes,
      ////,
      ////         save,
      ////            false);

   }


   void file_dialog::pick_multiple_file(
      ::user::element* puserelement,
      const file_dialog_filter& filedialogfilter,
      const ::function < void(::pointer<file_dialog>) >& function,
      const ::file::path& pathStartFolder)
   {
      //
      //      operating_system_file_dialog(
      //         poswindow,
      //         filetypes,
      //         function,
      //         false,
      //         false);

      //      auto pdialog = __initialize_new ::operating_system_file_dialog(this,
      //                                                        poswindow,
      //                                                        nullptr,
      //                                                        filetypes, function, false, false));
      //
      //      operating_system_file_dialog(pdialog);

      m_puserelement = puserelement;
      m_filedialogfilter.copy(filedialogfilter);
      m_function = function;
      m_pathStartFolder = pathStartFolder;
      m_bSave = false;
      m_bMultiple = true;

      call();

   }


   ::file::path file_dialog::_get_file_path() const
   {

      if (m_patha.is_empty())
      {

         return {};

      }
      else if (m_patha.get_count() >= 2)
      {

         throw ::exception(error_wrong_state);

      }

      return m_patha.first();

   }


   ::file::path file_dialog::get_file_path() const
   {

      if (m_bSave)
      {

         return process_file_path(_get_file_path());

      }

      return _get_file_path();

   }


   ::file::path file_dialog::process_file_path(const ::file::path& pathParam) const
   {

      auto path = pathParam;

      path.defer_set_extension(this);

      return path;

   }


   const ::file::file_dialog_filter_item* file_dialog::get_selected_filter() const
   {

      if (m_iFilter < 0 ||
         m_iFilter >= m_filedialogfilter.count())
      {

         return nullptr;

      }

      return &m_filedialogfilter[m_iFilter];

   }


   void file_dialog::do_callback()
   {

      m_function(this);

   }


   ::string file_dialog::get_selected_filter_main_extension() const
   {

      auto pitem = get_selected_filter();

      if (::is_null(pitem))
      {

         return {};

      }

      return pitem->get_main_extension();



   }


} // namespace file



