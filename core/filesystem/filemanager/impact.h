#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE impact :
      virtual public ::filemanager_show < ::user::split_view >
   {
   public:


      impact();
      virtual ~impact();


      virtual void install_message_routing(::channel * pchannel) override;


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      virtual void on_create_split_impact() override;

      void FileManagerBrowse(const ::string & pcwstr, const ::action_context & action_context);


      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;


   };



} // namespace filemanager




