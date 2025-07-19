// Created by camilo on 2023-02-21 04:00 BRT <3ThomasBorregaardSorensen!!
#pragma once


namespace file
{


   class CLASS_DECL_ACME file_dialog_filter_item
   {

   public:

      ::string       m_strName;
      ::string       m_strPatternList;


      ::string get_main_extension() const;
      ::string_array get_preserve_extensions() const;

   };

   class CLASS_DECL_ACME file_dialog_filter :
      public ::array < file_dialog_filter_item >
   {

   public:

      using ::array < file_dialog_filter_item >::array;

      ::collection::index find_first_with_extension(const ::scoped_string & scopedstrExtension);
      ::string_array get_all_related_extensions() const;
      ::string_array get_pattern_list() const;

   };


   //CLASS_DECL_ACME string_array get_pattern_list(const file_dialog_filter & filedialogfiltera);


   class CLASS_DECL_ACME file_dialog :
           virtual public particle
   {
   public:


      //void *                                           m_poswindow;
      void *                                             m_posdata;
      ::pointer < ::user::element>                       m_puserelement;
      file_dialog_filter                                 m_filedialogfilter;
      ::function < void(::pointer<file_dialog>) >        m_function;
      ::file::path                                       m_pathStartFolder;
      bool                                               m_bSave;
      bool                                               m_bMultiple;
      ::file::path_array                                 m_patha;
      ::collection::index                                m_iFilter;

      
      file_dialog();
      ~file_dialog() override;
      
//      void start()
//      {
//         
//         node()->operating_system_file_dialog(this);
//         
//      }
      
      void pick_single_file(
         ::user::element * puserelement,
         const file_dialog_filter& filedialogfiltera,
         const ::function < void(::pointer<file_dialog>) >& function,
         bool save,
         const ::file::path & pathStartFolder = {});


      void pick_multiple_file(
                              ::user::element * puserelement,
         const file_dialog_filter & filedialogfiltera,
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

      ::file::path _get_file_path() const;

      ::file::path get_file_path() const;

      ::file::path process_file_path(const ::file::path & path) const;

      const ::file::file_dialog_filter_item * get_selected_filter() const;

      ::string get_selected_filter_main_extension() const;

      void do_callback();

   };


   inline void path::defer_set_extension(const ::file::file_dialog* pdialog)
   {

      if (::is_null(pdialog))
      {

         return;

      }

      auto pfilteritem = pdialog->get_selected_filter();

      if (::is_null(pfilteritem))
      {

         return;

      }

      return defer_set_extension(
         pfilteritem->get_preserve_extensions(),
         pdialog->m_filedialogfilter.get_all_related_extensions());

   }



} // namespace file



