#pragma once


namespace filemanager
{


   class  CLASS_DECL_CORE folder_list_view:
      virtual public simple_list_view,
      virtual public ::filemanager::impact
   {
   public:


      

      bool                             m_bRecursive;
      bool                             m_bRecursiveColumn;


      folder_list_view();
      virtual ~folder_list_view();


      virtual void install_message_routing(::channel * pchannel) override;


      virtual void initialize(string strDataKeyModifier,bool bRecursive);


      virtual void _001InsertColumns() override;


      bool add_unique(const string_array & stra);
      bool add_unique(const string_array & stra, int_array & baRecursive);
      bool remove(const string_array & stra);


      virtual void GetSel(string_array & stra);

      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;


   };


} // namespace filemanager













