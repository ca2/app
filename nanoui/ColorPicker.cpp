/*
    src/colorpicker.cpp -- push button with a popup to tweak a color value

    This pwidget was contributed by Christian Schueller.

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "ColorPicker.h"
#include "Layout.h"
#include "ColorWheel.h"
#include "IntBox.h"
#include "Label.h"
#include "TabWidget.h"
#include "acme/constant/source.h"
#include "acme/prototype/prototype/action_context.h"


namespace nanoui
{
   ColorPicker::MyGridWidget::MyGridWidget(nanoui::Widget* p, int cols) :
      nanoui::Widget(p)
   {
      auto playout = øallocate nanoui::GridLayout(::e_orientation_horizontal, cols,
         e_alignment_minimum);

      set_layout(playout);

   }


   void ColorPicker::sync_color(const ::color::hls& hls, bool bForceH, bool bForceS, bool bForceB)
   {

      m_pick_button->set_background_color(hls);

      ::color::color color(hls);

      m_pick_button->set_text_color(color.contrasting_color());

      m_color_wheel->set_sel_color(hls);

      if (m_callback)
      {

         m_callback(hls);

      }

      ::color::hsv hsv(hls);
      m_peditRed->set_value(color.byte_red(), e_source_sync);
      m_peditGreen->set_value(color.byte_green(), e_source_sync);
      m_peditBlue->set_value(color.byte_blue(), e_source_sync);
      if (bForceH || fabs(m_peditHSV_H->value() - (int)(hsv.m_dH * 360.0)) > 2.0)
      {
         m_peditHSV_H->set_value((int) (hsv.m_dH * 360.0), e_source_sync);
      }
      if (bForceS || fabs(m_peditHSV_S->value() - (int)(hsv.m_dS * 100.0)) > 5.0)
      {
         m_peditHSV_S->set_value((int) (hsv.m_dS * 100.0), e_source_sync);
      }
      if (bForceB || fabs(m_peditHSV_V->value() - (int)(hsv.m_dV * 100.0)) > 5.0)
      {
         m_peditHSV_V->set_value((int)(hsv.m_dV * 100.0), e_source_sync);
      }

      ::string strHex;
      strHex.formatf("%02X%02X%02X", color.byte_red(), color.byte_green(),  color.byte_blue());

      m_peditHex->set_value(strHex, e_source_sync);

      m_ppopup->set_need_redraw();

      m_ppopup->post_redraw();

   }


   ColorPicker::ColorPicker(Widget* parent, const ::color::hls& hls) :
      PopupButton(parent, "")
   {

      set_background_color(hls);

      m_ppopup->set_layout(øallocate GroupLayout());

      // initialize callback to do nothing; this is for users to hook into
      // receiving a ___new color value
      m_callback = [](const ::color::hls&) {};
      m_final_callback = [](const ::color::hls&) {};

      

      // set the color wheel to the specified color
      m_color_wheel = øallocate ColorWheel(m_ppopup, hls);

      m_ptab = øallocate TabWidget(m_ppopup);

      m_ptab->set_erase_children(false);

      m_pgridRgb = øallocate MyGridWidget(m_ptab, 2);

      {
         
         øallocate nanoui::Label(m_pgridRgb, "Red", "sans", 14);

         auto pedit = øallocate  nanoui::IntBox<int>(m_pgridRgb);
         pedit->set_editable(true);
         pedit->set_font_size(14);
         pedit->set_unit("");
         pedit->set_fixed_size({ 70,25 });
         pedit->set_value(0, ::e_source_initialize);
         pedit->set_minimum_maximum_values(0, 255);
         pedit->set_alignment(::nanoui::TextBox::e_alignment_right);
         pedit->set_spinnable(true);

         m_peditRed = pedit;

      }

      {

         øallocate nanoui::Label(m_pgridRgb, "Green", "sans", 14);

         auto pedit = øallocate  nanoui::IntBox<int>(m_pgridRgb);
         pedit->set_editable(true);
         pedit->set_font_size(14);
         pedit->set_unit("");
         pedit->set_fixed_size({ 70,25 });
         pedit->set_value(0, ::e_source_initialize);
         pedit->set_minimum_maximum_values(0, 255);
         pedit->set_alignment(::nanoui::TextBox::e_alignment_right);
         pedit->set_spinnable(true);

         m_peditGreen = pedit;

      }


      {

         øallocate nanoui::Label(m_pgridRgb, "Blue", "sans", 14);

         auto pedit = øallocate  nanoui::IntBox<int>(m_pgridRgb);
         pedit->set_editable(true);
         pedit->set_font_size(14);
         pedit->set_unit("");
         pedit->set_fixed_size({ 70,25 });
         pedit->set_value(0, ::e_source_initialize);
         pedit->set_minimum_maximum_values(0, 255);
         pedit->set_alignment(::nanoui::TextBox::e_alignment_right);
         pedit->set_spinnable(true);

         m_peditBlue = pedit;

      }

      m_ptab->append_tab("RGB", m_pgridRgb);

      m_pgridHSV = øallocate MyGridWidget(m_ptab, 2);

      {

         øallocate nanoui::Label(m_pgridHSV, "Hue", "sans", 14);

         auto pedit = øallocate  nanoui::IntBox<int>(m_pgridHSV);
         pedit->set_editable(true);
         pedit->set_font_size(14);
         pedit->set_unit("");
         pedit->set_fixed_size({ 70,25 });
         pedit->set_value(0, ::e_source_initialize);
         pedit->set_alignment(::nanoui::TextBox::e_alignment_right);
         pedit->set_minimum_maximum_values(0, 360);
         pedit->set_spinnable(true);

         m_peditHSV_H = pedit;

      }

      {

         øallocate nanoui::Label(m_pgridHSV, "Saturation", "sans", 14);

         auto pedit = øallocate  nanoui::IntBox<int>(m_pgridHSV);
         pedit->set_editable(true);
         pedit->set_font_size(14);
         pedit->set_unit("");
         pedit->set_fixed_size({ 70,25 });
         pedit->set_value(0, ::e_source_initialize);
         pedit->set_alignment(::nanoui::TextBox::e_alignment_right);
         pedit->set_minimum_maximum_values(0, 100);
         pedit->set_spinnable(true);

         m_peditHSV_S = pedit;

      }



      {

         øallocate nanoui::Label(m_pgridHSV, "Brightness", "sans", 14);

         auto pedit = øallocate  nanoui::IntBox<int>(m_pgridHSV);
         pedit->set_editable(true);
         pedit->set_font_size(14);
         pedit->set_unit("");
         pedit->set_fixed_size({ 70,25 });
         pedit->set_value(0, ::e_source_initialize);
         pedit->set_alignment(::nanoui::TextBox::e_alignment_right);
         pedit->set_minimum_maximum_values(0, 100);
         pedit->set_spinnable(true);

         m_peditHSV_V = pedit;

      }

      m_ptab->append_tab("HSV", m_pgridHSV);

      m_pgridHEX = øallocate MyGridWidget(m_ptab, 2);

      {

         øallocate nanoui::Label(m_pgridHEX, "#", "sans", 14);

         auto pedit = øallocate  nanoui::TextBox(m_pgridHEX);
         pedit->set_editable(true);
         pedit->set_font_size(14);
         pedit->set_fixed_size({ 70,25 });
         pedit->set_value("", ::e_source_initialize);
         pedit->set_alignment(::nanoui::TextBox::e_alignment_right);

         m_peditHex = pedit;

      }

      m_ptab->append_tab("HEX", m_pgridHEX);

      ::color::color color(hls);

      // set the pick button to the specified color
      m_pick_button = øallocate Button(m_ppopup, "Pick");
      m_pick_button->set_background_color(hls);
      m_pick_button->set_text_color(color.contrasting_color());
      m_pick_button->set_fixed_size({100, 20});

      // set the reset button to the specified color
      m_reset_button = øallocate Button(m_ppopup, "Reset");
      m_reset_button->set_background_color(color);
      m_reset_button->set_text_color(color.contrasting_color());
      m_reset_button->set_fixed_size({100, 20});

      PopupButton::set_change_callback([&](bool)
         {

            if (m_pick_button->checked())
            {

               set_color(colorBackground());

               m_final_callback(colorBackground());

            }

         });

      m_color_wheel->set_callback([&](const ::color::hls& hls)
         {

            sync_color(hls, true, true, true);

         });

      m_pick_button->set_callback([&]() {
         if (m_bChecked) {
            ::color::hls value = m_color_wheel->get_sel_color();
            set_checked(false, e_source_selection);
            set_color(value);
            call_final_callback(value);
            post_redraw();
         }
         });

      m_reset_button->set_callback([&]() {
         ::color::hls bg = m_reset_button->colorBackground();
         ::color::hls fg = m_reset_button->text_color();

         m_color_wheel->set_sel_color(bg);
         m_pick_button->set_background_color(bg);
         m_pick_button->set_text_color(fg);

         m_callback(bg);
         call_final_callback(bg);

         post_redraw();

         });

      m_peditRed->set_callback([&](int iIntensity) {
            ::color::color color = m_color_wheel->get_sel_color();
            color.set_red(iIntensity);
            sync_color(color, true, true, true);
         });
      m_peditGreen->set_callback([&](int iIntensity) {
            ::color::color color = m_color_wheel->get_sel_color();
            color.set_green(iIntensity);
            sync_color(color, true, true, true);
         });
      m_peditBlue->set_callback([&](int iIntensity) {
            ::color::color color = m_color_wheel->get_sel_color();
         color.set_blue(iIntensity);
         sync_color(color, true, true, true);
         });
      m_peditHSV_H->set_callback([&](int iIntensity) {
         auto hls = m_color_wheel->get_sel_color();
         hls.m_dH = (double) iIntensity / 360.0;
         sync_color(hls, false, true, true);
         });
      m_peditHSV_S->set_callback([&](int iIntensity) {
         ::color::hsv hsv = m_color_wheel->get_sel_color();
         hsv.m_dS = (double)iIntensity / 100.0;
         sync_color(hsv, true, false, true);
         });
      m_peditHSV_V->set_callback([&](int iIntensity) {
         ::color::hsv hsv = m_color_wheel->get_sel_color();
         hsv.m_dV = (double)iIntensity / 100.0;
         sync_color(hsv, true, true, false);
         });
      m_peditHex->set_callback([&](const ::scoped_string& str) {
         ::color::color color;
         try
         {
            color = ::color::hex_to_color(str);
         }
         catch (...)
         {
            color = ::color::white;
         }
         sync_color(color, true, true, true);
         return true;
         });

      sync_color(hls, true, true, true);


   }


   ::color::hls ColorPicker::color() const
   {

      return colorBackground();

   }


   void ColorPicker::set_color(const ::color::hls& hls)
   {

      /* Ignore set_color() calls when the user is currently editing */
      if (!m_bChecked)
      {
         ::color::color color(hls);
         auto fg = color.contrasting_color();
         set_background_color(hls);
         set_text_color(fg);
         m_color_wheel->set_sel_color(color);

         m_pick_button->set_background_color(color);
         m_pick_button->set_text_color(fg);

         m_reset_button->set_background_color(color);
         m_reset_button->set_text_color(fg);
      }

   }


   void ColorPicker::call_final_callback(const ::color::hls& color)
   {

      popup()->set_visible(false);

      m_final_callback(color);

   }



} // namespace nanoui



