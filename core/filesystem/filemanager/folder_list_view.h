#pragma once


namespace filemanager
{


   class  CLASS_DECL_CORE folder_list_view:
      virtual public ::filemanager_show < simple_list_view >
   {
   public:


      bool                             m_bRecursive;
      bool                             m_bRecursiveColumn;
      __pointer(folder_list_data)      m_pfolderlistdata;


      folder_list_view();
      virtual ~folder_list_view();


      void install_message_routing(::channel * pchannel) override;


      virtual void initialize(string strDataKeyModifier,bool bRecursive);


      virtual void _001InsertColumns() override;


      bool add_unique(const string_array & stra);
      bool add_unique(const string_array & stra, int_array & baRecursive);
      bool erase(const string_array & stra);


      void on_check_save(::user::interaction* puserinteraction) override;
      void on_check_load(::user::interaction* puserinteraction) override;

      virtual void GetSel(string_array & stra);

      virtual void handle(::subject * psubject, ::context * pcontext) override;


   };


} // namespace filemanager













