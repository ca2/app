#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE view :
      virtual public ::user::split_view,
      virtual public impact
   {
   public:


      view();
      virtual ~view();


      virtual void install_message_routing(::channel * pchannel) override;


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      virtual void on_create_split_impact() override;

      void FileManagerBrowse(const char * pcwstr, const ::action_context & action_context);


      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;


   };



} // namespace filemanager




