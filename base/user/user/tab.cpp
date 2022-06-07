#include "framework.h"
//#include "base/user/user/_user.h"
#include "aura/update.h"
#include "acme/constant/timer.h"
#include "aqua/xml.h"
#include "tab_pane.h"
#include "aura/graphics/draw2d/_draw2d.h"
#include "aura/graphics/image/list.h"
#include "acme/platform/timer.h"


//extern CLASS_DECL_BASE thread_int_ptr < DWORD_PTR > t_time1;

// pgraphics->get_text_extent("->:<-"); // oh no!! omg!! The size_i32 is the size_i32 of the alien!!
#define MAGIC_PALACE_TAB_SPLT "->:<-"
#define MAGIC_PALACE_TAB_SIZE "-/-"
#define MAGIC_PALACE_TAB_TEXT "/"


::duration g_tickDragStart;


namespace user
{


   tab::tab()
   {

      m_bTabScrollingActive = false;

      m_bHoverDefaultMouseHandling = true;

      m_econtroltype = e_control_type_tab;

      m_bMouseDown = false;

      m_iTabScroll = 0;
      m_iTabScrollMax = 0;
      m_iTabSize = 0;
      m_edisplayParentFrameAutoHide = ::e_display_none;
      m_estate = e_state_initial;

      m_iRestoredTabCount = 0;

      m_bDisableSavingRestorableTabs           = true;

      m_bShowTabs                      = true;

      m_bNoTabs                        = false;

      m_bDrawTabAtBackground           = true;

      m_bCreatedTabs                   = false;

      m_bAutoCreateTabsOnCreate        = true;

   }


   tab::~tab()
   {

   }

   
   void tab::on_initialize_object()
   {

      //auto estatus = 
      
      ::user::interaction::on_initialize_object();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      __defer_construct_new(m_pdata);

      //if (estatus == ::success)
      //{

         auto pdata = get_data();

         pdata->m_iHeightAddUp = 0;
         pdata->m_pcallback = nullptr;
         pdata->m_bCreated = false;
         pdata->m_iTabHeight = 16;
         pdata->m_iTabWidth = 48;
         pdata->m_iClickTab = -1;

      //}

      //return estatus;

   }


   /*bool tab::add_tab(::u32 uIdTitle, i32 iId)
   {
      get_pane get_pane;
      ppane->m_uiId = uiIdTitle;
      ppane->m_istrTitleEx = L"";
      ppane->m_iId = iId == -1 ? get_data()->m_tabpanecompositea.get_size() : iId;
      if(!ppane->m_wstrTitle.load_string(uiIdTitle))
      {
         return false;
      }*/
   //   ppane->m_pcontainer = pcontainer;
   // ppane->m_type = nullptr;
   /* ppane->m_iImage = -1;

    get_data()->m_tabpanecompositea.add(get_pane);
    return true;
   }*/


   enum_element tab::get_default_element() const
   {

      return e_element_tab;

   }


   bool tab::set_title(::index iIndex, const ::string & pcsz)

   {

      synchronous_lock synchronouslock(mutex());

      if (iIndex < 0)
      {

         return false;

      }

      if (iIndex >= get_data()->m_tabpanecompositea.get_size())
      {

         return false;

      }

      get_data()->m_tabpanecompositea[iIndex]->set_title(pcsz);


      return true;

   }


   bool tab::set_title_by_id(const ::atom & atom, const ::string & pcsz)
   {

      auto iIndex = id_index(atom);

      if (iIndex < 0)
      {

         return false;

      }

      get_data()->m_tabpanecompositea[iIndex]->set_title(pcsz);

      return true;

   }


   //bool tab::set_tab(const ::string & pcsz, const ::atom & atom, bool bVisible)
   //{

   //   return add_tab(pcsz, atom, bVisible, true);

   //}


   bool tab::add_tab(const ::string & strTitle, const ::atom & atomImpact, bool bVisible, bool bPermanent, ::user::place_holder * pholder)
   {

      ::atom atom(atomImpact);

      auto & ppane = get_data()->m_tabpanecompositea.add_new();

      __compose_new(ppane);

      ppane->initialize_tab_pane(this);

      // second colon starts the text.
      // if the text is a ID, the ID will be result when no translation
      // if the text is a text (in English), the text (in English) will be the result when there is no translation.
      //set_tille("text://hellomultiverse/AKDFJG./:Main Tab"));
      ppane->set_title(strTitle);

      ppane->m_bTabPaneVisible   = bVisible;
      ppane->m_bPermanent        = bPermanent;
      ppane->m_pplaceholder      = pholder;

      synchronous_lock synchronouslock(mutex());

      if (atom.is_empty())
      {

         atom = get_data()->m_tabpanecompositea.get_size();

      }

      ppane->m_atom = atom;

      on_change_tab_count({ ppane });

      return true;

   }

   
   bool tab::set_tab(const ::string & strName, const ::atom & atomImpact, bool bVisible)
   {

      return add_tab(strName, atomImpact, bVisible, true);

   }


   bool tab::add_tab_with_icon(const ::string & strName, const ::string & strIcon, const ::atom & atomImpact, bool bVisible, bool bPermanent, ::user::place_holder * pplaceholder)
   {

      ::atom atom(atomImpact);

      auto & ppane = get_data()->m_tabpanecompositea.add_new();

      __compose_new(ppane);

      ppane->initialize_tab_pane(this);

      ppane->m_bTabPaneVisible = bVisible;
      ppane->m_bPermanent = bPermanent;
      ppane->set_title(strName);

      synchronous_lock synchronouslock(mutex());

      if (atom.is_empty())
      {

         atom = get_data()->m_tabpanecompositea.get_size();

      }

      ppane->m_atom = atom;
      ppane->m_pplaceholder = pplaceholder;

      auto pcontext = m_pcontext->m_pauracontext;

      auto pcontextimage = pcontext->context_image();

      ppane->m_pimage = pcontextimage->load_image(strIcon, { .cache = false });

      on_change_tab_count({ ppane });

      return true;

   }


   bool tab::set_tab_with_icon(const ::string & strName, const ::string & strIcon, const ::atom & atomImpact, bool bVisible)
   {

      return add_tab_with_icon(strName, strIcon, atomImpact, bVisible, true);

   }
      
      
   void tab::_001OnRemoveTab(class tab_pane * ptab)
   {


   }


   bool tab::erase_tab_by_id(const ::atom & atom)
   {

      bool bRestorableMatch = false;

      for(i32 i = 0; i < get_data()->m_tabpanecompositea.get_count(); i++)
      {

         if(get_data()->m_tabpanecompositea[i]->m_atom == atom)
         {

            if (!bRestorableMatch && matches_restorable_tab(get_data()->m_tabpanecompositea[i]->m_atom, get_data()->m_tabpanecompositea[i]->m_pplaceholder))
            {

               bRestorableMatch = true;

            }

            erase_tab(i, false);

            break;

         }

      }

      if (bRestorableMatch)
      {

         on_change_tab_count({ nullptr });

      }

      on_change_tab_count();

      return true;

   }


   //bool tab::set_image_tab(const ::string & pcszTitle, const ::string & pszImage, const ::atom & atom, bool bVisible)
   //{

   //   return add_image_tab(pcszTitle, pszImage, atom, bVisible, true);

   //}




   void tab::erase_tab(::index iIndex, bool bVisible)
   {

      synchronous_lock synchronouslock(mutex());

      if (iIndex < 0 || iIndex >= get_data()->m_tabpanecompositea.get_size())
      {

         return;

      }

      if(bVisible)
      {

         for(i32 i = 0; iIndex >= 0 && i < get_data()->m_tabpanecompositea.get_count(); i++)
         {

            if(get_data()->m_tabpanecompositea[i]->m_bTabPaneVisible)
            {

               if(iIndex <= 0)
               {

                  auto ppane = get_data()->m_tabpanecompositea[iIndex];

                  get_data()->m_tabpanecompositea.erase_at(iIndex);

                  _001OnRemoveTab(ppane);

                  on_change_tab_count();

                  break;

               }
               else
               {

                  iIndex--;

               }

            }

         }

      }
      else
      {

         auto ppane = get_data()->m_tabpanecompositea[iIndex];

         get_data()->m_tabpanecompositea.erase_at(iIndex);

         _001OnRemoveTab(ppane);

         on_change_tab_count();

      }

   }


   void tab::erase_all_tabs()
   {

      synchronous_lock synchronouslock(mutex());

      get_data()->m_tabpanecompositea.erase_all();

      on_change_tab_count();

   }



   bool tab::defer_handle_auto_hide_tabs(bool bLayout)
   {

      if (!get_wnd()->is_ok())
      {

         return false;

      }

      //__pointer(::experience::frame_window) pchannel = top_level_frame();
      //
      //if (pchannel != nullptr && pchannel->m_bInitialFramePosition)
      //{
      //   return false;
      //}

      bool bNeedLayout = false;

      ::user::interaction * puiTopLevel = get_top_level();

      if (puiTopLevel != nullptr)
      {

         if (puiTopLevel->frame_is_transparent() && !top_level_frame()->layout().is_full_screen())
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

            m_edisplayParentFrameAutoHide = top_level_frame()->layout().design().display();

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

         m_edisplayParentFrameAutoHide = top_level_frame()->layout().design().display();

         return bNeedLayout;

      }

      if(m_bShowTabs)
      {

         if(top_level_frame()!= nullptr && top_level_frame()->layout().is_full_screen())
         {

            ::rectangle_i32 rectangleTab(get_data()->m_rectangleTab);

            client_to_screen(rectangleTab);

            auto psession = get_session();

            auto puser = psession->user();

            auto pwindowing = puser->windowing();

            auto pointCursor = pwindowing->get_cursor_position();

            bool bShowTabs = rectangleTab.contains(pointCursor);

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

         auto pframe = get_parent_frame();

         if(::is_set(pframe) && !pframe->layout().is_full_screen())
         {

            m_bShowTabs = true;

            if (bLayout)
            {

               set_need_layout();

            }

            bNeedLayout = true;

         }
         else if(::is_set(get_app()) && ::is_set(get_app()->get_session()))
         {

            ::rectangle_i32 rectangleWindow;

            get_window_rect(rectangleWindow);

            bool bShowTabs;

            auto psession = get_session();

            auto puser = psession->user();

            auto pwindowing = puser->windowing();

            auto pointCursor = pwindowing->get_cursor_position();

            if(get_data()->m_bVertical)
            {

               bShowTabs = pointCursor.x <= rectangleWindow.left;

            }
            else
            {
               bShowTabs = pointCursor.y <= rectangleWindow.top;
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

      if (get_parent_frame() != nullptr && (bNeedLayout || !get_parent_frame()->is_this_screen_visible()))
      {

         m_edisplayParentFrameAutoHide = get_parent_frame()->layout().design().display();

      }

      return bNeedLayout;

   }


   void tab::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      defer_handle_auto_hide_tabs();

      if (m_bNoTabs || !m_bShowTabs)
      {

         return;

      }

      if (get_top_level()->frame_is_transparent())
      {

         return;

      }

      //point_i32 pointViewportOffset = pgraphics->GetViewportOrg();

      ::rectangle_f64 rClip;

      pgraphics->get_clip_box(&rClip);

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

      ::rectangle_i32 rectangle;
      ::rectangle_i32 rectangleBorder;
      ::rectangle_i32 rectangleText;
      ::rectangle_i32 rectangleClient;
      ::rectangle_i32 rectangleIcon;
      ::rectangle_i32 rectangleClose;

      get_data()->m_ppen->create_solid(1, rgb(32, 32, 32));

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto pstyle = get_style(pgraphics);

      ::index iIndex = 0;

      auto pbrushText = __create < ::draw2d::brush > ();

      auto ppenBorder = __create < ::draw2d::pen > ();

      for (; iIndex < get_data()->m_tabpanecompositea.get_size(); iIndex++)
      {

         auto ppane = get_data()->m_tabpanecompositea[iIndex].get();

         if (!ppane->m_bTabPaneVisible)
         {

            continue;

         }


         ::user::e_state estate = ::user::e_state_none;

         if (get_data()->m_idaSel.contains(ppane->m_atom))
         {

            estate |= ::user::e_state_selected;

         }

         if (::is_item(m_pitemHover, iIndex))
         {

            estate |= ::user::e_state_hover;

         }

         iIndex++;

         if (!get_element_rect(iIndex, rectangle, ::e_element_tab))
         {

            continue;

         }

         if (!get_element_rect(iIndex, rectangleBorder, ::e_element_border))
         {

            continue;

         }

         if (!get_element_rect(iIndex, rectangleClient, ::e_element_client))
         {

            continue;

         }

         if (get_data()->m_bVertical)
         {

            if (get_element_rect(iIndex, rectangleIcon, ::e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               image_source imagesource(ppane->m_pimage);

               image_drawing_options imagedrawingoptions(rectangleIcon);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

            auto ppath = __create < ::draw2d::path > ();

            if (true)
            {

               if (get_data()->m_idaSel.contains(ppane->m_atom))
               {

                  ppath->add_line(rectangleBorder.right, rectangleBorder.bottom, rectangleBorder.left + 1, rectangleBorder.bottom);

                  ppath->add_line(rectangleBorder.left, rectangleBorder.top - (rectangleBorder.left - rectangleClient.left));
                  ppath->add_line(rectangleClient.left, rectangleBorder.top);
                  ppath->add_line(rectangleBorder.right, rectangleBorder.top);

                  ppath->close_figure();

                  ppane->m_pbrushFillSel->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 235, 235, 230), argb(250, 255, 255, 250));

                  pgraphics->set(ppane->m_pbrushFillSel);

                  pgraphics->fill(ppath);

                  ppenBorder->create_solid(1.0, get_color(pstyle, ::e_element_border, ::user::e_state_selected));

                  pgraphics->draw(ppath);

                  pgraphics->set(get_font(pstyle));

                  pbrushText->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));

               }
               else
               {

                  ppath->add_line(rectangleBorder.right, rectangleBorder.bottom, rectangleBorder.left + 1, rectangleBorder.bottom);
                  ppath->add_line(rectangleBorder.left, rectangleBorder.top - (rectangleBorder.left - rectangleClient.left));
                  ppath->add_line(rectangleText.left, rectangleBorder.top);
                  ppath->add_line(rectangleBorder.right, rectangleBorder.top);
                  ppath->add_line(rectangleBorder.right, rectangleBorder.bottom);

                  ppath->close_figure();

                  if (::is_item(m_pitemHover, iIndex) 
                     && !::is_element(m_pitemHover, ::e_element_close_tab_button)
                     && !in_element_range(m_pitemHover, ::e_element_split, 100))
                  {

                     ppane->m_pbrushFillHover->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 215, 215, 210), argb(250, 235, 235, 230));

                     pgraphics->set(ppane->m_pbrushFillHover);

                     pgraphics->fill(ppath);

                     ppenBorder->create_solid(1.0, get_color(pstyle, ::e_element_border, ::user::e_state_hover));

                     pgraphics->set(ppenBorder);

                     pgraphics->draw(ppath);

                     pgraphics->set(get_font(pstyle, e_state_hover));

                     pbrushText->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_hover));

                  }
                  else
                  {

                     ppane->m_pbrushFill->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 175, 175, 170), argb(250, 195, 195, 190));

                     pgraphics->set(ppane->m_pbrushFill);

                     pgraphics->fill(ppath);

                     ppenBorder->create_solid(1.0, get_color(pstyle, ::e_element_border));

                     pgraphics->set(ppenBorder);

                     pgraphics->draw(ppath);

                     pgraphics->set(get_font(pstyle));

                     pbrushText->create_solid(get_color(pstyle, ::e_element_item_text));

                  }

               }

            }

         }
         else
         {

            if (get_element_rect(iIndex, rectangleIcon, ::e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               image_source imagesource(ppane->m_pimage);

               image_drawing_options imagedrawingoptions(rectangleIcon);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

            if (true)
            {

               auto ppath = __create < ::draw2d::path > ();

               if (get_data()->m_idaSel.contains(ppane->m_atom))
               {

                  ppath->add_line(rectangleBorder.left, rectangleClient.bottom, rectangleBorder.left, rectangleBorder.top);

                  ppath->add_line(rectangleClient.right, rectangleBorder.top);

                  ppath->add_line(rectangleBorder.right, rectangleBorder.top + (rectangleBorder.right - rectangleClient.right));

                  ppath->add_line(rectangleBorder.right - 1, rectangleClient.bottom);

                  ppath->close_figure();

                  ppane->m_pbrushFillSel->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 235, 235, 230), argb(250, 255, 255, 250));

                  pgraphics->set(ppane->m_pbrushFillSel);

                  pgraphics->fill(ppath);

                  ppenBorder->create_solid(1.0, get_color(pstyle, ::e_element_border, ::user::e_state_selected));

                  pgraphics->set(ppenBorder);

                  pgraphics->draw(ppath);

                  pgraphics->set(get_font(pstyle));

                  pbrushText->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));

               }
               else
               {

                  ppath->add_line(rectangleBorder.left, rectangleClient.bottom, rectangleBorder.left, rectangleBorder.top);

                  ppath->add_line(rectangleClient.right, rectangleBorder.top);

                  ppath->add_line(rectangleBorder.right, rectangleBorder.top + (rectangleBorder.right - rectangleClient.right));

                  ppath->add_line(rectangleBorder.right - 1, rectangleClient.bottom);

                  ppath->close_figure();

                  if (::is_item(m_pitemHover, iIndex) 
                     && !::is_element(m_pitemHover, ::e_element_close_tab_button)
                     && !::in_element_range(m_pitemHover, ::e_element_split, 100))
                  {

                     ppane->m_pbrushFillHover->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 215, 215, 210), argb(250, 235, 235, 230));

                     pgraphics->set(ppane->m_pbrushFillHover);

                     pgraphics->fill(ppath);

                     pgraphics->set(ppenBorder);

                     pgraphics->draw(ppath);

                     pgraphics->set(get_font(pstyle, e_state_hover));

                     pbrushText->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_hover));

                  }
                  else
                  {

                     ppane->m_pbrushFill->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 175, 175, 170), argb(250, 195, 195, 190));

                     pgraphics->set(ppane->m_pbrushFill);

                     pgraphics->fill(ppath);

                     ppenBorder->create_solid(1.0, get_color(pstyle, ::e_element_border, ::user::e_state_selected));

                     pgraphics->set(ppenBorder);

                     pgraphics->draw(ppath);

                     pgraphics->set(get_font(pstyle));

                     pbrushText->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));

                  }

               }

            }

         }

         if (true)
         {

            __pointer(::base::style) pbasestyle = pstyle;

            if (pbasestyle && get_element_rect(iIndex, rectangleText, ::e_element_text))
            {

               pbasestyle->_001OnTabPaneDrawTitle(*ppane, this, pgraphics, rectangleText, pbrushText, estate);

            }

         }

         if (true)
         {

            if (get_element_rect(iIndex, rectangleClose, ::e_element_close_tab_button))
            {

               pgraphics->set(get_font(pstyle, e_element_close_tab_button));

               if (::is_item(m_pitemHover, iIndex) && ::is_element(m_pitemHover, ::e_element_close_tab_button))
               {

                  pbrushText = get_data()->m_pbrushCloseHover;

               }
               else
               {

                  pbrushText = get_data()->m_pbrushClose;

               }

               pgraphics->set(pbrushText);

               pgraphics->draw_text("x", rectangleClose, e_align_center);

            }

         }

      }

   }


   void tab::_001OnDrawStandard(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangle;
      ::rectangle_i32 rectangleBorder;
      ::rectangle_i32 rectangleText;
      ::rectangle_i32 rectangleClient;
      ::rectangle_i32 rectangleIcon;
      ::rectangle_i32 rectangleClose;

      auto pstyle = get_style(pgraphics);

      get_data()->m_ppen->create_solid(1,rgb(32,32,32));

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->fill_rectangle(get_data()->m_rectangleTab, argb(0xc0, 250, 255, 255));

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

      ::index iVisiblePane = 0;

      auto pbrushText = __create < ::draw2d::brush > ();

      for(i32 iIndex = 0; iIndex < get_data()->m_tabpanecompositea.get_size(); iIndex++)
      {

         auto ppane = get_data()->m_tabpanecompositea[iIndex].get();

         if (!ppane->m_bTabPaneVisible)
         {

            continue;

         }



         if(!get_element_rect(iVisiblePane, rectangle, e_element_tab))
            continue;

         if (!get_element_rect(iVisiblePane, rectangleBorder, e_element_border))
         {

            continue;

         }

         if (!get_element_rect(iVisiblePane, rectangleClient, e_element_client))
         {

            continue;

         }

         if(get_data()->m_bVertical)
         {

            if(get_element_rect(iVisiblePane, rectangleIcon, e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               image_source imagesource(ppane->m_pimage);

               image_drawing_options imagedrawingoptions(rectangleIcon);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

            if(get_data()->m_idaSel.contains(iIndex))
            {

               auto ppen = __create < ::draw2d::pen > ();

               ppen->create_solid(1.0, argb(255, 0, 0, 0));

               pgraphics->set(ppen);

               pgraphics->set_current_point(rectangleBorder.right, rectangleBorder.bottom);
               pgraphics->line_to(rectangleBorder.left + 1, rectangleBorder.bottom);
               pgraphics->line_to(rectangleBorder.left, rectangleBorder.top - (rectangleBorder.left - rectangleClient.left));
               pgraphics->line_to(rectangleClient.left, rectangleBorder.top);
               pgraphics->line_to(rectangleBorder.right, rectangleBorder.top);

               auto pstyle = get_style(pgraphics);

               pgraphics->set(get_font(pstyle, e_state_selected));

               pbrushText->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));

            }
            else
            {

               auto ppen = __create < ::draw2d::pen > ();

               ppen->create_solid(1.0, argb(255, 0, 0, 0));

               pgraphics->set(ppen);

               pgraphics->set_current_point(rectangleBorder.right, rectangleBorder.bottom);
               pgraphics->line_to(rectangleBorder.left + 1, rectangleBorder.bottom);
               pgraphics->line_to(rectangleBorder.left, rectangleBorder.top - (rectangleBorder.left - rectangleClient.left));
               pgraphics->line_to(rectangleText.left, rectangleBorder.top);
               pgraphics->line_to(rectangleBorder.right, rectangleBorder.top);
               pgraphics->line_to(rectangleBorder.right, rectangleBorder.bottom);

               if(::is_item(m_pitemHover, iVisiblePane) && !::is_element(m_pitemHover, e_element_close_tab_button))
               {

                  auto pstyle = get_style(pgraphics);

                  pgraphics->set(get_font(pstyle, e_state_hover));

                  pbrushText = get_data()->m_pbrushClose;

               }
               else
               {

                  auto pstyle = get_style(pgraphics);

                  pgraphics->set(get_font(pstyle, e_state_hover));

                  pbrushText->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_hover));


               }

            }

         }
         else
         {

            if(get_element_rect(iVisiblePane, rectangleIcon, e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               image_source imagesource(ppane->m_pimage);

               image_drawing_options imagedrawingoptions(rectangleIcon);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

            if(get_data()->m_idaSel.contains(ppane->m_atom))
            {

               auto ppen = __create < ::draw2d::pen > ();

               ppen->create_solid(1.0, argb(255, 0, 0, 0));

               pgraphics->set(ppen);

               pgraphics->set_current_point(rectangleBorder.left, rectangleClient.bottom);
               pgraphics->line_to(rectangleBorder.left, rectangleBorder.top);
               pgraphics->line_to(rectangleClient.right, rectangleBorder.top);
               pgraphics->line_to(rectangleBorder.right, rectangleBorder.top + (rectangleBorder.right - rectangleClient.right));
               pgraphics->line_to(rectangleBorder.right - 1, rectangleClient.bottom);

               auto pstyle = get_style(pgraphics);

               pgraphics->set(get_font(pstyle, e_state_selected));

               pbrushText->create_solid(argb(255, 0, 0, 0));

            }
            else
            {

               auto ppen = __create < ::draw2d::pen > ();

               ppen->create_solid(1.0, argb(255, 0, 0, 0));

               pgraphics->set(ppen);

               pgraphics->set_current_point(rectangleBorder.left, rectangleClient.bottom);
               pgraphics->line_to(rectangleBorder.left, rectangleBorder.top);
               pgraphics->line_to(rectangleClient.right, rectangleBorder.top);
               pgraphics->line_to(rectangleBorder.right, rectangleBorder.top + (rectangleBorder.right - rectangleClient.right));
               pgraphics->line_to(rectangleBorder.right - 1, rectangleClient.bottom);
               pgraphics->line_to(rectangleBorder.left, rectangleClient.bottom);

               if (::is_item(m_pitemHover, iVisiblePane) && !::is_element(m_pitemHover, e_element_close_tab_button))
               {

                  pgraphics->set(get_font(pstyle, e_state_hover));

                  pbrushText->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_hover));

               }
               else
               {

                  pgraphics->set(get_font(pstyle));

                  pbrushText->create_solid(get_color(pstyle, ::e_element_item_text));

               }

            }

         }

         if (get_element_rect(iVisiblePane, rectangleText, e_element_text))
         {

            pgraphics->set(pbrushText);

            pgraphics->_DrawText(ppane->get_title(), rectangleText, e_align_bottom_left);

         }

         if (get_element_rect(iVisiblePane, rectangleClose, e_element_close_tab_button))
         {

            pgraphics->set(get_font(pstyle, e_element_close_tab_button));

            if (::is_item(m_pitemHover, iVisiblePane)  && ::is_element(m_pitemHover, e_element_close_tab_button))
            {

               pbrushText = get_data()->m_pbrushCloseSel;

               pbrushText->create_solid(argb(0xff, 255, 127, 0));

            }
            else
            {

               pbrushText->create_solid(argb(0xff, 0, 0, 0));

            }

            pgraphics->set(pbrushText);

            pgraphics->draw_text("x", rectangleClose, e_align_center);

         }

         iVisiblePane++;

      }

   }


   void tab::get_title(int iIndex, string_array & stra)
   {

      auto ppane = get_data()->m_tabpanecompositea[iIndex].get();

      stra = ppane->m_straTitle;

   }


   void tab::GetTabClientRect(RECTANGLE_I32 * prectangle)

   {

      *prectangle = get_data()->m_rectangleTabClient;


   }


   void tab::GetTabClientRect(RECTANGLE_I64 * prectangle)

   {

      ::rectangle_i32 rectangleClient;
      get_client_rect(rectangleClient);
      rectangle_i64 rectangle_i64(rectangleClient);
      *prectangle = rectangle_i64;


   }


   void tab::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = get_client_rect();

      if(!rectangleClient)
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

         get_data()->m_rectangleMargin.set(2, 3, 1, 0);

         get_data()->m_rectangleBorder.set(11, 1, 6, 0);

         get_data()->m_rectangleTextMargin.set(3, 0, 1, 0);

         get_data()->m_iTabHeight += get_data()->m_rectangleBorder.top + get_data()->m_rectangleBorder.bottom +
                                     get_data()->m_rectangleMargin.top + get_data()->m_rectangleMargin.bottom;

         get_data()->m_iTabWidth += get_data()->m_rectangleBorder.left + get_data()->m_rectangleBorder.right +
                                    get_data()->m_rectangleMargin.left + get_data()->m_rectangleMargin.right;

      }
      else
      {

         get_data()->m_rectangleMargin.set(3, 2, 0, 1);

         get_data()->m_rectangleBorder.set(0, 1, 11, 6);

         get_data()->m_rectangleTextMargin.set(3, 0, 1, 0);

         get_data()->m_iTabHeight += get_data()->m_rectangleBorder.top + get_data()->m_rectangleBorder.bottom +
                                     get_data()->m_rectangleMargin.top + get_data()->m_rectangleMargin.bottom;

         get_data()->m_iTabWidth += get_data()->m_rectangleBorder.left + get_data()->m_rectangleBorder.right +
                                    get_data()->m_rectangleMargin.left + get_data()->m_rectangleMargin.right;

      }

      defer_handle_auto_hide_tabs(false);

      pgraphics->set(get_font(pstyle, e_element_close_tab_button));

      m_dcextension.get_text_extent(pgraphics,MAGIC_PALACE_TAB_SIZE,get_data()->m_sizeSep);

      if(get_data()->m_bVertical)
      {

         i32 iTabWidth = 16;

         i32 iTabHeight = 8;

         i32 cx;

         i32 cy;

         for(i32 iIndex = 0; iIndex < get_data()->m_tabpanecompositea.get_size(); iIndex++)
         {

            auto ppane = get_data()->m_tabpanecompositea[iIndex].get();

            if (!ppane->m_bTabPaneVisible)
            {

               continue;

            }

            string str = ppane->get_title();

            ppane->do_split_layout(m_dcextension, pgraphics);

            ::size_i32 size;

            m_dcextension.get_text_extent(pgraphics, str, size);

            if(ppane->m_pimage->is_set())
            {

               size.cx += ppane->m_pimage->width()+ 2;

               size.cy = maximum(size.cy, ppane->m_pimage->height());

            }

            cx = size.cx + 2;

            if(!ppane->m_bPermanent)
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

         iTabWidth += get_data()->m_rectangleBorder.left + get_data()->m_rectangleBorder.right +
                      get_data()->m_rectangleMargin.left + get_data()->m_rectangleMargin.right +
                      get_data()->m_rectangleTextMargin.left + get_data()->m_rectangleTextMargin.right;

         get_data()->m_iTabWidth = iTabWidth;

         iTabHeight += get_data()->m_rectangleBorder.top + get_data()->m_rectangleBorder.bottom +
                       get_data()->m_rectangleMargin.top + get_data()->m_rectangleMargin.bottom +
                       get_data()->m_rectangleTextMargin.top + get_data()->m_rectangleTextMargin.bottom;

         get_data()->m_iTabHeight = iTabHeight;

         //::rectangle_i32 rectangleClient;

         //get_client_rect(rectangleClient);

         get_data()->m_rectangleTab.left       = rectangleClient.left;
         get_data()->m_rectangleTab.top        = rectangleClient.top;
         get_data()->m_rectangleTab.right      = get_data()->m_rectangleTab.left + get_data()->m_iTabWidth;
         get_data()->m_rectangleTab.bottom     = rectangleClient.bottom;

         get_data()->m_rectangleTabClient.left       = m_bShowTabs ? get_data()->m_rectangleTab.right : rectangleClient.left;
         get_data()->m_rectangleTabClient.top        = get_data()->m_rectangleTab.top;
         get_data()->m_rectangleTabClient.right      = rectangleClient.right;
         get_data()->m_rectangleTabClient.bottom     = get_data()->m_rectangleTab.bottom;

      }
      else
      {

         i32 iTabHeight = 16;

         i32 cy;

         pgraphics->set(get_font(pstyle, e_state_selected));

//         ::rectangle_i32 rectangleClient;

//         get_client_rect(rectangleClient);

         int x = rectangleClient.left;

         i32 ixAdd;

         for(i32 iIndex = 0; iIndex < get_data()->m_tabpanecompositea.get_size(); iIndex++)
         {

            auto ppane = get_data()->m_tabpanecompositea[iIndex].get();

            if (!ppane->m_bTabPaneVisible)
            {

               return;

            }

            string str = ppane->get_title();

            ppane->do_split_layout(m_dcextension,pgraphics);

            ::size_i32 size;

            m_dcextension.get_text_extent(pgraphics, str, size);

            if(ppane->m_pimage->is_ok())
            {

               size.cy = maximum(size.cy, ppane->m_pimage->size().cy);

            }

            cy = size.cy + 2;

            if(cy > iTabHeight)
            {

               iTabHeight = cy;

            }

            ppane->m_point.x = x;

            ppane->m_point.y = rectangleClient.top;

            ixAdd = 5;

            if (ppane->m_pimage->is_set())
            {

               ixAdd += ppane->m_pimage->width() + 2;

            }

            if (!ppane->m_bPermanent)
            {

               ixAdd += 2 + 16 + 2;

            }

            ppane->m_size.cx = size.cx + ixAdd
                                 + get_data()->m_rectangleBorder.left + get_data()->m_rectangleBorder.right
                                 + get_data()->m_rectangleMargin.left + get_data()->m_rectangleMargin.right
                                 + get_data()->m_rectangleTextMargin.left + get_data()->m_rectangleTextMargin.right;

            x += ppane->m_size.cx;
         }

         // close tab button
         cy = 2 + 16 + 2;
         if(cy > iTabHeight)
         {
            iTabHeight = cy;
         }

         iTabHeight += get_data()->m_rectangleBorder.top + get_data()->m_rectangleBorder.bottom +
                       get_data()->m_rectangleMargin.top + get_data()->m_rectangleMargin.bottom + get_data()->m_iHeightAddUp;

         get_data()->m_iTabHeight = iTabHeight;

         for (i32 iIndex = 0; iIndex < get_data()->m_tabpanecompositea.get_size(); iIndex++)
         {

            auto ppane = get_data()->m_tabpanecompositea[iIndex].get();

            ppane->m_size.cy = iTabHeight;

         }




         get_data()->m_rectangleTab.left       = rectangleClient.left;
         get_data()->m_rectangleTab.top        = rectangleClient.top;
         get_data()->m_rectangleTab.right      = rectangleClient.right;
         get_data()->m_rectangleTab.bottom     = get_data()->m_rectangleTab.top + get_data()->m_iTabHeight;

         ::rectangle_i32 & rectangleTabClient = get_data()->m_rectangleTabClient;

         bool bTabbedClient = m_bShowTabs;

         rectangleTabClient.left       = get_data()->m_rectangleTab.left;
         rectangleTabClient.top        = bTabbedClient ? get_data()->m_rectangleTab.bottom : rectangleClient.top;
         rectangleTabClient.right      = get_data()->m_rectangleTab.right;
         rectangleTabClient.bottom     = rectangleClient.bottom;

         //TRACE0("rectangleTabClient");
      }

      {

//               ::u32 dwTime2= ::duration::now();

         //FORMATTED_TRACE("message_handler call time0= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
         //FORMATTED_TRACE("usertab::on_layout call time2= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
      }


      for(i32 iIndex = 0; iIndex < get_data()->m_tabpanecompositea.get_size(); iIndex++)
      {

         if(iIndex != get_current_tab_index())
         {

            layout_pane(iIndex);

         }

      }

      layout_pane(get_current_tab_index(), is_window_visible());

      if(m_pdata->m_bVertical)
      {

         m_iTabSize = (int) m_pdata->m_tabpanecompositea.get_count() * m_pdata->m_iTabHeight;

         m_iTabScrollMax = m_iTabSize - rectangleClient.height();

      }
      else
      {

         m_iTabSize = m_pdata->m_tabpanecompositea.last()->m_point.x +
         m_pdata->m_tabpanecompositea.last()->m_size.cx;

         m_iTabScrollMax = m_iTabSize - rectangleClient.width();

      }


   }


   void tab::layout_pane(index iIndex, bool bDisplay)
   {

      auto ppane = get_tab(iIndex);

      if (::is_null(ppane))
      {

         return;

      }

      auto ppaneSel = get_tab(get_current_tab_index());

      if (::is_null(ppane))
      {

         return;

      }

      auto pholder = ppane->m_pplaceholder;

      if(pholder.is_null())
      {

         return;

      }

      ::rectangle_i32 rectangleChild;

      GetTabClientRect(rectangleChild);

      ::rectangle_i32 rectangleWindow;

      pholder->get_window_rect(rectangleWindow);

      screen_to_client(rectangleWindow);

      if(bDisplay && iIndex == get_current_tab_index())
      {

         pholder->order(e_zorder_top);

      }

      pholder->place(rectangleChild);

      if (bDisplay)
      {

         pholder->display(::e_display_normal);

         pholder->set_need_layout();

         pholder->set_need_redraw();

         pholder->post_redraw();

      }
      else if(::is_set(ppaneSel) && ppaneSel->m_eflag.has(e_flag_hide_all_others_on_show))
      {

         pholder->hide();

      }

   }


   void tab::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      pmouse->previous();

      m_pitemClick = hit_test(pmouse);

      get_data()->m_bDrag = false;

      get_data()->m_iClickTab = -1;

      m_pointLeftButtonDown = pmouse->m_point;

      m_bMouseDown = true;

      if(::is_element(m_pitemClick, e_element_tab_near_scroll))
      {

         if(m_iTabScroll > 0)
         {

            m_iTabScroll--;

            set_need_redraw();

            post_redraw();

            pmouse->m_bRet = true;

            set_mouse_capture();

            return;

         }

      }
      else if(::is_element(m_pitemClick, e_element_tab_far_scroll))
      {

         if(m_iTabScroll < m_iTabScrollMax)
         {

            m_iTabScroll++;

            set_need_redraw();

            post_redraw();

            pmouse->m_bRet = true;

            set_mouse_capture();

            return;

         }

      }

      if(::is_set(m_pitemClick) && m_pitemClick->m_iItem >= 0)
      {

         index iIndex = get_current_tab_index();

         if(::is_element(m_pitemClick, e_element_close_tab_button))
         {

            get_data()->m_iClickTab = m_pitemClick->m_iItem;

            pmouse->m_bRet = true;

            pmouse->m_lresult = 1;

            m_estate = state_close_button_down;

         }
         else if(m_pitemClick->m_iItem != iIndex)
         {

            get_data()->m_iClickTab = m_pitemClick->m_iItem;

            //set_mouse_capture();

            //SetTimer(e_timer_drag_start, 300, nullptr);

            //g_tickDragStart.Now();

            pmouse->m_bRet = true;

            pmouse->m_lresult = 1;

            m_estate = state_other_tab_button_down;

         }

      }

   }


   void tab::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if(m_bMouseDown)
      {

         m_bMouseDown = false;

         auto psession = get_session();

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         pwindowing->release_mouse_capture();

      }

      if (m_bTabScrollingActive)
      {

         pmouse->m_bRet = true;

         pmouse->m_lresult = 1;

         m_bTabScrollingActive = false;

         return;

      }

      auto pitem = hit_test(pmouse);

      index iClickTab = get_data()->m_iClickTab;

      if (m_estate == state_other_tab_button_down)
      {

         // drag operation was about to start (but ended prematurely)

         auto psession = get_session();

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         pwindowing->release_mouse_capture();

         KillTimer(e_timer_drag_start);

      }

      if (::is_set(pitem))
      {

         if (pitem->m_iItem >= 0 && iClickTab == pitem->m_iItem && ::is_same_item(m_pitemClick, pitem))
         {

            if (::is_element(pitem, e_element_close_tab_button))
            {

               _001OnTabClose(pitem->m_iItem);

            }
            else
            {

               _001OnTabClick(pitem->m_iItem);

            }

            set_need_redraw();

            post_redraw();

            pmouse->m_bRet = true;

            pmouse->m_lresult = 1;

         }

      }

      get_data()->m_iClickTab = -1;

      get_data()->m_bDrag = false;

   }


   void tab::on_message_mouse_move(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if(m_bMouseDown)
      {

         if (window()->windowing()->is_sandboxed())
         {

            m_bTabScrollingActive = true;

            int iOffset = m_pointLeftButtonDown.x - pmouse->m_point.x;

            auto iTabScroll = minimum_maximum(m_iTabScroll + iOffset, 0, m_iTabScrollMax);

            if (iTabScroll != m_iTabScroll)
            {

               m_iTabScroll = iTabScroll;

               set_need_redraw();

               post_redraw();

            }

            pmouse->m_bRet = true;

            return;


         }
         else
         {
            if (::is_element(m_pitemClick, e_element_tab_far_scroll))
            {

               if (m_iTabScroll < m_iTabScrollMax)
               {

                  m_iTabScroll++;

                  set_need_redraw();

                  post_redraw();

                  pmouse->m_bRet = true;

                  return;

               }

            }
            else if (::is_element(m_pitemClick, e_element_tab_near_scroll))
            {

               if (m_iTabScroll > 0)
               {

                  m_iTabScroll--;

                  set_need_redraw();

                  post_redraw();

                  pmouse->m_bRet = true;

                  return;

               }

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


   void tab::on_message_mouse_leave(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);
      //__pointer(::user::message) pusermessage(pmessage);

   }


   bool tab::has_tab_scrolling() const
   {

      return m_iTabScrollMax > 0;

   }


   bool tab::get_element_rect(::index iIndex, RECTANGLE_I32 * prectangle, enum_element eelement)
   {

      point_i32 ptOffset(0,0);

      if(has_tab_scrolling())
      {

         float fDensity = 1.0f;

         if (!window()->windowing()->is_sandboxed())
         {

            if (eelement == e_element_tab_near_scroll)
            {

               if (get_data()->m_bVertical)
               {

                  ::rectangle_i32 rectangle = get_data()->m_rectangleTab;

                  prectangle->left = rectangle.left;

                  prectangle->top = rectangle.top;

                  prectangle->right = rectangle.right;

                  fDensity = window()->get_density_for_window();

                  prectangle->bottom = rectangle.top + (::i32)(8.0f * fDensity);

               }
               else
               {

                  ::rectangle_i32 rectangle = get_data()->m_rectangleTab;

                  prectangle->left = rectangle.left;

                  prectangle->top = rectangle.top;

                  fDensity = window()->get_density_for_window();

                  prectangle->right = rectangle.left + (::i32)(8.0f * fDensity);

                  prectangle->bottom = rectangle.bottom;

               }

               return true;

            }
            else if (eelement == e_element_tab_far_scroll)
            {

               if (get_data()->m_bVertical)
               {

                  ::rectangle_i32 rectangle = get_data()->m_rectangleTab;

                  prectangle->left = rectangle.left;

                  fDensity = window()->get_density_for_window();

                  prectangle->top = rectangle.bottom - (::i32)(8.0f * fDensity);

                  prectangle->right = rectangle.right;

                  prectangle->bottom = rectangle.bottom;

               }
               else
               {

                  ::rectangle_i32 rectangle = get_data()->m_rectangleTab;

                  fDensity = window()->get_density_for_window();

                  prectangle->left = rectangle.right - (::i32)(8.0f * fDensity);

                  prectangle->top = rectangle.top;

                  prectangle->right = rectangle.right;

                  prectangle->bottom = rectangle.bottom;

               }

               return true;

            }

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

      if (iIndex < 0)
      {

         return false;

      }

      ///auto ptabpane = get_tab(iIndex);

      if(eelement == e_element_border)
      {

         if (!get_element_rect(iIndex, prectangle, e_element_tab))

         {

            return false;

         }

         ::rect_deflate(prectangle, &get_data()->m_rectangleMargin);

         //::OffsetRect(prectangle, ptOffset.x, ptOffset.y);

         return true;

      }

      if(eelement == e_element_client)
      {

         if (!get_element_rect(iIndex, prectangle, e_element_border))
         {

            return false;

         }

         ::rect_deflate(prectangle, &get_data()->m_rectangleBorder);

         //::OffsetRect(prectangle, ptOffset.x, ptOffset.y);

         return true;

      }

      if(eelement == e_element_icon)
      {

         if (::not_ok(get_data()->m_tabpanecompositea[iIndex]->m_pimage))
         {

            return false;

         }

         if (!get_element_rect(iIndex, prectangle, e_element_client))
         {

            return false;

         }

         prectangle->right = prectangle->left + get_data()->m_tabpanecompositea[iIndex]->m_pimage->width();

         prectangle->bottom = prectangle->top + get_data()->m_tabpanecompositea[iIndex]->m_pimage->height();

         //::OffsetRect(prectangle, ptOffset.x, ptOffset.y);

         return true;

      }
      else if(eelement == e_element_text)
      {

         if (!get_element_rect(iIndex, prectangle, e_element_client))
         {

            return false;

         }

         if(::is_ok(get_data()->m_tabpanecompositea[iIndex]->m_pimage))
         {

            prectangle->left += get_data()->m_tabpanecompositea[iIndex]->m_pimage->width() + 2;


         }

         if(!get_data()->m_tabpanecompositea[iIndex]->m_bPermanent)
         {

            prectangle->right -= 2 + 16 + 2;

         }

         ::rect_deflate(prectangle, &get_data()->m_rectangleTextMargin);

         //::offset_rect(prectangle, ptOffset.x, ptOffset.y);

         return true;

      }
      else if(eelement == e_element_close_tab_button)
      {

         if (iIndex < 0)
         {

            return false;

         }

         if (get_data()->m_tabpanecompositea[iIndex]->m_bPermanent)
         {

            return false;

         }

         if (get_data()->get_visible_tab_count() <= 1 && !get_data()->m_bEnableCloseAll)
         {

            return false;

         }

         if (!get_element_rect(iIndex, prectangle, e_element_client))
         {

            return false;

         }

         prectangle->right  = prectangle->right;


         prectangle->left   = prectangle->right - 20;


         prectangle->top    = prectangle->bottom - 20;


         //::OffsetRect(prectangle, ptOffset.x, ptOffset.y);


         return true;

      }

      if (eelement != e_element_tab)
      {

         return false;

      }

      if(get_data()->m_bVertical)
      {

         ::rectangle_i32 rectangle = get_data()->m_rectangleTab;

         rectangle.bottom = rectangle.top;

         prectangle->left   = rectangle.left;

         prectangle->top    = (::i32) (rectangle.top +  iIndex * get_data()->m_iTabHeight);

         prectangle->right  = rectangle.right;

         prectangle->bottom = prectangle->top + get_data()->m_iTabHeight;

      }
      else
      {

         auto ppane = get_data()->m_tabpanecompositea[iIndex].get();

         prectangle->left = ppane->m_point.x;

         prectangle->top = ppane->m_point.y;

         prectangle->right = ppane->m_point.x + ppane->m_size.cx;

         prectangle->bottom = ppane->m_point.y + ppane->m_size.cy;

      }

      ::offset_rect(prectangle, ptOffset.x, ptOffset.y);

      return true;

   }


   ::count tab::get_tab_count()
   {

      return get_data()->m_tabpanecompositea.get_size();

   }


   ::count tab::get_visible_tab_count()
   {

      return get_data()->m_tabpanecompositea.predicate_get_count([](auto & pane) {return pane->m_bTabPaneVisible; });

   }


   index tab::find_child_pane(::user::interaction * pinteraction)
   {

      index iIndex = get_data()->m_tabpanecompositea.predicate_find_first([=](auto & pane)
      {

         return pane->m_pplaceholder && pane->m_pplaceholder->is_ascendant_of(pinteraction, true);

      });

      return iIndex;

   }


   void tab::defer_erase_child_pane(::user::interaction * pinteraction)
   {

      synchronous_lock synchronouslock(mutex());

      index iIndex = find_child_pane(pinteraction);

      if (iIndex >= 0)
      {

         erase_tab(iIndex, false);

      }

   }


   void tab::on_erase_child(::user::interaction * pinteraction)
   {

      defer_erase_child_pane(pinteraction);

   }


   void tab::on_erase_place_holder_child(::user::interaction * pinteraction)
   {

      defer_erase_child_pane(pinteraction);

   }


   void tab::on_hide_child(::user::interaction * pinteraction)
   {

      //__pointer(::user::interaction) pupdown = pinteraction;

      //if (pupdown.is_set()
      //      && pupdown->m_eupdown != updown_normal_frame
      //      && pupdown->m_eupdown != updown_none)
      //{

      //   defer_erase_child_pane(pinteraction);

      //}

   }


   void tab::on_hide_place_holder_child(::user::interaction * pinteraction)
   {

      //__pointer(::user::interaction) pupdown = pinteraction;

      //if (pupdown.is_set()
      //      && pupdown->m_eupdown != updown_normal_frame
      //      && pupdown->m_eupdown != updown_none)
      //{

      //   defer_erase_child_pane(pinteraction);

      //}

   }


   ::item_pointer tab::on_hit_test(const ::point_i32 &point)
   {

      synchronous_lock synchronouslock(mutex());

      ::rectangle_i32 rectangleScroll;

      bool bScroll = has_tab_scrolling();

      if(bScroll)
      {

         if (window()->windowing()->is_sandboxed())
         {

         }
         else
         {

            if (get_element_rect(-1, rectangleScroll, ::e_element_tab_near_scroll))
            {

               if (rectangleScroll.contains(point))
               {

                  return __new(::item(::e_element_tab_near_scroll, -1));

               }

            }

            if (get_element_rect(-1, rectangleScroll, ::e_element_tab_far_scroll))
            {

               if (rectangleScroll.contains(point))
               {

                  return __new(::item(::e_element_tab_far_scroll, -1));

               }

            }

         }

      }

      ::rectangle_i32 rectangle;

      for(i32 iIndex = 0; iIndex < get_data()->m_tabpanecompositea.get_size(); iIndex++)
      {

         auto ppane = get_data()->m_tabpanecompositea[iIndex].get();

         if(ppane->m_straTitle.get_size() > 1)
         {

            ::rectangle_i32 rectangleText;

            if(get_element_rect(iIndex, rectangleText, e_element_text))
            {

               if(rectangleText.contains(point))
               {

                  for(int iTitle = 0; iTitle < ppane->m_straTitle.get_size(); iTitle++)
                  {

                     rectangleText.left += ppane->m_sizeaText[iTitle].cx;

                     rectangleText.right = rectangleText.left + get_data()->m_sizeSep.cx;

                     if(rectangleText.contains(point))
                     {

                        return __new(::item((enum_element)((int)e_element_split + iTitle), iIndex ));

                     }

                     rectangleText.left += get_data()->m_sizeSep.cx;

                  }

               }

            }

         }

         if(get_element_rect(iIndex, rectangle, e_element_close_tab_button) )
         {

            if(rectangle.contains(point))
            {

               return __new(::item(e_element_close_tab_button, iIndex));

            }

         }

         if(get_element_rect(iIndex, rectangle, e_element_tab))
         {

            if(rectangle.contains(point))
            {

               return __new(::item(e_element_tab, iIndex));

            }

         }

      }

      return nullptr;

   }


   ::user::interaction * tab::GetNotifyWnd()
   {

#ifdef _UWP

      return nullptr;

#else

      ::user::interaction * puserinteraction;

      if ((puserinteraction = get_parent()->get_wnd()) != nullptr)
      {

         return puserinteraction;

      }

      return nullptr;

#endif

   }

   /*
   bool tab::create(::user::interaction * pchannel, ::u32 uId)
   {
      if(!m_puserinteraction->create(
         pchannel,
         uId))
         return false;
      m_bCreated = true;
      on_layout(pgraphics);
      return true;
   }
   */

   void tab::on_message_create(::message::message * pmessage)
   {

      auto psystem = m_psystem->m_pbasesystem;

      m_bNoTabs = psystem->has_property("no_tabs");

      __pointer(::user::message) pusermessage(pmessage);

      if(pmessage->previous())
         return;

      auto psession = get_session()->m_paurasession;

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pcursor = pwindowing->get_cursor(e_cursor_arrow);

      set_mouse_cursor(pcursor);

      __construct_new(get_data()->m_pimagelist);

      get_data()->m_pimagelist->create(16, 16, 0, 0, 16);

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics(this);

      get_data()->m_bCreated = true;

      pusermessage->m_lresult = 0;

      SetTimer(e_timer_defer_handle_auto_hide_tabs, 300_ms);

      //post_message(WM_USER + 1342);

      if (m_bAutoCreateTabsOnCreate)
      {

         create_tabs();

      }

   }


   void tab::on_create_tabs()
   {

      auto pextendedtopic = create_extended_topic(::id_on_create_tab);

      pextendedtopic->m_puserelement = this;

      pextendedtopic->m_ptab = this;

      route(pextendedtopic);

   }


   ::count tab::restore_tabs()
   {

      ::count c = 0;

      __keep(m_bDisableSavingRestorableTabs);

      if(get_data()->m_matchanyRestore.m_itema.get_count() > 0)
      {

         ::payload payload;

         //if(data_get("restore_tab",::payload))
         //{

         //   c = open_tabs(payload.payloada());

         //}

      }

      return c;

   }


   void tab::install_message_routing(::channel *pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      //install_hover_default_mouse_handling(pchannel);

      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &tab::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &tab::on_message_left_button_up);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &tab::on_message_mouse_move);
      MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &tab::on_message_mouse_leave);
      MESSAGE_LINK(e_message_create, pchannel, this, &tab::on_message_create);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &tab::on_message_show_window);
      MESSAGE_LINK(e_message_language, pchannel, this, &tab::_001OnAppLanguage);
      MESSAGE_LINK(message_start_tab_drag, pchannel, this,&tab::_001OnStartTabDrag);

      ////MESSAGE_LINK(e_message_timer, pchannel, this, &tab::_001OnTimer);

   }


   void tab::set_current_tab_by_index(::index iIndex)
   {

      synchronous_lock lock(get_data()->mutex());

      get_data()->m_idaSel.erase_all();

      atom idTab = index_id(iIndex);

      if (!idTab.is_empty())
      {

         get_data()->m_idaSel.add(idTab);

      }

      on_change_cur_sel();

   }


   ::index tab::tab_index(::user::tab_pane* ptabpaneFind)
   {

      if (::is_null(ptabpaneFind))
      {

         return -1;

      }

      auto pdata = get_data();

      synchronous_lock lock(pdata->mutex());

      return pdata->m_tabpanecompositea.predicate_find_first([ptabpaneFind](auto& ptabpane)
         {

            return ptabpane == ptabpaneFind;

         });

   }


   ::index tab::visible_index_index(::index iVisibleIndex)
   {

      if (iVisibleIndex < 0)
      {

         return -1;

      }

      auto pdata = get_data();

      synchronous_lock lock(pdata->mutex());

      return pdata->m_tabpanecompositea.predicate_index_index(iVisibleIndex, [](auto & ptabpane)
         {

            return ptabpane->m_bTabPaneVisible;

         });

   }


   ::index tab::index_visible_index(::index iIndex)
   {

      if (iIndex < 0)
      {

         return -1;

      }

      auto pdata = get_data();

      synchronous_lock lock(pdata->mutex());

      return pdata->m_tabpanecompositea.index_predicate_index(iIndex, [](auto& ptabpane)
         {

            return ptabpane->m_bTabPaneVisible;

         });

   }


   ::index tab::id_index(const ::atom& atom)
   {

      auto pdata = get_data();

      synchronous_lock lock(pdata->mutex());

      return pdata->m_tabpanecompositea.predicate_find_first([atom](auto& ptabpane)
         {

            return ptabpane->m_atom == atom;

         });


   }


   ::atom tab::index_id(::index iIndex)
   {

      auto pdata = get_data();

      synchronous_lock lock(pdata->mutex());

      if (iIndex < 0 || iIndex >= pdata->m_tabpanecompositea.get_count())
      {

         return -1;

      }

      auto ppane = pdata->m_tabpanecompositea[iIndex];

      if (!ppane)
      {

         return -1;

      }

      return ppane->m_atom;

   }

   
   ::index tab::id_visible_index(const ::atom& atom)
   {

      auto iIndex = id_index(atom);

      auto iVisibleIndex = index_visible_index(iIndex);

      return iVisibleIndex;

   }


   ::atom tab::visible_index_id(::index iVisibleIndex)
   {

      auto iIndex = visible_index_index(iVisibleIndex);

      auto atom = index_id(iIndex);

      return atom;

   }


   void tab::_001OnAppLanguage(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

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


   ::index tab::get_current_tab_index()
   {

      if(get_data()->m_idaSel.get_size() == 1)
      {

         return id_index(get_data()->m_idaSel[0]);

      }
      else
      {

         return -1;

      }

   }


   ::index tab::get_current_visible_tab_index()
   {

      auto iIndex = get_current_tab_index();

      if (iIndex)
      {

         return -1;

      }

      auto iVisibleIndex = index_visible_index(iIndex);

      return iVisibleIndex;

   }


   bool tab::_001IsAddTab(::index iIndex)
   {

      if(get_data()->m_pcallback != nullptr)
      {

         return get_data()->m_pcallback->_001IsAddTab(this, iIndex);

      }
      else
      {

         return false;

      }

   }


   void tab::_001OnTabClick(::index iIndex)
   {

      if(get_data()->m_pcallback != nullptr)
      {

         get_data()->m_pcallback->_001OnTabClick(this, iIndex);

      }
      else
      {

         set_current_tab_by_index(iIndex);

      }

   }


   void tab::_001OnTabClose(::index iIndex)
   {

      if(get_data()->m_pcallback != nullptr)
      {

         get_data()->m_pcallback->_001OnTabClose(this, iIndex);

      }
      else
      {

         _001CloseTab(iIndex);

      }

   }


   bool tab::show_tab_by_id(const ::atom & atom, bool bShow)
   {

      auto ppane = get_tab_by_id(atom);

      if (ppane == nullptr)
      {

         return false;

      }

      ppane->m_bTabPaneVisible = bShow;

      set_need_layout();

      return true;

   }


   bool tab::show_pane(::index iIndex, bool bShow)
   {

      auto ppane = get_tab(iIndex);

      if (ppane == nullptr)
      {

         return !bShow;

      }

      ppane->m_bTabPaneVisible = bShow;

      set_need_layout();

      return true;

   }


   bool tab::hide_tab(::index iIndex)
   {

      if (iIndex < 0)
      {

         return false;

      }

      if (!show_pane(iIndex, false))
      {

         return false;

      }

      return true;

   }


   bool tab::hide_place_holder_by_id(const ::atom & atomTab)
   {

      auto ptabpane = get_tab_by_id(atomTab);

      if (::is_null(ptabpane))
      {

         return false;

      }

      auto pplaceholder = ptabpane->m_pplaceholder;

      if(::is_null(pplaceholder))
      {

         return false;

      }

      pplaceholder->hide();

      pplaceholder->set_need_redraw();

      pplaceholder->post_redraw();

      return true;

   }


   ::user::interaction * tab::tab_window(::index iIndex)
   {

      __pointer(place_holder) pholder = tab_holder(iIndex);

      if (pholder.is_null())
      {

         return nullptr;

      }

      return pholder->get_hold();

   }


   ::user::place_holder * tab::tab_holder(::index iIndex)
   {

      auto ppane = get_tab(iIndex);

      if (ppane == nullptr)
      {

         return nullptr;

      }

      return ppane->m_pplaceholder;

   }


   ::user::interaction * tab::pane_window(::index iIndex)
   {

      __pointer(place_holder) pholder = pane_holder(iIndex);

      if (pholder.is_null())
      {

         return nullptr;

      }

      return pholder->get_hold();

   }


   ::user::place_holder * tab::pane_holder(::index iIndex)
   {

      auto ppane = get_tab(iIndex);

      if (ppane == nullptr)
      {

         return nullptr;

      }

      return ppane->m_pplaceholder;

   }


   ::user::tab_pane * tab::get_tab(::index iIndex)
   {

      if (iIndex < 0)
      {

         return nullptr;

      }

      if (iIndex >= get_data()->m_tabpanecompositea.get_count())
      {

         return nullptr;

      }

      return get_data()->m_tabpanecompositea.element_at(iIndex);

   }


   ::user::tab_pane* tab::get_visible_tab(::index iVisibleIndex)
   {

      auto iIndex = visible_index_index(iVisibleIndex);

      if (iIndex < 0)
      {

         return nullptr;

      }

      auto ptabpane = get_tab(iIndex);

      return ptabpane;

   }


   //::user::tab_pane * tab::get_tab(::index iIndex)
   //{

   //   index iIndex = get_pane(iIndex);

   //   if(iIndex < 0)
   //   {

   //      return nullptr;

   //   }

   //   return get_data()->m_tabpanecompositea.element_at(iIndex);

   //}


//   void tab::set_current_tab_by_index(::index iIndex)
//   {
////      if(get_tab_holder(get_current_tab_index()) != nullptr)
//      //    {
//      //     get_tab_holder(get_current_tab_index())->display(e_display_none);
//      // }
//      set_current_tab_by_index(iIndex);
//      // if(get_tab_holder(get_current_tab_index()) != nullptr)
//      //{
//      // get_tab_holder(get_current_tab_index())->display(e_display_normal);
//      // }
//
//      //on_layout(pgraphics);
//
//   }


   void tab::on_change_cur_sel()
   {

      if(get_data()->m_pcallback != nullptr && dynamic_cast < ::user::tab * > (get_data()->m_pcallback) != this)
      {

         get_data()->m_pcallback->_001OnShowTab(this);

      }

      __pointer(::base::application) papp = get_app();

      papp->on_change_cur_sel(this);

   }


   void tab:: _001SetVertical(bool bVertical)
   {

      get_data()->m_bVertical = bVertical;

   }


   void tab::_001ConnectParent(::channel * pchannel)
   {

      __UNREFERENCED_PARAMETER(pchannel);

   }


   atom tab::get_current_tab_id()
   {

      return index_id(get_current_tab_index());

   }


   //::index tab::id_index(atom atom)
   //{

   //   index iIndex = -1;

   //   for(::index iIndex = 0; iIndex < get_data()->m_tabpanecompositea.get_size(); iIndex++)
   //   {

   //      if (get_data()->m_tabpanecompositea[iIndex]->m_bTabPaneVisible)
   //      {

   //         iIndex++;

   //      }

   //      if (get_data()->m_tabpanecompositea[iIndex]->m_atom == atom)
   //      {

   //         return iIndex;

   //      }

   //   }

   //   return -1;

   //}



   //atom tab::index_id(::index iIndex)
   //{

   //   for(i32 iIndex = 0; iIndex < get_data()->m_tabpanecompositea.get_count(); iIndex++)
   //   {

   //      if(get_data()->m_tabpanecompositea[iIndex]->m_bTabPaneVisible)
   //      {

   //         if(iIndex <= 0)
   //         {

   //            return get_data()->m_tabpanecompositea[iIndex]->m_atom;

   //         }
   //         else
   //         {

   //            iIndex--;

   //         }

   //      }

   //   }

   //   return atom();

   //}


   bool tab::set_current_tab_by_id(const ::atom & atom, ::create * pcreate)
   {

      try
      {

         if (::is_set(pcreate))
         {

            m_pusersystem->m_pcreate = pcreate;

         }

         ::index iIndex = id_index(atom);

         if(iIndex < 0)
         {

            auto ptabpane = create_tab_by_id(atom);

            if (ptabpane == nullptr)
            {

               return false;

            }

            iIndex = id_index(atom);

            if (iIndex < 0)
            {

               return false;

            }

         }

         set_current_tab_by_index(iIndex);

      }
      catch (::exit_exception * pexception)
      {

         __rethrow(pexception);

      }
      catch (const ::exception &)
      {

         return false;

      }
      catch(...)
      {

         return false;

      }

      if (::is_set(pcreate) && pcreate == m_pusersystem->m_pcreate)
      {

         m_pusersystem->m_pcreate = nullptr;

      }

      return true;

   }


   ::user::tab_pane* tab::get_current_tab()
   {

      auto atom = get_current_tab_id();

      auto ptabpane = get_tab_by_id(atom);

      if (::is_null(ptabpane))
      {

         return nullptr;

      }

      return ptabpane;

   }


   enum_position tab::DragHitTest(const ::point_i32 & point)
   {
      ::rectangle_i32 rectangle;
      GetDragRect(rectangle, e_position_top);
      if(rectangle.contains(point))
      {
         return e_position_top;
      }
      GetDragRect(rectangle, e_position_bottom);

      if(rectangle.contains(point))
      {

         return e_position_bottom;

      }

      GetDragRect(rectangle, e_position_left);

      if(rectangle.contains(point))
      {

         return e_position_left;

      }

      GetDragRect(rectangle, e_position_right);

      if(rectangle.contains(point))
      {

         return e_position_right;

      }

      return e_position_none;

   }


   void tab::GetDragRect(RECTANGLE_I32 * prectangle, enum_position eposition)

   {
      switch(eposition)
      {
      case e_position_top:
      {
         prectangle->top = get_data()->m_rectangleTabClient.top;

         prectangle->left = get_data()->m_rectangleTabClient.left + get_data()->m_rectangleTabClient.width() / 3;

         prectangle->right = prectangle->left + get_data()->m_rectangleTabClient.width() / 3;

         prectangle->bottom = prectangle->top + get_data()->m_rectangleTabClient.height() / 3;

      }
      break;
      case e_position_left:
      {
         prectangle->top = get_data()->m_rectangleTabClient.top + get_data()->m_rectangleTabClient.height() / 3;

         prectangle->left = get_data()->m_rectangleTabClient.left;

         prectangle->right = prectangle->left + get_data()->m_rectangleTabClient.width() / 3;

         prectangle->bottom = prectangle->top + get_data()->m_rectangleTabClient.height() / 3;

      }
      break;
      case e_position_right:
      {
         prectangle->top = get_data()->m_rectangleTabClient.top + get_data()->m_rectangleTabClient.height() / 3;

         prectangle->left = get_data()->m_rectangleTabClient.left + get_data()->m_rectangleTabClient.width() * 2 / 3;

         prectangle->right = prectangle->left + get_data()->m_rectangleTabClient.width() / 3;

         prectangle->bottom = prectangle->top + get_data()->m_rectangleTabClient.height() / 3;

      }
      break;
      case e_position_bottom:
      {
         prectangle->top = get_data()->m_rectangleTabClient.top + get_data()->m_rectangleTabClient.height() * 2 / 3;

         prectangle->left = get_data()->m_rectangleTabClient.left + get_data()->m_rectangleTabClient.width() / 3;

         prectangle->right = prectangle->left + get_data()->m_rectangleTabClient.width() / 3;

         prectangle->bottom = prectangle->top + get_data()->m_rectangleTabClient.height() / 3;

      }
      break;
      default:
         break;
      }
   }



   void tab::_001OnDropTab(::index iIndex, enum_position eposition)
   {

      if(get_data()->m_pcallback != nullptr)
      {

         get_data()->m_pcallback->_001OnDropTab(iIndex, eposition);

      }

   }


   ::user::interaction * tab::get_view_uie()
   {

      return nullptr;

   }


   void tab::get_child_rect(RECTANGLE_I32* prectangle)
   {

      if (::is_null(prectangle))
      {

         return;

      }

      synchronous_lock synchronouslock(mutex());

      *prectangle = get_data()->m_rectangleTabClient;

   }


   void tab::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::interaction::handle(ptopic, pcontext);

      if (ptopic->m_atom == id_get_topic_view_id)
      {

         ptopic->payload(id_id) = get_current_tab_id();

         ptopic->m_bRet = true;

      }
      else if (ptopic->m_atom == id_set_topic_view_by_id)
      {

         set_current_tab_by_id(ptopic->payload(id_id));

         ptopic->m_bRet = true;

      }
      else if(ptopic->m_atom == id_place_child_title_change)
      {

         for (auto& ppane : get_data()->m_tabpanecompositea)
         {

            if (ppane->m_pplaceholder == ptopic->m_puserelement)
            {

               auto puserinteractionpointeraChild = ppane->m_pplaceholder->m_puserinteractionpointeraChild;

               auto pchild = puserinteractionpointeraChild->first_interaction();

               if (pchild)
               {

                  string strTitle(pchild->payload("place_child_title").get_string());

                  ppane->set_title(strTitle);

               }

            }

         }

      }

   }


   void tab::rotate()
   {

      throw ::exception(todo);

   }


   void tab::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction::_001OnTimer(ptimer);

      if (ptimer->m_uEvent == e_timer_defer_handle_auto_hide_tabs)
      {

         if (defer_handle_auto_hide_tabs(false))
         {

            set_need_layout();

            set_need_redraw();

         }

      }

      if(ptimer->m_uEvent == e_timer_drag_start)
      {
         //auto elapsed = g_tickDragStart.elapsed();
         KillTimer(e_timer_drag_start);

         auto psession = get_session();

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         pwindowing->release_mouse_capture();

         auto pointCursor = pwindowing->get_cursor_position();

         auto pitem = hit_test(pointCursor);

         index iClickTab = get_data()->m_iClickTab;

         if(::is_item(pitem, iClickTab))
         {

            get_data()->m_bDrag = true;

            m_estate = state_drag_commanded;

            post_message(message_start_tab_drag);

         }
         else
         {

            m_estate = e_state_initial;

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

         m_estate = e_state_initial;

      }

   }


   //void tab::_000OnMouse(::message::mouse * pmouse)
   //{

   //   if(m_bShowTabs)
   //   {

   //      // these try catchs are needed for multi threading supporting: multi threaded windows: an endeavour
   //      // Now I understand why Microsoft (TM) Windows (R) windows are single threaded.
   //      // to debug, enable catch exceptions in debugger
   //      try
   //      {

   //         ::rectangle_i32 rectangleTabScreen(get_data()->m_rectangleTab);

   //         client_to_screen(rectangleTabScreen);

   //         if ((pmouse->m_atom == e_message_left_button_down || pmouse->m_atom == e_message_left_button_up) && rectangleTabScreen.contains(pmouse->m_point))
   //         {

   //            route_message(pmouse);

   //            if (pmouse->m_lresult != 0)
   //            {

   //               return;

   //            }

   //         }
   //         else if (pmouse->m_atom == e_message_mouse_move)
   //         {

   //            route_message(pmouse);

   //            if (pmouse->m_lresult != 0)
   //            {

   //               return;

   //            }

   //         }

   //      }
   //      catch(...)
   //      {

   //      }

   //   }
   //   else if(pmouse->m_atom == e_message_mouse_move)
   //   {

   //   }

   //   __pointer(::user::interaction) pinteraction;


   //   while(rget_child(pinteraction))
   //   {

   //      try
   //      {

   //         if(pinteraction->is_window_visible() && pinteraction->_001IsPointInside(pmouse->m_point))
   //         {

   //            try
   //            {

   //               pinteraction->_000OnMouse(pmouse);

   //               if (pmouse->m_bRet)
   //               {

   //                  return;

   //               }

   //            }
   //            catch(...)
   //            {

   //            }

   //         }

   //      }
   //      catch(...)
   //      {

   //      }

   //   }

   //}


   tab_data * tab::get_data()
   {

      return m_pdata;

   }


   ::user::tab_pane *tab::get_tab_by_id(const ::atom & atom)
   {

      return get_data()->get_tab_by_id(atom);

   }


   //::user::tab_pane * tab::create_tab_by_id(atom atom)
   //{

   //   create_tab_by_id(atom);

   //   return get_data()->get_tab_by_id(atom);

   //}


   ::user::tab_pane * tab::create_tab_by_id(const ::atom & atom)
   {

      if (!add_tab("", atom))
      {

         return nullptr;

      }

      index iIndex = id_index(atom);

      if (iIndex < 0)
      {

         return nullptr;

      }

      auto ppaneTab = get_tab(iIndex);

      return ppaneTab;

   }


   /// array - if you want, you can hint on_change_tab_count
   /// with added panes info. Pass array with nullptr value to force save restorable tabs
   void tab::on_change_tab_count(array < ::user::tab_pane * > array)
   {

      bool bAny = false;

      for (auto ppane : array)
      {

         if (ppane == nullptr || matches_restorable_tab(ppane->m_atom, ppane->m_pplaceholder))
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

   }


   void tab::save_restorable_tabs()
   {

      if (m_bDisableSavingRestorableTabs)
      {

         return;

      }

      if (get_data()->m_matchanyRestore.m_itema.get_count() > 0)
      {

         payload_array payloada;

         get_restore_tab(payloada);

         //if (payloada.get_size() > 0)
         //{
         //   TRACE(".");
         //   for (index i = 0; i < 200; i++)
         //   {


         //data_set("restore_tab", payloada);
         //   }
         //}
         //else
         //{
         //   TRACE("o");
         //   for (index i = 0; i < 200; i++)
         //   {


         //      data_save("restore_tab", payloada);
         //   }

         //}

      }


   }


   void tab::get_text_id(string_array & stra)
   {

      get_presuffixed_ci_id(stra, nullptr, nullptr);

   }


   void tab::get_prefixed_ci_id(string_array & stra, const ::string & pszPrefix)
   {

      get_presuffixed_ci_id(stra, pszPrefix, nullptr);

   }


   void tab::get_suffixed_ci_id(string_array & stra, const ::string & pszSuffix)
   {

      get_presuffixed_ci_id(stra, nullptr, pszSuffix);

   }


   void tab::get_presuffixed_ci_id(string_array & stra, const ::string & pszPrefix, const ::string & pszSuffix)
   {

      string strPrefix(pszPrefix);

      string strSuffix(pszSuffix);

      string strPath;

      auto & panea = get_data()->m_tabpanecompositea;

      for(i32 i = 0; i < panea.get_count(); i++)
      {

         auto ppane = panea[i].get();

         strPath = ppane->m_atom;

         if(strPrefix.is_empty() || ::str().begins_ci(strPath, strPrefix))
         {

            if(strSuffix.is_empty() || ::str().ends_ci(strPath, strSuffix))
            {

               stra.add(strPath);

            }

         }

      }

   }


   void tab::get_begins_ci_eat_id(string_array & stra, const ::string & pszPrefix)
   {

      get_begins_ends_ci_eat_id(stra, pszPrefix, nullptr);

   }


   void tab::get_ends_ci_eat_id(string_array & stra, const ::string & pszSuffix)
   {

      get_begins_ends_ci_eat_id(stra, nullptr, pszSuffix);

   }


   void tab::get_begins_ends_ci_eat_id(string_array & stra, const ::string & pszPrefix, const ::string & pszSuffix)
   {

      string strPrefix(pszPrefix);

      string strSuffix(pszSuffix);

      string strPath;

      tab_pane_composite_array & panea = get_data()->m_tabpanecompositea;

      for(i32 i = 0; i < panea.get_count(); i++)
      {

         auto ppane = panea[i].get();

         strPath = ppane->m_atom;

         if(strPrefix.is_empty() || ::str().begins_ci(strPath, strPrefix))
         {

            if(strSuffix.is_empty() || ::str().ends_ci(strPath, strSuffix))
            {

               stra.add(strPath);

            }

         }

      }

   }


   bool tab::matches_restorable_tab(const ::payload & varId, ::user::place_holder * pholder)
   {

      ::match::any & matchany = get_data()->m_matchanyRestore;

      if (pholder != nullptr && pholder->payload("void_restore").is_true())
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

   void tab::get_restore_tab(payload_array & payloada)
   {

      ::payload varId;

      tab_pane_composite_array & panea = get_data()->m_tabpanecompositea;

      for(i32 i = 0; i < panea.get_count(); i++)
      {

         varId = panea[i]->m_atom;

         if(matches_restorable_tab(varId, panea[i]->m_pplaceholder))
         {

            payloada.add(varId);

         }

      }

   }


   void tab::create_tabs()
   {

      m_iRestoredTabCount = restore_tabs();

      on_create_tabs();

      m_bCreatedTabs = true;

   }


   bool tab::has_restore_tab()
   {

      ::match::any  & matchany = get_data()->m_matchanyRestore;

      if(matchany.is_there_no_item())
         return false;
      ::payload varId;
      tab_pane_composite_array & panea = get_data()->m_tabpanecompositea;
      for(i32 i = 0; i < panea.get_count(); i++)
      {
         varId = panea[i]->m_atom;
         if(matchany.matches(varId))
         {
            return true;
         }
      }

      return false;

   }


   ::count tab::open_tabs(const payload_array & payloada)
   {

      ::count c = 0;

      string_array stra;

      for(i32 i = 0; i < payloada.get_count(); i++)
      {

         // ODOW : TODO : should create bergedgewrapper to open bergedge inside a window.

         if(payloada[i].get_type() == ::e_type_string && payloada[i].string() == "app:bergedge")
            continue;

         if(payloada[i].get_type() == ::e_type_string && payloada[i].string() == "app:")
            continue;

         //if(stra.add_unique(payloada[i]) >= 0)
         //{
         //create_tab_by_id(stra.last());

         set_current_tab_by_id(payloada[i].atom());

         c++;

         //}

      }

      return c;

   }


   void tab::_001CloseTab(::index iIndex)
   {

      erase_tab_by_id(index_id(iIndex));

   }


   void tab::on_message_show_window(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

//      __pointer(::message::show_window) pshowwindow(pmessage);

//      ::user::place_holder * pholder = tab_holder(get_current_tab_index());
//
//      if (pholder != nullptr)
//      {
//
//         if (pshowwindow->m_bShow)
//         {
//
//            pholder->display(e_display_normal);
//
//         }
//         else
//         {
//
//            pholder->display(e_display_none);
//
//         }
//
//      }

   }


} // namespace base


