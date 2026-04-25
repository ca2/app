#pragma once


////#include "acme/prototype/prototype/object.h"
#include "acme/prototype/collection/atom_map.h"


namespace user
{


   class CLASS_DECL_BERG document_manager :
      virtual public ::object
   {
   public:


      //pointer_array < ::user::impact_system >       m_templateptra;

      atom_map_base < ::pointer < ::user::impact_system > > m_mapImpactSystem;


      static ::string_literal gen_ShellOpenFmt;
      static ::string_literal gen_ShellPrintFmt;
      static ::string_literal gen_ShellPrintToFmt;
      static ::string_literal gen_DefaultIconFmt;
      static ::string_literal gen_ShellNewFmt;

#define DEFAULT_ICON_INDEX 0

      static ::string_literal gen_IconIndexFmt;
      static ::string_literal gen_Command;
      static ::string_literal gen_OpenArg;
      static ::string_literal gen_PrintArg;
      static ::string_literal gen_PrintToArg;
      static ::string_literal gen_DDEArg;

      static ::string_literal gen_DDEExec;
      static ::string_literal gen_DDEOpen;

      static ::string_literal gen_DDEPrint;
      static ::string_literal gen_DDEPrintTo;

      static ::string_literal gen_ShellNewValueName;
      static ::string_literal gen_ShellNewValue;


      document_manager();
      ~document_manager() override;


      void on_initialize_particle() override;


      void destroy() override;


      virtual void add_impact_system(const ::atom & atom, const ::pointer<::user::impact_system> & pimpactsystem);


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;
      virtual ::pointer < ::user::impact_system > & __impact_system(const ::atom & atom);
      virtual void on_add_impact_system(const ::atom & atom);
      virtual void erase_impact_system(const ::atom & atom);
      virtual ::collection::count get_impact_system_count() const;
      //virtual ::user::impact_system * get_template(::collection::index index) const;
      virtual void RegisterShellFileTypes(bool bCompat);
      void UnregisterShellFileTypes();
      void request(::request * prequest) override; // open named file
      virtual bool save_all_modified(); // save before exit
      virtual void pre_close_all_documents(); // pre close documents before exiting
      virtual void close_all_documents(bool bEndApp); // close documents before exiting
      virtual ::collection::count get_open_document_count();

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      virtual bool do_prompt_file_name(::payload & payloadFile, string nIDSTitle, unsigned int lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument);

      virtual bool OnDDECommand(const ::scoped_string & scopedstrDDECommand);

      virtual void _001OnFileNew();
      virtual void on_file_open();

      ::collection::count get_document_count(); // helper to ::collection::count number of total documents



   };


} // namespace user






