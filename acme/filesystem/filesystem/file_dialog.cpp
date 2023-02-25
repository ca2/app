// Created by camilo on 2023-02-21 04:00 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "file_dialog.h"
#include "acme/user/user/element.h"
//#include "path.h"
////#include "acme/primitive/primitive/payload.h"
////#include "acme/primitive/collection/numeric_array.h"
//

//CLASS_DECL_ACME string ::url::decode(const string & str);

//CLASS_DECL_ACME::file::path __xxxnode_full_file_path(file::path path);


namespace file
{


file_dialog::file_dialog()
{
   
   
}


file_dialog::~file_dialog()
{
   
   
}


   void file_dialog::pick_single_file(
      ::user::element * puserelement,
      const ::array < ::pair < ::string, ::string > >& filetypes,
      const ::function < void(::pointer<file_dialog>) >& function,
      bool bSave,
                            const ::file::path & pathStartFolder)
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
      //auto pdialog = __new(::operating_system_file_dialog(this,
   
   m_puserelement = puserelement;
   m_filetypes = filetypes;
   m_function = function;
   m_pathStartFolder = pathStartFolder;
   m_bSave = bSave;
   m_bMultiple = false;
   
   call_run();
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
      ::user::element * puserelement,
      const ::array < ::pair < ::string, ::string > >& filetypes,
      const ::function < void(::pointer<file_dialog>) >& function,
                                        const ::file::path & pathStartFolder)
   {
//
//      operating_system_file_dialog(
//         poswindow,
//         filetypes,
//         function,
//         false,
//         false);

//      auto pdialog = __new(::operating_system_file_dialog(this,
//                                                        poswindow,
//                                                        nullptr,
//                                                        filetypes, function, false, false));
//
//      operating_system_file_dialog(pdialog);

      m_puserelement = puserelement;
      m_filetypes = filetypes;
      m_function = function;
      m_pathStartFolder = pathStartFolder;
      m_bSave = false;
      m_bMultiple = true;
      
      call_run();

   }


} // namespace file



