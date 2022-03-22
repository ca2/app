/*
    nanogui/imagepanel.h -- Image panel widget which shows a number of
    square-shaped icons

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/** \file */

#pragma once



#include <nanogui/widget.h>

NAMESPACE_BEGIN(nanogui)

/**
 * \class ImagePanel imagepanel.h nanogui/imagepanel.h
 *
 * \brief Image panel widget which shows a number of square-shaped icons.
 */
   class NANOGUI_EXPORT ImagePanel : public Widget {
   public:
      typedef std::vector<std::pair<int, std::string>> Images;
      std::string m_strLoadDirectory;
      bool m_bPendingLoad = false;
   public:
      ImagePanel(Widget * parent);


      void  load_image_directory(const std::string & str) { m_strLoadDirectory = str; m_bPendingLoad = true; }

      void set_images(const Images & data) { m_images = data; }
      const Images & images() const { return m_images; }
      ::image * _get_image(int iImage);

      ::function<void(int)> callback() const { return m_callback; }
      void set_callback(const ::function<void(int)> & callback) { m_callback = callback; }

      virtual bool mouse_motion_event(const Vector2i & p, const Vector2i & rel, int button,
         int modifiers) override;
      virtual bool mouse_button_event(const Vector2i & p, int button, bool down,
         int modifiers) override;
      virtual Vector2i preferred_size(NVGcontext * ctx) const override;
      virtual void draw(NVGcontext * ctx) override;

      void _defer_load_image_directory(NVGcontext * ctx);

   protected:
      Vector2i grid_size() const;
      int index_for_position(const Vector2i & p) const;
   protected:
      Images m_images;
      ::function<void(int)> m_callback;
      int m_thumb_size;
      int m_spacing;
      int m_margin;
      int m_mouse_index;
};

NAMESPACE_END(nanogui)
