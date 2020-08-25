#include "framework.h"
#include "aura/update.h"
#include "aura/const/timer.h"


//extern CLASS_DECL_BASE thread_int_ptr < DWORD_PTR > t_time1;

// pgraphics->GetTextExtent("->:<-"); // oh no!! omg!! The size is the size of the alien!!
#define MAGIC_PALACE_TAB_SPLT "->:<-"
#define MAGIC_PALACE_TAB_SIZE "-/-"
#define MAGIC_PALACE_TAB_TEXT "/"

tick g_tickDragStart;
namespace user
{


   tab::data::data() :
      m_pen(e_create),
      m_brushTextHover(e_create),
      m_brushTextSel(e_create),
      m_brushText(e_create),
      m_brushCloseHover(e_create),
      m_brushCloseSel(e_create),
      m_brushClose(e_create),
      m_penBorder(e_create),
      m_penBorderSel(e_create),
      m_penBorderHover(e_create)
   {

      m_bNoClient = false;
      m_brushTextHover->create_solid(ARGB(255, 0, 127, 255));
      m_brushTextSel->create_solid(ARGB(255, 0, 0, 0));
      m_brushText->create_solid(ARGB(163, 0, 0, 0));
      m_brushCloseHover->create_solid(ARGB(255, 255, 127, 0));
      m_brushCloseSel->create_solid(ARGB(255, 0, 0, 0));
      m_brushClose->create_solid(ARGB(163, 0, 0, 0));
      m_penBorderHover->create_solid(1.0, ARGB(255, 0, 0, 0));
      m_penBorderSel->create_solid(1.0, ARGB(255, 0, 0, 0));
      m_penBorder->create_solid(1.0, ARGB(163, 90, 90, 80));

      m_bEnableCloseAll = false;
      m_rectTabClient.set(0,0,0,0);

   }

   tab::data::~data()
   {
   }


   tab_pane * tab::data::get_pane_by_id(id id)
   {

      return m_panea.get_by_id(id);

   }


   ::count tab::data::get_visible_tab_count()
   {

      return m_panea.get_visible_count();

   }


   tab::tab()
   {

      m_bMouseDown = false;

      m_iTabScroll = 0;
      m_iTabScrollMax = 0;
      m_iTabSize = 0;
      m_edisplayParentFrameAutoHide = ::display_none;
      m_estate = state_initial;

      m_iRestoredTabCount = 0;

      m_spdata = __new(data);

      get_data()->m_iHeightAddUp = 0;
      get_data()->m_pcallback    = nullptr;
      get_data()->m_bCreated     = false;
      get_data()->m_iTabHeight   = 16;
      get_data()->m_iTabWidth    = 48;
      get_data()->m_iClickTab    = -1;

      m_bDisableSavingRestorableTabs           = true;

      m_bShowTabs                      = true;

      m_bNoTabs                        = false;

      m_bDrawTabAtBackground           = false;

      _001SetVertical(false);

   }


   tab::~tab()
   {

   }

   /*bool tab::add_tab(UINT uiIdTitle, i32 iId)
   {
      tab_pane tab_pane;
      tab_pane.m_uiId = uiIdTitle;
      tab_pane.m_istrTitleEx = L"";
      tab_pane.m_iId = iId == -1 ? get_data()->m_panea.get_size() : iId;
      if(!tab_pane.m_wstrTitle.load_string(uiIdTitle))
      {
         return false;
      }*/
   //   tab_pane.m_pcontainer = pcontainer;
   // tab_pane.m_type = nullptr;
   /* tab_pane.m_iImage = -1;

    get_data()->m_panea.add(tab_pane);
    return true;
   }*/


   e_element tab::get_default_element() const
   {

      return element_tab;

   }


   bool tab::set_title(::index iPane, const char * pcsz)

   {

      sync_lock sl(mutex());

      if (iPane < 0)
      {

         return false;

      }

      if (iPane >= get_data()->m_panea.get_size())
      {

         return false;

      }

      get_data()->m_panea[iPane]->set_title(pcsz);


      return true;

   }


   bool tab::SetTitleById(id id, const char * pcsz)

   {

      index iPane = id_pane(id);

      if (iPane < 0)
      {

         return false;

      }

      get_data()->m_panea[iPane]->set_title(pcsz);


      return true;

   }


   bool tab::set_tab(const char * pcsz, id id, bool bVisible)

   {

      return add_tab(pcsz, id, bVisible, true);


   }


   bool tab::add_tab(const char * pcsz, id id, bool bVisible, bool bPermanent, ::user::place_holder * pholder)

   {

      __pointer(::user::tab_pane) ppane = __new(::user::tab_pane(this));

      ppane->set_title(pcsz);

      ppane->m_bTabPaneVisible   = bVisible;
      ppane->m_bPermanent        = bPermanent;
      ppane->m_pplaceholder      = pholder;

      sync_lock sl(mutex());

      if (id.is_empty())
      {

         id = get_data()->m_panea.get_size();

      }

      ppane->m_id = id;

      //ppane->m_pimage->release();

      get_data()->m_panea.add(ppane);

      on_change_pane_count({ ppane });

      return true;

   }


   void tab::_001OnRemoveTab(class tab_pane * ptab)
   {


   }


   bool tab::remove_tab_by_id(id id)
   {

      bool bRestorableMatch = false;

      for(i32 i = 0; i < get_data()->m_panea.get_count(); i++)
      {

         if(get_data()->m_panea[i]->m_id == id)
         {

            if (!bRestorableMatch && matches_restorable_tab(get_data()->m_panea[i]->m_id, get_data()->m_panea[i]->m_pplaceholder))
            {

               bRestorableMatch = true;

            }

            remove_tab(i, false);

            break;

         }

      }

      if (bRestorableMatch)
      {

         on_change_pane_count({ nullptr });

      }

      on_change_pane_count();

      return true;

   }


   bool tab::set_image_tab(const char * pcszTitle, const char * pszImage, id id, bool bVisible)

   {

      return add_image_tab(pcszTitle, pszImage, id, bVisible, true);


   }


   bool tab::add_image_tab(const char * pcszTitle, const char * pszImage, id id, bool bVisible, bool bPermanent)

   {

      __pointer(::user::tab_pane) ppane = __new(::user::tab_pane(this));

      if (ppane == nullptr)
      {

         return false;

      }

      ppane->m_bTabPaneVisible = bVisible;
      ppane->m_bPermanent  = bPermanent;
      ppane->set_title(pcszTitle);


      sync_lock sl(mutex());

      if(id.is_empty())
         id = get_data()->m_panea.get_size();

      ppane->m_id          = id;
      ppane->m_pplaceholder = nullptr;
      ppane->m_pimage       = load_image(pszImage, false);

      get_data()->m_panea.add(ppane);

      on_change_pane_count({ ppane });

      return true;

   }


   void tab::remove_tab(::index iPane, bool bVisible)
   {

      sync_lock sl(mutex());

      if (iPane < 0 || iPane >= get_data()->m_panea.get_size())
      {

         return;

      }

      if(bVisible)
      {

         for(i32 i = 0; iPane >= 0 && i < get_data()->m_panea.get_count(); i++)
         {

            if(get_data()->m_panea[i]->m_bTabPaneVisible)
            {

               if(iPane <= 0)
               {

                  __pointer(::user::tab_pane) ppane = get_data()->m_panea[iPane];

                  get_data()->m_panea.remove_at(iPane);

                  _001OnRemoveTab(ppane);

                  on_change_pane_count();

                  break;

               }
               else
               {

                  iPane--;

               }

            }

         }

      }
      else
      {

         __pointer(::user::tab_pane) ppane = get_data()->m_panea[iPane];

         get_data()->m_panea.remove_at(iPane);

         _001OnRemoveTab(ppane);

         on_change_pane_count();

      }

   }


   void tab::remove_all_tabs()
   {

      sync_lock sl(mutex());

      get_data()->m_panea.remove_all();

      on_change_pane_count();

   }



   bool tab::defer_handle_auto_hide_tabs(bool bLayout)
   {

      if (!get_wnd()->is_ok())
      {

         return false;

      }

      //__pointer(::experience::frame_window) pchannel = GetTopLevelFrame();
      //
      //if (pchannel != nullptr && pchannel->m_bInitialFramePosition)
      //{
      //   return false;
      //}

      bool bNeedLayout = false;

      ::user::interaction * puiTopLevel = GetTopLevel();

      if (puiTopLevel != nullptr)
      {

         if (puiTopLevel->frame_is_transparent() && !GetTopLevelFrame()->window_is_full_screen())
         {

            if (m_bShowTabs)
            {

               m_bShowTabs = false;

               if (bLayout)
               {

                  set_need_layout();

               }

               bNeedLayout = true;

            }

            m_edisplayParentFrameAutoHide = GetTopLevelFrame()->display_state();

            return bNeedLayout;

         }

      }

      if(m_bNoTabs)
      {

         if(m_bShowTabs)
         {

            m_bShowTabs = false;

            if (bLayout)
            {

               set_need_layout();

            }

            bNeedLayout = true;

         }

         m_edisplayParentFrameAutoHide = GetTopLevelFrame()->display_state();

         return bNeedLayout;

      }

      if(m_bShowTabs)
      {

         if(GetTopLevelFrame()!= nullptr && GetTopLevelFrame()->window_is_full_screen())
         {

            ::rect rectTab(get_data()->m_rectTab);

            _001ClientToScreen(rectTab);

            auto pointCursor = Session.get_cursor_pos();

            bool bShowTabs = rectTab.contains(pointCursor);

            if(is_different(bShowTabs, m_bShowTabs))
            {

               m_bShowTabs = bShowTabs;

               if (bLayout)
               {

                  set_need_layout();

               }

               bNeedLayout = true;

            }

         }

      }
      else
      {

         auto pframe = GetParentFrame();

         if(::is_set(pframe) && !pframe->window_is_full_screen())
         {

            m_bShowTabs = true;

            if (bLayout)
            {

               set_need_layout();

            }

            bNeedLayout = true;

         }
         else if(::is_set(get_context_application()) && ::is_set(get_context_application()->get_context_session()))
         {

            ::rect rectWindow;
            
            get_window_rect(rectWindow);

            bool bShowTabs;

            auto pointCursor = Session.get_cursor_pos();

            if(get_data()->m_bVertical)
            {

               bShowTabs = pointCursor.x <= rectWindow.left;

            }
            else
            {
               bShowTabs = pointCursor.y <= rectWindow.top;
            }

            m_bShowTabs = bShowTabs;

            if(bShowTabs)
            {

               if (bLayout)
               {

                  set_need_layout();

               }

               bNeedLayout = true;

            }

         }

      }

      if (GetParentFrame() != nullptr && (bNeedLayout || !GetParentFrame()->is_this_screen_visible()))
      {

         m_edisplayParentFrameAutoHide = GetParentFrame()->display_state();

      }

      return bNeedLayout;

   }


   void tab::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      defer_handle_auto_hide_tabs();

      if (m_bNoTabs || !m_bShowTabs)
      {

         return;

      }

      if (GetTopLevel()->frame_is_transparent())
      {

         return;

      }

      point pointViewportOffset = pgraphics->GetViewportOrg();
      
      ::rect rClip;
      
      pgraphics->GetClipBox(rClip);

      __pointer(::base::style) pstyle = get_style(pgraphics);

      if(pstyle)
      {

         if (pstyle->_001TabOnDrawSchema01(pgraphics, this))
         {

            return;

         }

      }


      if(pstyle == nullptr)
      {

         _001OnDrawStandard(pgraphics);

         return;

      }


      if (!pstyle->_001TabOnDrawSchema01(pgraphics, this))
      {

         _001OnDrawSchema01(pgraphics);

      }

   }


   void tab::_001OnDrawSchema01(::draw2d::graphics_pointer & pgraphics)
   {

      ::rect rect;
      ::rect rectBorder;
      ::rect rectText;
      ::rect rectClient;
      ::rect rectIcon;
      ::rect rectClose;

      get_data()->m_pen->create_solid(1, RGB(32, 32, 32));

      pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias_grid_fit);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      auto pstyle = get_style(pgraphics);

      ::index iTab = -1;

      ::draw2d::brush_pointer brushText;

      for (i32 iPane = 0; iPane < get_data()->m_panea.get_size(); iPane++)
      {

         ::user::tab_pane & pane = get_data()->m_panea(iPane);

         if (!pane.m_bTabPaneVisible)
            continue;

         iTab++;

         if (!get_element_rect(iTab, rect, ::user::element_tab))
            continue;

         if (!get_element_rect(iTab, rectBorder, ::user::element_border))
            continue;

         if (!get_element_rect(iTab, rectClient, ::user::element_client))
            continue;

         if (get_data()->m_bVertical)
         {

            if (get_element_rect(iTab, rectIcon, ::user::element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

               pane.m_pimage->bitmap_blend(pgraphics, rectIcon);

            }

            ::draw2d::path_pointer path(e_create);

            if (true)
            {

               if (get_data()->m_idaSel.contains(pane.m_id))
               {

                  //path->start_figure();

                  path->add_line(rectBorder.right, rectBorder.bottom, rectBorder.left + 1, rectBorder.bottom);
                  //path->add_line(rectClient.right, rectBorder.top);
                  path->add_line(rectBorder.left, rectBorder.top - (rectBorder.left - rectClient.left));
                  path->add_line(rectClient.left, rectBorder.top);
                  path->add_line(rectBorder.right, rectBorder.top);

                  path->close_figure();

                  pane.m_brushFillSel->CreateLinearGradientBrush(rectBorder.top_left(), rectBorder.bottom_left(), ARGB(230, 235, 235, 230), ARGB(250, 255, 255, 250));

                  pgraphics->set(pane.m_brushFillSel);

                  pgraphics->fill_path(path);

                  pgraphics->set(get_data()->m_penBorderSel);

                  pgraphics->draw_path(path);

                  pgraphics->set(get_font(pstyle));

                  brushText = get_data()->m_brushTextSel;

               }
               else
               {

                  //path->start_figure();

                  path->add_line(rectBorder.right, rectBorder.bottom, rectBorder.left + 1, rectBorder.bottom);
                  path->add_line(rectBorder.left, rectBorder.top - (rectBorder.left - rectClient.left));
                  path->add_line(rectText.left, rectBorder.top);
                  path->add_line(rectBorder.right, rectBorder.top);
                  path->add_line(rectBorder.right, rectBorder.bottom);

                  path->close_figure();

                  if (m_itemHover == iTab && m_itemHover != ::user::element_close_tab_button && !m_itemHover.in_range(::user::element_split, 100))
                  {

                     pane.m_brushFillHover->CreateLinearGradientBrush(rectBorder.top_left(), rectBorder.bottom_left(), ARGB(230, 215, 215, 210), ARGB(250, 235, 235, 230));

                     pgraphics->set(pane.m_brushFillHover);

                     pgraphics->fill_path(path);

                     pgraphics->set(get_data()->m_penBorderHover);

                     pgraphics->draw_path(path);

                     pgraphics->set(get_font(pstyle, e_state_hover));

                     brushText = get_data()->m_brushTextHover;

                  }
                  else
                  {

                     pane.m_brushFill->CreateLinearGradientBrush(rectBorder.top_left(), rectBorder.bottom_left(), ARGB(230, 175, 175, 170), ARGB(250, 195, 195, 190));

                     pgraphics->set(pane.m_brushFill);

                     pgraphics->fill_path(path);

                     pgraphics->set(get_data()->m_penBorder);

                     pgraphics->draw_path(path);

                     pgraphics->set(get_font(pstyle));

                     brushText = get_data()->m_brushText;

                  }

               }

            }

         }
         else
         {

            if (get_element_rect(iTab, rectIcon, ::user::element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

               pane.m_pimage->bitmap_blend(pgraphics, rectIcon);

            }

            if (true)
            {

               ::draw2d::path_pointer path(e_create);

               if (get_data()->m_idaSel.contains(pane.m_id))
               {

                  path->add_line(rectBorder.left, rectClient.bottom, rectBorder.left, rectBorder.top);

                  path->add_line(rectClient.right, rectBorder.top);

                  path->add_line(rectBorder.right, rectBorder.top + (rectBorder.right - rectClient.right));

                  path->add_line(rectBorder.right - 1, rectClient.bottom);

                  path->close_figure();

                  pane.m_brushFillSel->CreateLinearGradientBrush(rectBorder.top_left(), rectBorder.bottom_left(), ARGB(230, 235, 235, 230), ARGB(250, 255, 255, 250));

                  pgraphics->set(pane.m_brushFillSel);

                  pgraphics->fill_path(path);

                  get_data()->m_penBorderSel->create_solid(1.0, ARGB(255, 0, 0, 0));

                  pgraphics->set(get_data()->m_penBorderSel);

                  pgraphics->draw_path(path);

                  pgraphics->set(get_font(pstyle));

                  brushText = get_data()->m_brushTextSel;

               }
               else
               {

                  //path->begin_figure(true, ::draw2d::fill_mode_winding);

                  path->add_line(rectBorder.left, rectClient.bottom, rectBorder.left, rectBorder.top);

                  path->add_line(rectClient.right, rectBorder.top);

                  path->add_line(rectBorder.right, rectBorder.top + (rectBorder.right - rectClient.right));

                  path->add_line(rectBorder.right - 1, rectClient.bottom);

                  path->close_figure();

                  if (m_itemHover == iTab  && m_itemHover != ::user::element_close_tab_button && !m_itemHover.in_range(::user::element_split, 100))
                  {

                     pane.m_brushFillHover->CreateLinearGradientBrush(rectBorder.top_left(), rectBorder.bottom_left(), ARGB(230, 215, 215, 210), ARGB(250, 235, 235, 230));

                     pgraphics->set(pane.m_brushFillHover);

                     pgraphics->fill_path(path);

                     pgraphics->set(get_data()->m_penBorderHover);

                     pgraphics->draw_path(path);

                     pgraphics->set(get_font(pstyle, e_state_hover));

                     brushText = get_data()->m_brushTextHover;

                  }
                  else
                  {

                     pane.m_brushFill->CreateLinearGradientBrush(rectBorder.top_left(), rectBorder.bottom_left(), ARGB(230, 175, 175, 170), ARGB(250, 195, 195, 190));

                     pgraphics->set(pane.m_brushFill);

                     pgraphics->fill_path(path);

                     pgraphics->set(get_data()->m_penBorder);

                     pgraphics->draw_path(path);

                     pgraphics->set(get_font(pstyle));

                     brushText = get_data()->m_brushTextSel;

                  }

               }

            }

         }

         if (true)
         {

            __pointer(::base::style) pbasestyle = pstyle;

            if (pbasestyle && get_element_rect(iTab, rectText, ::user::element_text))
            {

               pbasestyle->_001OnTabPaneDrawTitle(pane, this, pgraphics, rectText, brushText);

            }

         }

         if (true)
         {

            if (get_element_rect(iTab, rectClose, ::user::element_close_tab_button))
            {

               pgraphics->set(get_font(pstyle, element_close_tab_button));

               if (m_itemHover == iTab && m_itemHover == ::user::element_close_tab_button)
               {

                  brushText = get_data()->m_brushCloseHover;

               }
               else
               {

                  brushText = get_data()->m_brushClose;

               }

               pgraphics->set(brushText);

               pgraphics->draw_text("x", rectClose, DT_CENTER | DT_VCENTER);

            }

         }

      }

   }


   void tab::_001OnDrawStandard(::draw2d::graphics_pointer & pgraphics)
   {

      ::rect rect;
      ::rect rectBorder;
      ::rect rectText;
      ::rect rectClient;
      ::rect rectIcon;
      ::rect rectClose;

      auto pstyle = get_style(pgraphics);

      get_data()->m_pen->create_solid(1,RGB(32,32,32));

      pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias_grid_fit);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      pgraphics->fill_rect(get_data()->m_rectTab, ARGB(0xc0, 250, 255, 255));

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_set);

      ::index iVisiblePane = 0;

      ::draw2d::brush_pointer brushText(e_create);

      for(i32 iPane = 0; iPane < get_data()->m_panea.get_size(); iPane++)
      {

         ::user::tab_pane & tab_pane = get_data()->m_panea(iPane);

         if(!tab_pane.m_bTabPaneVisible)
            continue;



         if(!get_element_rect(iVisiblePane, rect, element_tab))
            continue;

         if (!get_element_rect(iVisiblePane, rectBorder, element_border))
         {

            continue;

         }

         if (!get_element_rect(iVisiblePane, rectClient, element_client))
         {

            continue;

         }

         if(get_data()->m_bVertical)
         {

            if(get_element_rect(iVisiblePane, rectIcon, element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

               tab_pane.m_pimage->bitmap_blend(pgraphics, rectIcon);

            }

            if(get_data()->m_idaSel.contains(iPane))
            {

               ::draw2d::pen_pointer pen(e_create);

               pen->create_solid(1.0, ARGB(255, 0, 0, 0));

               pgraphics->set(pen);

               pgraphics->move_to(rectBorder.right, rectBorder.bottom);
               pgraphics->line_to(rectBorder.left + 1, rectBorder.bottom);
               pgraphics->line_to(rectBorder.left, rectBorder.top - (rectBorder.left - rectClient.left));
               pgraphics->line_to(rectClient.left, rectBorder.top);
               pgraphics->line_to(rectBorder.right, rectBorder.top);

               auto pstyle = get_style(pgraphics);

               pgraphics->set(get_font(pstyle, e_state_selected));

               brushText = get_data()->m_brushTextSel;

            }
            else
            {

               ::draw2d::pen_pointer pen(e_create);

               pen->create_solid(1.0, ARGB(255, 0, 0, 0));

               pgraphics->set(pen);

               pgraphics->move_to(rectBorder.right, rectBorder.bottom);
               pgraphics->line_to(rectBorder.left + 1, rectBorder.bottom);
               pgraphics->line_to(rectBorder.left, rectBorder.top - (rectBorder.left - rectClient.left));
               pgraphics->line_to(rectText.left, rectBorder.top);
               pgraphics->line_to(rectBorder.right, rectBorder.top);
               pgraphics->line_to(rectBorder.right, rectBorder.bottom);

               if(m_itemHover == iVisiblePane && m_itemHover != element_close_tab_button)
               {

                  auto pstyle = get_style(pgraphics);

                  pgraphics->set(get_font(pstyle, e_state_hover));

                  brushText = get_data()->m_brushClose;

               }
               else
               {

                  auto pstyle = get_style(pgraphics);

                  pgraphics->set(get_font(pstyle, e_state_hover));

                  brushText = get_data()->m_brushText;

               }

            }

         }
         else
         {

            if(get_element_rect(iVisiblePane, rectIcon, element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

               tab_pane.m_pimage->bitmap_blend(pgraphics, rectIcon);

            }

            if(get_data()->m_idaSel.contains(tab_pane.m_id))
            {

               ::draw2d::pen_pointer pen(e_create);

               pen->create_solid(1.0, ARGB(255, 0, 0, 0));

               pgraphics->set(pen);

               pgraphics->move_to(rectBorder.left, rectClient.bottom);
               pgraphics->line_to(rectBorder.left, rectBorder.top);
               pgraphics->line_to(rectClient.right, rectBorder.top);
               pgraphics->line_to(rectBorder.right, rectBorder.top + (rectBorder.right - rectClient.right));
               pgraphics->line_to(rectBorder.right - 1, rectClient.bottom);

               auto pstyle = get_style(pgraphics);

               pgraphics->set(get_font(pstyle, e_state_selected));

               brushText->create_solid(ARGB(255, 0, 0, 0));

            }
            else
            {

               ::draw2d::pen_pointer pen(e_create);

               pen->create_solid(1.0, ARGB(255, 0, 0, 0));

               pgraphics->set(pen);

               pgraphics->move_to(rectBorder.left, rectClient.bottom);
               pgraphics->line_to(rectBorder.left, rectBorder.top);
               pgraphics->line_to(rectClient.right, rectBorder.top);
               pgraphics->line_to(rectBorder.right, rectBorder.top + (rectBorder.right - rectClient.right));
               pgraphics->line_to(rectBorder.right - 1, rectClient.bottom);
               pgraphics->line_to(rectBorder.left, rectClient.bottom);

               if (m_itemHover == iVisiblePane && m_itemHover != element_close_tab_button)
               {

                  pgraphics->set(get_font(pstyle, e_state_hover));

                  brushText->create_solid(ARGB(255, 0, 127, 255));

               }
               else
               {

                  pgraphics->set(get_font(pstyle));

                  brushText = get_data()->m_brushText;

               }

            }

         }

         if (get_element_rect(iVisiblePane, rectText, element_text))
         {

            pgraphics->set(brushText);

            pgraphics->_DrawText(tab_pane.get_title(), tab_pane.get_title().get_length(), rectText, DT_LEFT | DT_BOTTOM);

         }

         if (get_element_rect(iVisiblePane, rectClose, element_close_tab_button))
         {

            pgraphics->set(get_font(pstyle, element_close_tab_button));

            if (m_itemHover == iVisiblePane  && m_itemHover == element_close_tab_button)
            {

               brushText = get_data()->m_brushCloseSel;

               brushText->create_solid(ARGB(0xff, 255, 127, 0));

            }
            else
            {

               brushText->create_solid(ARGB(0xff, 0, 0, 0));

            }

            pgraphics->set(brushText);

            pgraphics->draw_text("x", rectClose, DT_CENTER | DT_VCENTER);

         }

         iVisiblePane++;

      }

   }


   void tab::get_title(int iPane, string_array & stra)
   {

      ::user::tab_pane & tab_pane = get_data()->m_panea(iPane);

      stra = tab_pane.m_straTitle;

   }


   void tab::GetTabClientRect(RECT * prect)

   {

      *prect = get_data()->m_rectTabClient;


   }


   void tab::GetTabClientRect(RECT64 * prect)

   {

      ::rect rectClient;
      get_client_rect(rectClient);
      rect64 rect64(rectClient);
      *prect = rect64;


   }


   void tab::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectClient = get_client_rect();

      if(!rectClient)
      {

         return;

      }

      __pointer(::base::style) pstyle = get_style(pgraphics);

      if(pstyle)
      {

         if (pstyle->_001OnTabLayout(pgraphics, this))
         {

            return;

         }

      }

      if (!get_data()->m_bCreated)
      {

         return;

      }

      if (get_data()->m_bVertical)
      {

         get_data()->m_rectMargin.set(2, 3, 1, 0);

         get_data()->m_rectBorder.set(11, 1, 6, 0);

         get_data()->m_rectTextMargin.set(3, 0, 1, 0);

         get_data()->m_iTabHeight += get_data()->m_rectBorder.top + get_data()->m_rectBorder.bottom +
                                     get_data()->m_rectMargin.top + get_data()->m_rectMargin.bottom;

         get_data()->m_iTabWidth += get_data()->m_rectBorder.left + get_data()->m_rectBorder.right +
                                    get_data()->m_rectMargin.left + get_data()->m_rectMargin.right;

      }
      else
      {

         get_data()->m_rectMargin.set(3, 2, 0, 1);

         get_data()->m_rectBorder.set(0, 1, 11, 6);

         get_data()->m_rectTextMargin.set(3, 0, 1, 0);

         get_data()->m_iTabHeight += get_data()->m_rectBorder.top + get_data()->m_rectBorder.bottom +
                                     get_data()->m_rectMargin.top + get_data()->m_rectMargin.bottom;

         get_data()->m_iTabWidth += get_data()->m_rectBorder.left + get_data()->m_rectBorder.right +
                                    get_data()->m_rectMargin.left + get_data()->m_rectMargin.right;

      }

      defer_handle_auto_hide_tabs(false);

      pgraphics->set(get_font(pstyle, element_close_tab_button));

      m_dcextension.GetTextExtent(pgraphics,MAGIC_PALACE_TAB_SIZE,get_data()->m_sizeSep);

      if(get_data()->m_bVertical)
      {

         i32 iTabWidth = 16;

         i32 iTabHeight = 8;

         i32 cx;

         i32 cy;

         for(i32 iPane = 0; iPane < get_data()->m_panea.get_size(); iPane++)
         {

            ::user::tab_pane & tab_pane = get_data()->m_panea(iPane);

            if (!tab_pane.m_bTabPaneVisible)
            {

               continue;

            }

            string str = tab_pane.get_title();

            tab_pane.do_split_layout(m_dcextension, pgraphics);

            ::size size;

            m_dcextension.GetTextExtent(pgraphics, str, size);

            if(tab_pane.m_pimage->is_set())
            {

               size.cx += tab_pane.m_pimage->width()+ 2;

               size.cy = MAX(size.cy, tab_pane.m_pimage->height());

            }

            cx = size.cx + 2;

            if(!tab_pane.m_bPermanent)
            {

               cx += 2 + 16 + 2;

            }

            if(cx > iTabWidth)
            {

               iTabWidth = cx;

            }

            cy = size.cy + 2;

            if(cy > iTabHeight)
            {

               iTabHeight = cy;

            }

         }

         cy = 2 + 16 + 2;

         if(cy > iTabHeight)
         {

            iTabHeight = cy;

         }

         iTabWidth += get_data()->m_rectBorder.left + get_data()->m_rectBorder.right +
                      get_data()->m_rectMargin.left + get_data()->m_rectMargin.right +
                      get_data()->m_rectTextMargin.left + get_data()->m_rectTextMargin.right;

         get_data()->m_iTabWidth = iTabWidth;

         iTabHeight += get_data()->m_rectBorder.top + get_data()->m_rectBorder.bottom +
                       get_data()->m_rectMargin.top + get_data()->m_rectMargin.bottom +
                       get_data()->m_rectTextMargin.top + get_data()->m_rectTextMargin.bottom;

         get_data()->m_iTabHeight = iTabHeight;

         //::rect rectClient;

         //get_client_rect(rectClient);

         get_data()->m_rectTab.left       = rectClient.left;
         get_data()->m_rectTab.top        = rectClient.top;
         get_data()->m_rectTab.right      = get_data()->m_rectTab.left + get_data()->m_iTabWidth;
         get_data()->m_rectTab.bottom     = rectClient.bottom;

         get_data()->m_rectTabClient.left       = m_bShowTabs ? get_data()->m_rectTab.right : rectClient.left;
         get_data()->m_rectTabClient.top        = get_data()->m_rectTab.top;
         get_data()->m_rectTabClient.right      = rectClient.right;
         get_data()->m_rectTabClient.bottom     = get_data()->m_rectTab.bottom;

      }
      else
      {

         i32 iTabHeight = 16;

         i32 cy;

         pgraphics->set(get_font(pstyle, e_state_selected));

//         ::rect rectClient;

//         get_client_rect(rectClient);

         int x = rectClient.left;

         i32 ixAdd;

         for(i32 iPane = 0; iPane < get_data()->m_panea.get_size(); iPane++)
         {

            ::user::tab_pane & tab_pane = get_data()->m_panea(iPane);

            if (!tab_pane.m_bTabPaneVisible)
            {

               return;

            }

            string str = tab_pane.get_title();

            tab_pane.do_split_layout(m_dcextension,pgraphics);

            ::size size;

            m_dcextension.GetTextExtent(pgraphics, str, size);

            if(tab_pane.m_pimage->is_ok())
            {

               size.cy = MAX(size.cy, tab_pane.m_pimage->size().cy);

            }

            cy = size.cy + 2;

            if(cy > iTabHeight)
            {

               iTabHeight = cy;

            }

            tab_pane.m_point.x = x;

            tab_pane.m_point.y = rectClient.top;

            ixAdd = 5;

            if (tab_pane.m_pimage->is_set())
            {

               ixAdd += tab_pane.m_pimage->width() + 2;

            }

            if (!tab_pane.m_bPermanent)
            {

               ixAdd += 2 + 16 + 2;

            }

            tab_pane.m_size.cx = size.cx + ixAdd
                                 + get_data()->m_rectBorder.left + get_data()->m_rectBorder.right
                                 + get_data()->m_rectMargin.left + get_data()->m_rectMargin.right
                                 + get_data()->m_rectTextMargin.left + get_data()->m_rectTextMargin.right;

            x += tab_pane.m_size.cx;
         }

         // close tab button
         cy = 2 + 16 + 2;
         if(cy > iTabHeight)
         {
            iTabHeight = cy;
         }

         iTabHeight += get_data()->m_rectBorder.top + get_data()->m_rectBorder.bottom +
                       get_data()->m_rectMargin.top + get_data()->m_rectMargin.bottom + get_data()->m_iHeightAddUp;

         get_data()->m_iTabHeight = iTabHeight;

         for (i32 iPane = 0; iPane < get_data()->m_panea.get_size(); iPane++)
         {

            ::user::tab_pane & tab_pane = get_data()->m_panea(iPane);

            tab_pane.m_size.cy = iTabHeight;

         }




         get_data()->m_rectTab.left       = rectClient.left;
         get_data()->m_rectTab.top        = rectClient.top;
         get_data()->m_rectTab.right      = rectClient.right;
         get_data()->m_rectTab.bottom     = get_data()->m_rectTab.top + get_data()->m_iTabHeight;

         ::rect & rectTabClient = get_data()->m_rectTabClient;

         bool bTabbedClient = m_bShowTabs;

         rectTabClient.left       = get_data()->m_rectTab.left;
         rectTabClient.top        = bTabbedClient ? get_data()->m_rectTab.bottom : rectClient.top;
         rectTabClient.right      = get_data()->m_rectTab.right;
         rectTabClient.bottom     = rectClient.bottom;

         //TRACE0("rectTabClient");
      }

      {

//               DWORD dwTime2 = ::get_tick();

         //TRACE("message_handler call time0= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
         //TRACE("usertab::on_layout call time2= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
      }


      for(i32 iPane = 0; iPane < get_data()->m_panea.get_size(); iPane++)
      {

         if(iPane != _001GetSel())
         {

            layout_pane(iPane);

         }

      }

      layout_pane(_001GetSel(), is_window_visible());

      if(m_spdata->m_bVertical)
      {

         m_iTabSize = (int) m_spdata->m_panea.get_count() * m_spdata->m_iTabHeight;

         m_iTabScrollMax = m_iTabSize - rectClient.height();

      }
      else
      {

         m_iTabSize = m_spdata->m_panea.last()->m_point.x +
         m_spdata->m_panea.last()->m_size.cx;

         m_iTabScrollMax = m_iTabSize - rectClient.width();

      }


   }


   void tab::layout_pane(index iPane, bool bDisplay)
   {

      auto ppane = get_pane(iPane);

      if (::is_null(ppane))
      {

         return;

      }

      auto ppaneSel = get_pane(_001GetSel());

      if (::is_null(ppane))
      {

         return;

      }

      auto pholder = ppane->m_pplaceholder;

      if(pholder.is_null())
      {

         return;

      }

      ::rect rectChild;

      GetTabClientRect(rectChild);

      ::rect rectWindow;
      
      pholder->get_window_rect(rectWindow);

      _001ScreenToClient(rectWindow);

      if(bDisplay && iPane == _001GetSel())
      {

         pholder->order(zorder_top);

      }

      pholder->place(rectChild);

      if (bDisplay)
      {

         pholder->display(::display_normal);

      }
      else if(::is_set(ppaneSel) && ppaneSel->m_eflag & flag_hide_all_others_on_show)
      {

         pholder->hide();

      }

   }


   void tab::_001OnLButtonDown(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);
      
      pmouse->previous();

      m_itemClick = hit_test(pmouse);

      get_data()->m_bDrag = false;

      get_data()->m_iClickTab = -1;

      if(m_itemClick.m_eelement == element_tab_near_scroll)
      {

         if(m_iTabScroll > 0)
         {

            m_iTabScroll--;

            set_need_redraw();

            post_redraw();

            pmouse->m_bRet = true;

            m_bMouseDown = true;

            SetCapture();

            return;

         }

      }
      else if(m_itemClick.m_eelement == element_tab_far_scroll
         )
      {

         if(m_iTabScroll < m_iTabScrollMax)
         {

            m_iTabScroll++;

            set_need_redraw();

            post_redraw();

            pmouse->m_bRet = true;

            m_bMouseDown = true;

            SetCapture();

            return;

         }

      }

      if(m_itemClick.m_iItem >= 0)
      {

         index iSel = _001GetSel();

         if(m_itemClick == element_close_tab_button)
         {

            get_data()->m_iClickTab = m_itemClick.m_iItem;

            pmouse->m_bRet = true;

            pmouse->m_lresult = 1;

            m_estate = state_close_button_down;

         }
         else if(m_itemClick.m_iItem != iSel)
         {

            get_data()->m_iClickTab = m_itemClick.m_iItem;

            SetCapture();

            //SetTimer(timer_drag_start, 300, nullptr);

            g_tickDragStart.Now();

            pmouse->m_bRet = true;

            pmouse->m_lresult = 1;

            m_estate = state_other_tab_button_down;

         }

      }

   }


   void tab::_001OnLButtonUp(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      if(m_bMouseDown)
      {

         m_bMouseDown = false;

         ReleaseCapture();

      }

      auto item = hit_test(pmouse);

      index iClickTab = get_data()->m_iClickTab;

      if (m_estate == state_other_tab_button_down)
      {

         // drag operation was about to start (but ended prematurely)

         ReleaseCapture();

         KillTimer(timer_drag_start);

      }

      if(item.m_iItem >= 0 && iClickTab == item.m_iItem && m_itemClick == item)
      {

         if (item == element_close_tab_button)
         {

            _001OnTabClose(item.m_iItem);

         }
         else
         {

            _001OnTabClick(item.m_iItem);

         }

         set_need_redraw();

         post_redraw();

         pmouse->m_bRet = true;

         pmouse->m_lresult = 1;

      }

      get_data()->m_iClickTab = -1;

      get_data()->m_bDrag = false;

   }


   void tab::_001OnMouseMove(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      if(m_bMouseDown)
      {

         if(m_itemClick.m_eelement == element_tab_far_scroll)
         {

            if(m_iTabScroll < m_iTabScrollMax)
            {

               m_iTabScroll++;

               set_need_redraw();

               post_redraw();

               pmouse->m_bRet = true;

               return;

            }

         }
         else if(m_itemClick.m_eelement == element_tab_near_scroll)
         {

            if(m_iTabScroll > 0)
            {

               m_iTabScroll--;

               set_need_redraw();

               post_redraw();

               pmouse->m_bRet = true;

               return;

            }

         }

      }

      if(get_data()->m_iClickTab >= 0)
      {

         if(get_data()->m_pcallback != nullptr)
         {

            get_data()->m_pcallback->_001DropTargetWindowRelay(this);

         }

      }

   }


   void tab::_001OnMouseLeave(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);
      //SCAST_PTR(::message::base, pbase, pmessage);

   }


   bool tab::has_tab_scrolling() const
   {

      return m_iTabScrollMax > 0;

   }


   bool tab::get_element_rect(::index iTab, RECT * prect, e_element eelement)
   {

      point ptOffset(0,0);

      if(has_tab_scrolling())
      {

         float fDensity = 1.0f;

         if(eelement == element_tab_near_scroll)
         {

            if(get_data()->m_bVertical)
            {

               ::rect rect = get_data()->m_rectTab;

               prect->left = rect.left;

               prect->top = rect.top;

               prect->right = rect.right;


#ifdef ANDROID

               fDensity = System.oslocal().m_fDensity;

#endif

               prect->bottom = rect.top + (LONG) (8.0f * fDensity);

            }
            else
            {

               ::rect rect = get_data()->m_rectTab;

               prect->left = rect.left;

               prect->top = rect.top;

#ifdef ANDROID

               fDensity = System.oslocal().m_fDensity;

#endif

               prect->right = rect.left + (LONG)(8.0f * fDensity);

               prect->bottom = rect.bottom;

            }

            return true;

         }
         else if(eelement == element_tab_far_scroll)
         {

            if(get_data()->m_bVertical)
            {

               ::rect rect = get_data()->m_rectTab;

               prect->left = rect.left;

#ifdef ANDROID

               fDensity = System.oslocal().m_fDensity;

#endif

               prect->top = rect.bottom - (LONG)(8.0f* fDensity);

               prect->right = rect.right;

               prect->bottom = rect.bottom;

            }
            else
            {

               ::rect rect = get_data()->m_rectTab;

#ifdef ANDROID

               fDensity = System.oslocal().m_fDensity;

#endif

               prect->left = rect.right - (LONG) (8.0f * fDensity);

               prect->top = rect.top;

               prect->right = rect.right;

               prect->bottom = rect.bottom;

            }

            return true;

         }

         if(get_data()->m_bVertical)
         {

            ptOffset.y += 4;

            ptOffset.y -= m_iTabScroll;

         }
         else
         {

            ptOffset.x += 4;

            ptOffset.x -= m_iTabScroll;

         }




      }

      if (iTab < 0)
      {

         return false;

      }

      index iPane = tab_pane(iTab);

      if(eelement == element_border)
      {

         if (!get_element_rect(iTab, prect, element_tab))

         {

            return false;

         }

         ::rect_deflate(prect, &get_data()->m_rectMargin);

         //::OffsetRect(prect, ptOffset.x, ptOffset.y);

         return true;

      }

      if(eelement == element_client)
      {

         if (!get_element_rect(iTab, prect, element_border))
         {

            return false;

         }

         ::rect_deflate(prect, &get_data()->m_rectBorder);

         //::OffsetRect(prect, ptOffset.x, ptOffset.y);

         return true;

      }

      if(eelement == element_icon)
      {

         if (::not_ok(get_data()->m_panea[iPane]->m_pimage))
         {

            return false;

         }

         if (!get_element_rect(iTab, prect, element_client))
         {

            return false;

         }

         prect->right = prect->left + get_data()->m_panea[iPane]->m_pimage->width();

         prect->bottom = prect->top + get_data()->m_panea[iPane]->m_pimage->height();

         //::OffsetRect(prect, ptOffset.x, ptOffset.y);

         return true;

      }
      else if(eelement == element_text)
      {

         if (!get_element_rect(iTab, prect, element_client))
         {

            return false;

         }

         if(::is_ok(get_data()->m_panea[iPane]->m_pimage))
         {

            prect->left += get_data()->m_panea[iPane]->m_pimage->width() + 2;


         }

         if(!get_data()->m_panea[iPane]->m_bPermanent)
         {

            prect->right -= 2 + 16 + 2;

         }

         ::rect_deflate(prect, &get_data()->m_rectTextMargin);

         //::OffsetRect(prect, ptOffset.x, ptOffset.y);

         return true;

      }
      else if(eelement == element_close_tab_button)
      {

         if (iPane < 0)
         {

            return false;

         }

         if (get_data()->m_panea[iPane]->m_bPermanent)
         {

            return false;

         }

         if (get_data()->get_visible_tab_count() <= 1 && !get_data()->m_bEnableCloseAll)
         {

            return false;

         }

         if (!get_element_rect(iTab, prect, element_client))
         {

            return false;

         }

         prect->right  = prect->right;


         prect->left   = prect->right - 20;


         prect->top    = prect->bottom - 20;


         //::OffsetRect(prect, ptOffset.x, ptOffset.y);


         return true;

      }

      if (eelement != element_tab)
      {

         return false;

      }

      if(get_data()->m_bVertical)
      {

         ::rect rect = get_data()->m_rectTab;
         rect.bottom = rect.top;

         prect->left   = rect.left;

         prect->top    = (LONG) (rect.top +  iTab * get_data()->m_iTabHeight);

         prect->right  = rect.right;

         prect->bottom = prect->top + get_data()->m_iTabHeight;

      }
      else
      {

         ::user::tab_pane & tab_pane = get_data()->m_panea(iTab);
         prect->left = tab_pane.m_point.x;

         prect->top = tab_pane.m_point.y;

         prect->right = tab_pane.m_point.x + tab_pane.m_size.cx;

         prect->bottom = tab_pane.m_point.y + tab_pane.m_size.cy;

      }

      ::OffsetRect(prect, ptOffset.x, ptOffset.y);

      return true;

   }


   ::count tab::get_pane_count()
   {

      return get_data()->m_panea.get_size();

   }


   ::count tab::get_tab_count()
   {

      return get_data()->m_panea.pred_get_count([](auto & pane) {return pane->m_bTabPaneVisible; });

   }


   index tab::find_child_pane(::user::interaction * pinteraction)
   {

      index iPane = get_data()->m_panea.pred_find_first([=](auto & pane)
      {

         return pane->m_pplaceholder && pane->m_pplaceholder->is_ascendant_of(pinteraction, true);

      });

      return iPane;

   }


   void tab::defer_remove_child_pane(::user::interaction * pinteraction)
   {

      sync_lock sl(mutex());

      index iPane = find_child_pane(pinteraction);

      if (iPane >= 0)
      {

         remove_tab(iPane, false);

      }

   }


   void tab::on_remove_child(::user::interaction * pinteraction)
   {

      defer_remove_child_pane(pinteraction);

   }


   void tab::on_remove_place_holder_child(::user::interaction * pinteraction)
   {

      defer_remove_child_pane(pinteraction);

   }


   void tab::on_hide_child(::user::interaction * pinteraction)
   {

      //__pointer(::user::interaction) pupdown = pinteraction;

      //if (pupdown.is_set()
      //      && pupdown->m_eupdown != updown_normal_frame
      //      && pupdown->m_eupdown != updown_none)
      //{

      //   defer_remove_child_pane(pinteraction);

      //}

   }


   void tab::on_hide_place_holder_child(::user::interaction * pinteraction)
   {

      //__pointer(::user::interaction) pupdown = pinteraction;

      //if (pupdown.is_set()
      //      && pupdown->m_eupdown != updown_normal_frame
      //      && pupdown->m_eupdown != updown_none)
      //{

      //   defer_remove_child_pane(pinteraction);

      //}

   }


   void tab::on_hit_test(::user::item & item)
   {

      sync_lock sl(mutex());

      ::rect rectScroll;

      bool bScroll = has_tab_scrolling();

      if(bScroll)
      {

         if(get_element_rect(-1,rectScroll, ::user::element_tab_near_scroll))
         {

            if(rectScroll.contains(item.m_pointHitTest))
            {

               item = { ::user::element_tab_near_scroll, -1 };

               return;

            }

         }

         if(get_element_rect(-1,rectScroll, ::user::element_tab_far_scroll))
         {

            if(rectScroll.contains(item.m_pointHitTest))
            {

               item = { ::user::element_tab_far_scroll, -1 };

               return;

            }

         }

      }


      ::rect rect;

      for(i32 iPane = 0; iPane < get_data()->m_panea.get_size(); iPane++)
      {

         ::user::tab_pane & pane = *get_data()->m_panea[iPane];

         if(pane.m_straTitle.get_size() > 1)
         {

            ::rect rectText;

            if(get_element_rect(iPane, rectText, element_text) && rectText.contains(item.m_pointHitTest))
            {

               for(int iTitle = 0; iTitle < pane.m_straTitle.get_size(); iTitle++)
               {

                  rectText.left += pane.m_sizeaText[iTitle].cx;

                  rectText.right = rectText.left + get_data()->m_sizeSep.cx;

                  if(rectText.contains(item.m_pointHitTest))
                  {

                     item = { (e_element)((int)element_split + iTitle), iPane };

                     return;

                  }

                  rectText.left += get_data()->m_sizeSep.cx;

               }

            }

         }

         if(get_element_rect(iPane, rect, element_close_tab_button) && rect.contains(item.m_pointHitTest))
         {

            item = { element_close_tab_button, iPane };

            return;

         }

         if(get_element_rect(iPane, rect, element_tab) && rect.contains(item.m_pointHitTest))
         {

            item = { element_tab, iPane };

            return;

         }

      }

      item = element_none;

   }


   ::user::interaction * tab::GetNotifyWnd()
   {

#ifdef _UWP

      return nullptr;

#else

      ::user::interaction * pwnd;

      if ((pwnd = GetParent()->get_wnd()) != nullptr)
      {

         return pwnd;

      }

      return nullptr;

#endif

   }

   /*
   bool tab::create(::user::interaction * pchannel, UINT uiId)
   {
      if(!m_puserinteraction->create(
         pchannel,
         uiId))
         return false;
      m_bCreated = true;
      on_layout(::draw2d::graphics_pointer & pgraphics);
      return true;
   }
   */

   void tab::_001OnCreate(::message::message * pmessage)
   {

      m_bNoTabs = System.has_property("no_tabs");

      SCAST_PTR(::message::base, pbase, pmessage);

      if(pmessage->previous())
         return;

      __construct_new(get_data()->m_pimagelist);

      get_data()->m_pimagelist->create(16, 16, 0, 0, 0);

      auto pgraphics = ::draw2d::create_memory_graphics();

      get_data()->m_bCreated = true;

      pbase->m_lresult = 0;

      SetTimer(timer_defer_handle_auto_hide_tabs, 300);

      //post_message(WM_USER + 1342);

      m_iRestoredTabCount = restore_tabs();


      on_create_tabs();


   }


   void tab::on_create_tabs()
   {

      ::user::control_event ev;

      ev.m_puie      = this;

      ev.m_ptab      = this;

      ev.m_eevent    = ::user::event_on_create_tab;

      on_control_event(&ev);

   }


   ::count tab::restore_tabs()
   {

      ::count c = 0;

      __keep(m_bDisableSavingRestorableTabs);

      if(get_data()->m_matchanyRestore.m_itema.get_count() > 0)
      {

         var var;

         //if(data_get("restore_tab",var))
         //{

         //   c = open_tabs(var.vara());

         //}

      }

      return c;

   }


   void tab::install_message_routing(::channel *pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      //install_simple_ui_default_mouse_handling(pchannel);

      IGUI_MSG_LINK(WM_LBUTTONDOWN, pchannel, this, &tab::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP, pchannel, this, &tab::_001OnLButtonUp);
      IGUI_MSG_LINK(WM_MOUSEMOVE, pchannel, this, &tab::_001OnMouseMove);
      IGUI_MSG_LINK(WM_MOUSELEAVE, pchannel, this, &tab::_001OnMouseLeave);
      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &tab::_001OnCreate);
      IGUI_MSG_LINK(WM_SHOWWINDOW, pchannel, this, &tab::_001OnShowWindow);
      MSG_TYPE_LINK(::message::type_language, pchannel, this, &tab::_001OnAppLanguage);
      IGUI_MSG_LINK(message_start_tab_drag, pchannel, this,&tab::_001OnStartTabDrag);

      ////IGUI_MSG_LINK(WM_TIMER, pchannel, this, &tab::_001OnTimer);

   }


   void tab::_001SetSel(::index iSel)
   {

      {

         sync_lock lock(get_data()->mutex());

         get_data()->m_idaSel.remove_all();

         id idTab = tab_id(iSel);

         if (!idTab.is_empty())
         {

            get_data()->m_idaSel.add(idTab);

         }

      }
      
      //fork([this]()
      //{

         on_change_cur_sel();
         
      //});

   }


   tab_pane::tab_pane(class tab * ptab) :
      m_ptab(ptab),
      m_brushFill(e_create),
      m_brushFillSel(e_create),
      m_brushFillHover(e_create)
      //m_istrTitleEx3(ptab->get_context_application())
   {

      m_bTabPaneVisible = true;
      m_bPermanent   = false;

   }


   tab_pane::tab_pane(const ::user::tab_pane & tab_pane)
   {

      operator = (tab_pane);

   }


   tab_pane::~tab_pane()
   {

   }


   tab_pane & tab_pane::operator = (const tab_pane & tab_pane)
   {

      if(this != &tab_pane)
      {

         m_ptab            = tab_pane.m_ptab;
         m_id              = tab_pane.m_id;
         m_strTitle        = tab_pane.m_strTitle;
         m_pimage          = tab_pane.m_pimage;
         m_pplaceholder    = tab_pane.m_pplaceholder;
         m_bTabPaneVisible = tab_pane.m_bTabPaneVisible;
         m_bPermanent      = tab_pane.m_bPermanent;
      }

      return *this;

   }


   string tab_pane::get_title()
   {

      return m_strTitle;

   }


   void tab_pane::set_title(const char * pszTitle)
   {

      m_strTitle = pszTitle;

      m_ptab->set_need_layout();

   }


   void tab_pane::do_split_layout(::draw2d::graphics_extension & dc, ::draw2d::graphics_pointer & pgraphics)
   {

      string_array straTitle = m_straTitle.c_stra();

      straTitle.explode(MAGIC_PALACE_TAB_SPLT,get_title());

      m_sizeaText.set_size(straTitle.get_count());

      for(int iTitle = 0; iTitle < straTitle.get_count(); iTitle++)
      {

         dc.GetTextExtent(pgraphics,straTitle[iTitle],m_sizeaText[iTitle]);

      }

   }


   tab_pane_array::tab_pane_array()
   {

   }


   tab_pane_array::~tab_pane_array()
   {

   }


   tab_pane * tab_pane_array::get_by_id(id id)
   {

      for(i32 i = 0; i < this->get_count(); i++)
      {
         if(this->element_at(i)->m_id == id)
         {
            return element_at(i);
         }
      }
      return nullptr;
   }

   ::count tab_pane_array::get_visible_count()
   {

      ::count count = 0;

      for(i32 i = 0; i < this->get_count(); i++)
      {
         if(this->element_at(i)->m_bTabPaneVisible)
         {
            count++;
         }
      }

      return count;
   }


   void tab::_001OnAppLanguage(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      set_need_layout();

   }


   void tab::_001SetTabCallback(tab_callback * pcallback)
   {

      if(get_data()->m_pcallback != nullptr)
      {

         delete get_data()->m_pcallback;

      }

      get_data()->m_pcallback = pcallback;

   }


   ::index tab::_001GetSel()
   {

      if(get_data()->m_idaSel.get_size() == 1)
      {

         return id_tab(get_data()->m_idaSel[0]);

      }
      else
      {

         return -1;

      }

   }


   ::count tab::_001GetPaneCount()
   {

      return get_data()->m_panea.get_count();

   }


   bool tab::_001IsAddTab(::index iPane)
   {

      if(get_data()->m_pcallback != nullptr)
      {

         return get_data()->m_pcallback->_001IsAddTab(this, iPane);

      }
      else
      {

         return false;

      }

   }


   void tab::_001OnTabClick(::index iPane)
   {

      if(get_data()->m_pcallback != nullptr)
      {

         get_data()->m_pcallback->_001OnTabClick(this, iPane);

      }
      else
      {

         _001SelectTab(iPane);

      }

   }


   void tab::_001OnTabClose(::index iPane)
   {

      if(get_data()->m_pcallback != nullptr)
      {

         get_data()->m_pcallback->_001OnTabClose(this, iPane);

      }
      else
      {

         _001CloseTab(iPane);

      }

   }


   bool tab::show_tab_by_id(id id, bool bShow)
   {

      ::user::tab_pane * ppane = get_pane_by_id(id);

      if (ppane == nullptr)
      {

         return false;

      }

      ppane->m_bTabPaneVisible = bShow;

      set_need_layout();

      return true;

   }


   bool tab::show_pane(::index iPane, bool bShow)
   {

      ::user::tab_pane * ppane = get_pane(iPane);

      if (ppane == nullptr)
      {

         return !bShow;

      }

      ppane->m_bTabPaneVisible = bShow;

      set_need_layout();

      return true;

   }


   bool tab::hide_tab(::index iTab)
   {

      index iPane = tab_pane(iTab);

      if (iPane < 0)
      {

         return false;

      }

      if (!show_pane(iPane, false))
      {

         return false;

      }

      return true;

   }


   ::user::interaction * tab::tab_window(::index iPane)
   {

      __pointer(place_holder) pholder = tab_holder(iPane);

      if (pholder.is_null())
      {

         return nullptr;

      }

      return pholder->get_hold();

   }


   ::user::place_holder * tab::tab_holder(::index iTab)
   {

      ::user::tab_pane * ppane = get_tab(iTab);

      if (ppane == nullptr)
      {

         return nullptr;

      }

      return ppane->m_pplaceholder;

   }


   ::user::interaction * tab::pane_window(::index iPane)
   {

      __pointer(place_holder) pholder = pane_holder(iPane);

      if (pholder.is_null())
      {

         return nullptr;

      }

      return pholder->get_hold();

   }


   ::user::place_holder * tab::pane_holder(::index iPane)
   {

      ::user::tab_pane * ppane = get_pane(iPane);

      if (ppane == nullptr)
      {

         return nullptr;

      }

      return ppane->m_pplaceholder;

   }


   tab_pane * tab::get_pane(::index iPane)
   {

      if (iPane < 0)
      {

         return nullptr;

      }

      if (iPane >= get_data()->m_panea.get_count())
      {

         return nullptr;

      }

      return get_data()->m_panea.element_at(iPane);

   }


   tab_pane * tab::get_tab(::index iTab)
   {

      index iPane = tab_pane(iTab);

      if(iPane < 0)
      {

         return nullptr;

      }

      return get_data()->m_panea.element_at(iPane);

   }


   void tab::_001SelectTab(::index iPane)
   {
//      if(get_tab_holder(_001GetSel()) != nullptr)
      //    {
      //     get_tab_holder(_001GetSel())->display(display_none);
      // }
      _001SetSel(iPane);
      // if(get_tab_holder(_001GetSel()) != nullptr)
      //{
      // get_tab_holder(_001GetSel())->display(display_normal);
      // }

      //on_layout(::draw2d::graphics_pointer & pgraphics);

   }


   void tab::on_change_cur_sel()
   {

      if(get_data()->m_pcallback != nullptr && dynamic_cast < ::user::tab * > (get_data()->m_pcallback) != this)
      {

         get_data()->m_pcallback->_001OnShowTab(this);

      }

      Application.on_change_cur_sel(this);

   }


   void tab:: _001SetVertical(bool bVertical)
   {

      get_data()->m_bVertical = bVertical;

   }


   void tab::_001ConnectParent(::channel * pchannel)
   {

      UNREFERENCED_PARAMETER(pchannel);

   }


   id tab::get_cur_tab_id()
   {

      return tab_id(_001GetSel());

   }


   ::index tab::id_tab(id id)
   {

      index iTab = -1;

      for(::index iPane = 0; iPane < get_data()->m_panea.get_size(); iPane++)
      {

         if (get_data()->m_panea[iPane]->m_bTabPaneVisible)
         {

            iTab++;

         }

         if (get_data()->m_panea[iPane]->m_id == id)
         {

            return iTab;

         }

      }

      return -1;

   }


   ::index tab::id_pane(id id)
   {

      for (::index iPane = 0; iPane < get_data()->m_panea.get_size(); iPane++)
      {

         if (get_data()->m_panea[iPane]->m_id == id)
         {

            return iPane;

         }

      }

      return -1;

   }


   id tab::tab_id(::index iTab)
   {

      for(i32 iPane = 0; iPane < get_data()->m_panea.get_count(); iPane++)
      {

         if(get_data()->m_panea[iPane]->m_bTabPaneVisible)
         {

            if(iTab <= 0)
            {

               return get_data()->m_panea[iPane]->m_id;

            }
            else
            {

               iTab--;

            }

         }

      }

      return id();

   }


   id tab::pane_id(::index iPane)
   {

      if (iPane < 0)
      {

         return id();

      }

      if (iPane >= get_data()->m_panea.get_size())
      {

         return id();

      }

      return get_data()->m_panea[iPane]->m_id;

   }


   ::index tab::tab_pane(index iTab)
   {

      if (iTab < 0)
      {

         return -1;

      }

      for (::index iPane = 0; iPane < get_data()->m_panea.get_size(); iPane++)
      {

         if (!get_data()->m_panea[iPane]->m_bTabPaneVisible)
         {

            continue;

         }

         if(iTab <= 0)
         {

            return iPane;

         }

         iTab--;

      }

      return -1;

   }


   ::index tab::pane_tab(index iPaneParam)
   {

      if (iPaneParam < 0)
      {

         return -1;

      }

      index iTab = 0;

      for (::index iPane = 0; iPane < get_data()->m_panea.get_size(); iPane++)
      {

         if (iPaneParam == iPane)
         {

            if (get_data()->m_panea[iPane]->m_bTabPaneVisible)
            {

               return iTab;

            }
            else
            {

               return -1;

            }

         }

         if (get_data()->m_panea[iPane]->m_bTabPaneVisible)
         {

            iTab++;

         }


      }

      return -1;

   }


   bool tab::set_cur_tab_by_id(id id, ::create * pcreate)
   {

      try
      {

         if (::is_set(pcreate))
         {

            m_spcreate = pcreate;

         }

         ::index iTab = id_tab(id);

         if(iTab == -1)
         {

            iTab = create_tab_by_id(id);

            if (iTab == -1)
            {

               return false;

            }

         }

         _001SetSel(iTab);

      }
      catch (::exit_exception * pexception)
      {

         __rethrow(pexception);

      }
      catch (const ::exception_pointer & pexception)
      {

         ::exception_pointer esp(pexception);

         return false;

      }
      catch(...)
      {

         return false;

      }

      if (::is_set(pcreate) && pcreate == m_spcreate)
      {

         m_spcreate = nullptr;

      }

      return true;

   }



   e_position tab::DragHitTest(const ::point & point)
   {
      ::rect rect;
      GetDragRect(rect, position_top);
      if(rect.contains(point))
      {
         return position_top;
      }
      GetDragRect(rect, position_bottom);

      if(rect.contains(point))
      {

         return position_bottom;

      }

      GetDragRect(rect, position_left);

      if(rect.contains(point))
      {

         return position_left;

      }

      GetDragRect(rect, position_right);

      if(rect.contains(point))
      {

         return position_right;

      }

      return position_none;

   }


   void tab::GetDragRect(RECT * prect, e_position eposition)

   {
      switch(eposition)
      {
      case position_top:
      {
         prect->top = get_data()->m_rectTabClient.top;

         prect->left = get_data()->m_rectTabClient.left + get_data()->m_rectTabClient.width() / 3;

         prect->right = prect->left + get_data()->m_rectTabClient.width() / 3;

         prect->bottom = prect->top + get_data()->m_rectTabClient.height() / 3;

      }
      break;
      case position_left:
      {
         prect->top = get_data()->m_rectTabClient.top + get_data()->m_rectTabClient.height() / 3;

         prect->left = get_data()->m_rectTabClient.left;

         prect->right = prect->left + get_data()->m_rectTabClient.width() / 3;

         prect->bottom = prect->top + get_data()->m_rectTabClient.height() / 3;

      }
      break;
      case position_right:
      {
         prect->top = get_data()->m_rectTabClient.top + get_data()->m_rectTabClient.height() / 3;

         prect->left = get_data()->m_rectTabClient.left + get_data()->m_rectTabClient.width() * 2 / 3;

         prect->right = prect->left + get_data()->m_rectTabClient.width() / 3;

         prect->bottom = prect->top + get_data()->m_rectTabClient.height() / 3;

      }
      break;
      case position_bottom:
      {
         prect->top = get_data()->m_rectTabClient.top + get_data()->m_rectTabClient.height() * 2 / 3;

         prect->left = get_data()->m_rectTabClient.left + get_data()->m_rectTabClient.width() / 3;

         prect->right = prect->left + get_data()->m_rectTabClient.width() / 3;

         prect->bottom = prect->top + get_data()->m_rectTabClient.height() / 3;

      }
      break;
      default:
         break;
      }
   }



   void tab::_001OnDropTab(::index iPane, e_position eposition)
   {

      if(get_data()->m_pcallback != nullptr)
      {

         get_data()->m_pcallback->_001OnDropTab(iPane, eposition);

      }

   }


   ::user::interaction * tab::get_view_uie()
   {

      return nullptr;

   }


   void tab::get_child_rect(RECT* prect)
   {

      if (::is_null(prect))
      {

         return;

      }

      sync_lock sl(mutex());

      *prect = get_data()->m_rectTabClient;

   }


   id tab::get_current_id()
   {

      return get_cur_tab_id();

   }


   void tab::update(::update * pupdate)
   {

      ::user::interaction::update(pupdate);

      if (pupdate->m_id == id_get_topic_view_id)
      {

         pupdate->value(id_id) = get_cur_tab_id();

         pupdate->m_bRet = true;

      }
      else if (pupdate->m_id == id_set_topic_view_by_id)
      {

         set_cur_tab_by_id(pupdate->value(id_id));

         pupdate->m_bRet = true;

      }
      else if(pupdate->m_id == id_place_child_title_change)
      {

         for (auto& ppane : get_data()->m_panea)
         {

            if (ppane->m_pplaceholder == pupdate->m_puserinteraction)
            {

               auto pchild = ppane->m_pplaceholder->m_uiptraChild.first();

               if (pchild)
               {

                  string strTitle = pchild->value("place_child_title");

                  ppane->set_title(strTitle);

               }

            }

         }

      }

   }


   void tab::rotate()
   {

      __throw(todo());

   }


   void tab::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction::_001OnTimer(ptimer);

      if (ptimer->m_nIDEvent == timer_defer_handle_auto_hide_tabs)
      {

         if (defer_handle_auto_hide_tabs(false))
         {

            set_need_layout();

            set_need_redraw();

         }

      }

      if(ptimer->m_nIDEvent == timer_drag_start)
      {
         //auto elapsed = g_tickDragStart.elapsed();
         KillTimer(timer_drag_start);

         ReleaseCapture();

         ::point point = Session.get_cursor_pos();

         auto item = hit_test(point);

         index iClickTab = get_data()->m_iClickTab;

         if(item && item == iClickTab)
         {

            get_data()->m_bDrag = true;

            m_estate = state_drag_commanded;

            post_message(message_start_tab_drag);

         }
         else
         {

            m_estate = state_initial;

         }

      }

   }


   void tab::_001OnStartTabDrag(::message::message * pmessage)
   {

      if(get_data()->m_pcallback != nullptr)
      {

         get_data()->m_pcallback->_001DropTargetWindowInitialize(this);


      }

      if (m_estate == state_drag_commanded)
      {

         m_estate = state_initial;

      }

   }


   void tab::_000OnMouse(::message::mouse * pmouse)
   {

      if(m_bShowTabs)
      {

         // these try catchs are needed for multi threading supporting: multi threaded windows: an endeavour
         // Now I understand why Microsoft (TM) Windows (R) windows are single threaded.
         // to debug, enable catch exceptions in debugger
         try
         {

            ::rect rectTabScreen(get_data()->m_rectTab);

            _001ClientToScreen(rectTabScreen);

            if ((pmouse->m_id == WM_LBUTTONDOWN || pmouse->m_id == WM_LBUTTONUP) && rectTabScreen.contains(pmouse->m_point))
            {

               route_message(pmouse);

               if (pmouse->m_lresult != 0)
               {

                  return;

               }

            }
            else if (pmouse->m_id == WM_MOUSEMOVE)
            {

               route_message(pmouse);

               if (pmouse->m_lresult != 0)
               {

                  return;

               }

            }

         }
         catch(...)
         {

         }

      }
      else if(pmouse->m_id == WM_MOUSEMOVE)
      {

      }

      __pointer(::user::interaction) pinteraction;


      while(rget_child(pinteraction))
      {

         try
         {

            if(pinteraction->is_window_visible() && pinteraction->_001IsPointInside(pmouse->m_point))
            {

               try
               {

                  pinteraction->_000OnMouse(pmouse);

                  if (pmouse->m_bRet)
                  {

                     return;

                  }

               }
               catch(...)
               {

               }

            }

         }
         catch(...)
         {

         }

      }

   }


   tab::data * tab::get_data()
   {

      return m_spdata;

   }


   tab_pane * tab::get_pane_by_id(id id)
   {

      return get_data()->get_pane_by_id(id);

   }


   tab_pane * tab::create_pane_by_id(id id)
   {

      create_tab_by_id(id);

      return get_data()->get_pane_by_id(id);

   }


   ::index tab::create_tab_by_id(id id)
   {

      if (!add_tab("", id))
      {

         return -1;

      }

      index iTab = id_tab(id);

      if (iTab < 0)
      {

         return -1;

      }

      return iTab;

   }

   /// array - if you want, you can hint on_change_pane_count
   /// with added panes info. Pass array with nullptr value to force save restorable tabs
   void tab::on_change_pane_count(array < ::user::tab_pane * > array)
   {

      bool bAny = false;

      for (auto ppane : array)
      {

         if (ppane == nullptr || matches_restorable_tab(ppane->m_id, ppane->m_pplaceholder))
         {

            bAny = true;

            break;

         }

      }

      if (array.is_empty() || bAny)
      {

         save_restorable_tabs();

      }
      else
      {

         TRACE("Yup! Optimized Out a save_restorable_tabs {?A*dev}op! ...... . .\n");

      }

      //set_need_layout();

   }


   void tab::save_restorable_tabs()
   {

      if (m_bDisableSavingRestorableTabs)
         return;

      if (get_data()->m_matchanyRestore.m_itema.get_count() > 0)
      {

         var_array vara;

         get_restore_tab(vara);

         //if (vara.get_size() > 0)
         //{
         //   TRACE(".");
         //   for (index i = 0; i < 200; i++)
         //   {


         //data_set("restore_tab", vara);
         //   }
         //}
         //else
         //{
         //   TRACE("o");
         //   for (index i = 0; i < 200; i++)
         //   {


         //      data_save("restore_tab", vara);
         //   }

         //}

      }


   }


   void tab::get_text_id(string_array & stra)
   {
      get_presuffixed_ci_id(stra, nullptr, nullptr);
   }

   void tab::get_prefixed_ci_id(string_array & stra, const char * pszPrefix)
   {
      get_presuffixed_ci_id(stra, pszPrefix, nullptr);
   }


   void tab::get_suffixed_ci_id(string_array & stra, const char * pszSuffix)
   {

      get_presuffixed_ci_id(stra, nullptr, pszSuffix);

   }


   void tab::get_presuffixed_ci_id(string_array & stra, const char * pszPrefix, const char * pszSuffix)
   {

      string strPrefix(pszPrefix);

      string strSuffix(pszSuffix);

      string strPath;

      tab_pane_array & panea = get_data()->m_panea;

      for(i32 i = 0; i < panea.get_count(); i++)
      {

         ::user::tab_pane & tab_pane = panea(i);

         strPath = tab_pane.m_id;

         if(strPrefix.is_empty() || ::str::begins_ci(strPath, strPrefix))
         {

            if(strSuffix.is_empty() || ::str::ends_ci(strPath, strSuffix))
            {

               stra.add(strPath);

            }

         }

      }

   }


   void tab::get_begins_ci_eat_id(string_array & stra, const char * pszPrefix)
   {

      get_begins_ends_ci_eat_id(stra, pszPrefix, nullptr);

   }


   void tab::get_ends_ci_eat_id(string_array & stra, const char * pszSuffix)
   {

      get_begins_ends_ci_eat_id(stra, nullptr, pszSuffix);

   }


   void tab::get_begins_ends_ci_eat_id(string_array & stra, const char * pszPrefix, const char * pszSuffix)
   {

      string strPrefix(pszPrefix);

      string strSuffix(pszSuffix);

      string strPath;

      tab_pane_array & panea = get_data()->m_panea;

      for(i32 i = 0; i < panea.get_count(); i++)
      {

         ::user::tab_pane & tab_pane = panea(i);

         strPath = tab_pane.m_id;

         if(strPrefix.is_empty() || ::str::begins_ci(strPath, strPrefix))
         {

            if(strSuffix.is_empty() || ::str::ends_ci(strPath, strSuffix))
            {

               stra.add(strPath);

            }

         }

      }

   }


   bool tab::matches_restorable_tab(const var & varId, ::user::place_holder * pholder)
   {

      ::match::any & matchany = get_data()->m_matchanyRestore;

      if (pholder != nullptr && (bool) pholder->value("void_restore"))
      {

         return false;

      }

      if (!matchany.has_item())
      {

         return false;

      }

      if (!matchany.matches(varId))
      {

         return false;

      }

      return true;

   }

   void tab::get_restore_tab(var_array & vara)
   {

      var varId;

      tab_pane_array & panea = get_data()->m_panea;

      for(i32 i = 0; i < panea.get_count(); i++)
      {

         varId = panea[i]->m_id;

         if(matches_restorable_tab(varId, panea[i]->m_pplaceholder))
         {

            vara.add(varId);

         }

      }

   }


   bool tab::has_restore_tab()
   {

      ::match::any  & matchany = get_data()->m_matchanyRestore;

      if(matchany.is_there_no_item())
         return false;
      var varId;
      tab_pane_array & panea = get_data()->m_panea;
      for(i32 i = 0; i < panea.get_count(); i++)
      {
         varId = panea[i]->m_id;
         if(matchany.matches(varId))
         {
            return true;
         }
      }

      return false;

   }


   ::count tab::open_tabs(const var_array & vara)
   {

      ::count c = 0;

      string_array stra;

      for(i32 i = 0; i < vara.get_count(); i++)
      {

         // ODOW : TODO : should create bergedgewrapper to open bergedge inside a window.

         if(vara[i].get_type() == ::type_string && vara[i].get_string() == "app:bergedge")
            continue;

         if(vara[i].get_type() == ::type_string && vara[i].get_string() == "app:")
            continue;

         //if(stra.add_unique(vara[i]) >= 0)
         //{
         //create_tab_by_id(stra.last());

         set_cur_tab_by_id(vara[i].get_id());

         c++;

         //}

      }

      return c;

   }


   void tab::_001CloseTab(::index iTab)
   {

      remove_tab_by_id(tab_id(iTab));

   }


   void tab::_001OnShowWindow(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

//      SCAST_PTR(::message::show_window, pshowwindow, pmessage);

//      ::user::place_holder * pholder = tab_holder(_001GetSel());
//
//      if (pholder != nullptr)
//      {
//
//         if (pshowwindow->m_bShow)
//         {
//
//            pholder->display(display_normal);
//
//         }
//         else
//         {
//
//            pholder->display(display_none);
//
//         }
//
//      }

   }


} // namespace base


