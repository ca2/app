#pragma once


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


   __pointer(::image_list)             m_pimagelist;
   __pointer(::image_list)             m_pimagelistDisabled;
   i32_spreadset *                     m_prel;
   bool                                m_bTracking;
   index                               m_iTracking;
   ::u32                                m_uResourceId;
   index                               m_iTopMenuCount;
   __composite(::user::menu)           m_pmenu;


   simple_menu_bar();
   virtual ~simple_menu_bar();


   using ::simple_toolbar::create_window;
   bool create_window(::user::interaction * puiParent, u32 uStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP, ::id id = __IDW_TOOLBAR) override;


   using ::simple_toolbar::create_window_ex;
   bool create_window_ex(::user::interaction * puiParent, u32 dwCtrlStyle = TBSTYLE_FLAT, u32 uStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP, ::id id = __IDW_TOOLBAR);


   LRESULT CALLBACK MessageProc(
   index code,  // hook code
   WPARAM wParam,  // undefined
   LPARAM lParam   // address of structure with message data
   );

   virtual void route_command_message(::user::command * pcommand) override;
   virtual void pre_translate_message(::message::message * pmessage) override;
protected:
   virtual bool pre_create_window(::user::create_struct& cs) override;

   //virtual index _001GetHoverItem() override;
   //virtual void OnUpdateHover() override;
   virtual bool on_click(const ::user::item & item) override;
   void _001OnDropDown(index iItem);
   //index _001GetHoverItem();
   //void _001Hover(const ::point & point);
   //void _001Hover();
   //void _001DrawItem(::draw2d::graphics_pointer & pgraphics, index iItem);
   //index _001HitTest(const POINT32 * point);
   //bool _001CheckItem(index iItem, bool bCheck);
   //bool _001GetItemRect(index iItem, RECT32 * prect, e_element eelement);

   //virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);
   bool ReloadMenuBar();
   virtual void OnUpdateCmdUI(__pointer(::user::frame_window) pTarget, bool bDisableIfNoHndler);
   void RemoveAllButtons();

   bool Initialize(
   __pointer(::image_list) imagelist,
   __pointer(::image_list) imagelistDisabled,
   ::i32_spreadset * prel,
   ::draw2d::font * pfont);

   //size CalcLayout(u32 dwMode, index nLength);

   //size CalcFixedLayout(bool bStretch, bool bHorz);

   //size CalcDynamicLayout(index nLength, u32 dwMode);
   //static ::estatus  CalcSize(::user::toolbar_control & tbc, size & size);
   //static ::estatus  CalcSize(CToolBarCtrl & tbc, size & size);
   bool _track_popup_menu(const ::point & point);
   bool _track_popup_menu(index iItem);
   bool LoadMenuBar(::u32 nIDResource);
   void SetMenuID(::u32 nIDResource);

   //DECL_GEN_SIGNAL(_001OnMouseMove);
   //DECL_GEN_SIGNAL(_001OnNcMouseMove);
   DECL_GEN_SIGNAL(_001OnCreate);
   DECL_GEN_SIGNAL(_001OnKeyDown);
   DECL_GEN_SIGNAL(_001OnDestroy);
   DECL_GEN_SIGNAL(_001OnMenuChar);
   //DECL_GEN_SIGNAL(_001OnLButtonDown);
   //DECL_GEN_SIGNAL(_001OnAppLanguage);
   void _001OnTimer(::timer * ptimer) override;

   //virtual index OnMessage(MPARAM mparam, NPARAM nparam, OPARAM oparam);

   //DECL_GEN_SIGNAL(_001OnAppLanguage);

   virtual void install_message_routing(::channel * pchannel) override;


};



