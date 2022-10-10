#pragma once


namespace user
{


   class CLASS_DECL_BASE menu_item :
      virtual public ::object
   {
   public:


      atom                               m_atom;
      ::pointer<menu_item_ptra>       m_pmenuitema;
      ::pointer<menu_item>            m_pmenuitemParent;
      i32                              m_iFullHeightItemCount;
      i32                              m_iSeparatorCount;
      ::pointer<::user::interaction>  m_puserinteraction;
      ::pointer<::user::interaction>  m_puserinteractionHost;
      bool                             m_bPopup;
      bool                             m_bBreak;
      i32                              m_iLevel;
      ::pointer<::user::menu>         m_pmenu;
      string                           m_strTitle;
      ::rectangle_i32                           m_rectangleUi;
      int                              m_iColumn;
      ::pointer<::image>            m_pimage;


      menu_item();
      ~menu_item() override;


      void menu_item_destruct();


      void add_item(menu_item * pitem);
      bool create_menu(const string_array & straCommand, const string_array & straCommandTitle);
      bool load_menu(::xml::node * pxmlnode);
      bool load_menu(::xml::node * pxmlnode, i32 iLevel);

      virtual void OnAddRef();
      virtual void OnRelease();


      virtual bool create_buttons(::draw2d::graphics_pointer& pgraphics, menu * pmenu);
      virtual bool contains_menu_item(menu_item * pitem, bool bRecursive = true) const;

      bool IsPopup();
      menu_item * find(atom atom);



   };


} // namespace user



