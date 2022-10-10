#pragma once


namespace xml
{


   enum e_action
   {

      action_none,
      action_set_attribute,
      action_set_name,
      action_set_value //,
      //action_add_attr

   };


   class CLASS_DECL_AQUA edit_item :
      virtual public ::object
   {
   public:

      
      e_action          m_eaction;
      index_array       m_iaPath;
      string            m_strName;
      string            m_strValue;


      edit_item();


      void set_name(const ::pointer<::xml::node>pnode);
      void set_value(const ::pointer<::xml::node>pnode);
      void set_attribute(const ::pointer<::xml::node>pnode, const property * pproperty);


      //virtual ::stream & write(::stream & stream) const override;
      //virtual ::stream & read(::stream & stream) override;


   };


   class CLASS_DECL_AQUA edit :
      public ::object
   {
   public:


      ::pointer<document>             m_pdocument;
      index                            m_iEdit;
      pointer_array < edit_item >       m_edititema;


      edit();
      virtual ~edit();


      void set_name(const ::pointer<::xml::node>pnode);
      void set_value(const ::pointer<::xml::node>pnode);
      void set_attribute(const ::pointer<::xml::node>pnode, const property * pproperty);


   };


} // namespace xml



