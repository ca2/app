#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE left_view :
      virtual public ::user::split_view,
      virtual public impact
   {
   public:


      ::user::tree *          m_pusertree;
      ::filemanager::tree *   m_ptree;


      left_view();
      virtual ~left_view();


      virtual void install_message_routing(::channel * pchannel) override;


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      void on_create_split_impact() override;

      void FileManagerBrowse(const char * pcwstr, const ::action_context & action_context);


      virtual void update(::update * pupdate) override;

   };



} // namespace filemanager



