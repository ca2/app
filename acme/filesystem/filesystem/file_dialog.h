// Created by camilo on 2023-02-21 04:00 BRT <3ThomasBorregaardSorensen!!
#pragma once


namespace file
{


   struct file_dialog_filter
   {

      ::string       m_strName;
      ::string       m_strPatternList;

   };


   CLASS_DECL_ACME string_array get_pattern_list(const ::array < file_dialog_filter > & filedialogfiltera);


   class CLASS_DECL_ACME file_dialog :
           virtual public particle
   {
   public:


      //void *                                           m_poswindow;
      void *                                             m_posdata;
      ::pointer < ::user::element>                       m_puserelement;
      ::array < file_dialog_filter >                     m_filedialogfiltera;
      ::function < void(::pointer<file_dialog>) >        m_function;
      ::file::path                                       m_pathStartFolder;
      bool                                               m_bSave;
      bool                                               m_bMultiple;
      ::file::path_array                                 m_patha;

      
      file_dialog();
      ~file_dialog() override;
      
//      void start()
//      {
//         
//         acmenode()->operating_system_file_dialog(this);
//         
//      }
      
      void pick_single_file(
         ::user::element * puserelement,
         const ::array < file_dialog_filter >& filedialogfiltera,
         const ::function < void(::pointer<file_dialog>) >& function,
         bool save,
         const ::file::path & pathStartFolder = {});


      void pick_multiple_file(
                              ::user::element * puserelement,
         const ::array < file_dialog_filter > & filedialogfiltera,
                              const ::function < void(::pointer<file_dialog>) >& function,
                              const ::file::path & pathStartFolder = {});
     
   //   void pick_single_file(
   //::user::element * pelement
   ////           ::particle * pparticle,
   //  //         void * poswindow,
   //    //       void * posdata,
   //           const ::array < ::pair < ::string, ::string > > & filetypes,
   //           const ::function < void(::pointer<operating_system_file_dialog>) > & function,
   //                                const ::file::path & pathStartDir,
   //           bool bSave,
   //           bool bMultiple) :
   //           m_poswindow(poswindow),
   //           m_posdata(posdata),
   //           m_filetypes(filetypes),
   //           m_function(function),
   //   m_pathStartDir(pathStartDir),
   //           m_bSave(bSave),
   //           m_bMultiple(bMultiple)
   //   {
   //      initialize(pparticle);
   //   }
   };


} // namespace file



