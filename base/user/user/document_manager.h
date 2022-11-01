#pragma once


#include "acme/primitive/primitive/object.h"


namespace user
{


   class CLASS_DECL_BASE document_manager :
      virtual public ::object
   {
   public:


      pointer_array < ::user::impact_system >       m_templateptra;


      static const char gen_ShellOpenFmt[];
      static const char gen_ShellPrintFmt[];
      static const char gen_ShellPrintToFmt[];
      static const char gen_DefaultIconFmt[];
      static const char gen_ShellNewFmt[];

#define DEFAULT_ICON_INDEX 0

      static  const char gen_IconIndexFmt[];
      static  const char gen_Command[];
      static  const char gen_OpenArg[];
      static  const char gen_PrintArg[];
      static  const char gen_PrintToArg[];
      static  const char gen_DDEArg[];

      static  const char gen_DDEExec[];
      static  const char gen_DDEOpen[];

      static const char gen_DDEPrint[];
      static const char gen_DDEPrintTo[];

      static const char gen_ShellNewValueName[];
      static const char gen_ShellNewValue[];


      document_manager();
      virtual ~document_manager();

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      virtual void add_document_template(::user::impact_system * ptemplate);
      virtual void erase_document_template(::user::impact_system * ptemplate);
      virtual ::count get_template_count() const;
      virtual ::user::impact_system * get_template(index index) const;
      virtual void RegisterShellFileTypes(bool bCompat);
      void UnregisterShellFileTypes();
      void request(::create * pcreate) override; // open named file
      virtual bool save_all_modified(); // save before exit
      virtual void pre_close_all_documents(); // pre close documents before exiting
      virtual void close_all_documents(bool bEndApp); // close documents before exiting
      virtual ::count get_open_document_count();

      void handle(::topic * ptopic, ::context * pcontext) override;

      virtual bool do_prompt_file_name(::payload & payloadFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument);

      virtual bool OnDDECommand(char * pszCommand);

      virtual void _001OnFileNew();
      virtual void on_file_open();

      ::count get_document_count(); // helper to ::count number of total documents



   };


} // namespace user






