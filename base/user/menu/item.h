#pragma once


#include "acme/handler/item.h"


namespace user
{


   class CLASS_DECL_BASE menu_item :
      virtual public ::item,
      virtual public ::object
   {
   public:


      ::item_pointer                   m_pitemParent;
      //::raw::index                          m_iCommand;
      //::raw::index                          m_iGroup;
      atom                             m_atom;
      ::pointer<menu_item_ptra>        m_pmenuitema;
      ::pointer<menu_item>             m_pmenuitemParent;
      i32                              m_iFullHeightItemCount;
      i32                              m_iSeparatorCount;
      ::pointer<::user::interaction>   m_puserinteraction;
      ::pointer<::user::interaction>   m_puserinteractionHost;
      bool                             m_bPopup;
      bool                             m_bBreak;
      i32                              m_iLevel;
      ::pointer<::user::menu>          m_pmenu;
      string                           m_strTitle;
      ::rectangle_i32                  m_rectangleUi;
      ::i32                            m_iColumn;
      ::i32                            m_iRow;
      ::pointer<::image>               m_pimage;
      //::pointer<::item_array>          m_pmenuitema;


      menu_item();
      ~menu_item() override;


      void menu_item_destruct();


      void add_item(menu_item * pitem);
      menu_item * separator();
      bool create_menu(const string_array & straCommand, const string_array & straCommandTitle);
      bool load_menu(::xml::node * pxmlnode);
      bool load_menu(::xml::node * pxmlnode, i32 iLevel);

      //virtual void OnAddRef();
      //virtual void OnRelease();


      virtual bool create_buttons(::draw2d::graphics_pointer& pgraphics, menu * pmenu);
      virtual bool contains_menu_item(menu_item * pitem, bool bRecursive = true) const;

      
      virtual bool is_popup() const;
      virtual bool is_separator() const;


      virtual void release_children_interaction();

      
      virtual menu_item * find(const ::atom & atom);


   };


} // namespace user



