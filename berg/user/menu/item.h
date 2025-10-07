#pragma once


#include "acme/handler/item.h"


namespace menu
{


   class CLASS_DECL_BERG item :
      virtual public ::item
   {
   public:


      ::item_pointer                   m_pitemParent;
      atom                             m_atomItem;
      ::pointer<::menu::item_ptra>     m_pmenuitema;
      ::pointer<::menu::item>          m_pmenuitemParent;
      //int                            m_iFullHeightItemCount;
      //int                            m_iSeparatorCount;
      ::pointer<::user::interaction>   m_puserinteraction;
      ::pointer<::user::interaction>   m_puserinteractionHost;
      bool                             m_bPopup;
      bool                             m_bBreak;
      int                              m_iLevel;
      ::pointer<::user::menu>          m_pmenu;
      string                           m_strTitle;
      ::int_rectangle                  m_rectangleUi;
      int                            m_iColumn;
      int                            m_iRow;
      ::pointer<::image::image>        m_pimage;
      //::pointer<::item_array>        m_pmenuitema;


      item();
      ~item() override;


      void destroy() override;


      //void menu_item_destruct();


      void add_item(::menu::item * pitem);
      ::menu::item * separator();
      bool create_menu(const string_array_base & straCommand, const string_array_base & straCommandTitle);
      bool load_menu(::xml::node * pxmlnode);
      bool load_menu(::xml::node * pxmlnode, int iLevel);

      //virtual void OnAddRef();
      //virtual void OnRelease();

      virtual ::collection::count get_separator_item_count();
      virtual ::collection::count get_full_height_item_count();

      virtual bool create_buttons(::draw2d::graphics_pointer& pgraphics, ::user::menu * pusermenu);
      virtual bool contains_menu_item(::menu::item * pitem, bool bRecursive = true) const;

      
      virtual bool is_popup() const;
      virtual bool is_separator() const;


      virtual void release_children_interaction();

      
      virtual ::menu::item * find(const ::atom & atom);


   };


} // namespace menu



