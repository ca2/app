#pragma once


#include "base/user/simple/toolbar.h"


namespace user
{


   class toolbar_control;


} // namespace user


class SimpleMenu;
class CMenuTrackingThreadV033;
class CMenuBarHookV033;

class CLASS_DECL_CORE simple_menu_bar :
   public simple_toolbar
{
public:


   ::image::image_list_pointer              m_pimagelist;
   ::image::image_list_pointer              m_pimagelistDisabled;
   int_spreadset *                     m_prel;
   bool                                m_bTracking;
   ::collection::index                               m_iTracking;
   unsigned int                               m_uResourceId;
   ::collection::index                               m_iTopMenuCount;
   ::pointer<::user::menu>             m_pmenu;


   simple_menu_bar();
   virtual ~simple_menu_bar();


   //using ::simple_toolbar::create_window;
   //bool create_window(::user::interaction * puiParent, unsigned int uStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP, ::atom atom = __IDW_TOOLBAR) override;


   //using ::simple_toolbar::create_window_ex;
   //bool create_window_ex(::user::interaction * puiParent, unsigned int dwCtrlStyle = TBSTYLE_FLAT, unsigned int uStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP, ::atom atom = __IDW_TOOLBAR);

//
//#ifdef WINDOWS_DESKTOP
//
//   LRESULT CALLBACK MessageProc(
//   index code,  // hook code
//   WPARAM wParam,  // undefined
//   LPARAM lParam   // address of structure with message data
//   );
//
//#endif


   void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;
   virtual void pre_translate_message(::message::message * pmessage) override;


protected:
   virtual bool pre_create_window(::user::system * pusersystem) override;

   //virtual ::collection::index _001GetHoverItem() override;
   //virtual void OnUpdateHover() override;
   bool on_click(::item * pitem) override;
   void _001OnDropDown(::collection::index iItem);
   //index _001GetHoverItem();
   //void _001Hover(const ::int_point & point);
   //void _001Hover();
   //void _001DrawItem(::draw2d::graphics_pointer & pgraphics, ::collection::index iItem);
   //index _001HitTest(const ::int_point * int_point);
   //bool _001CheckItem(::collection::index iItem, bool bCheck);
   //bool index_item_rectangle(::collection::index iItem, ::int_rectangle * prectangle, enum_element eelement);

   //virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);
   bool ReloadMenuBar();
   virtual void OnUpdateCmdUI(::pointer<::user::frame_window>pTarget, bool bDisableIfNoHndler);
   void RemoveAllButtons();

   bool Initialize(
   ::image::image_list_pointer imagelist,
   ::image::image_list_pointer imagelistDisabled,
   ::int_spreadset * prel,
   ::write_text::font * pfont);

   //int_size CalcLayout(unsigned int dwMode, ::collection::index nLength);

   //int_size CalcFixedLayout(bool bStretch, bool bHorz);

   //int_size CalcDynamicLayout(index nLength, unsigned int dwMode);
   //static void  CalcSize(::user::toolbar_control & tbc, int_size & size);
   //static void  CalcSize(CToolBarCtrl & tbc, int_size & size);
   bool _track_popup_menu(const ::int_point & point);
   bool _track_popup_menu(::collection::index iItem);
   bool LoadMenuBar(unsigned int nIDResource);
   void SetMenuID(unsigned int nIDResource);

   //DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
   //DECLARE_MESSAGE_HANDLER(_001OnNcMouseMove);
   DECLARE_MESSAGE_HANDLER(on_message_create);
   DECLARE_MESSAGE_HANDLER(on_message_key_down);
   DECLARE_MESSAGE_HANDLER(on_message_destroy);
   DECLARE_MESSAGE_HANDLER(_001OnMenuChar);
   //DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
   //DECLARE_MESSAGE_HANDLER(_001OnAppLanguage);
   void _001OnTimer(::timer * ptimer) override;

   //virtual ::collection::index OnMessage(MPARAM mparam, NPARAM nparam, OPARAM oparam);

   //DECLARE_MESSAGE_HANDLER(_001OnAppLanguage);

   void install_message_routing(::channel * pchannel) override;


};



