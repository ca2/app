/*
    nanoui/messagedialog.h -- Simple "OK" or "Yes/No"-style modal dialogs

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/** \file */

#pragma once


#include "Window.h"


namespace nanoui
{


/**
 * \class MessageDialog messagedialog.h nanoui/messagedialog.h
 *
 * \brief Simple "OK" or "Yes/No"-style modal dialogs.
 */
   class CLASS_DECL_NANOUI MessageDialog : public Window {
   public:
      /// Classification of the type of message this MessageDialog represents.
      enum class Type {
         Information,
         Question,
         Warning
      };

      MessageDialog(Widget * parent, Type type, const ::scoped_string & title = "Untitled",
         const ::scoped_string & message = "Message",
         const ::scoped_string & button_text = "OK",
         const ::scoped_string & alt_button_text = "Cancel", bool alt_button = false, const ::function < void(nanoui::Widget * p) > functionExtras = nullptr);

      Label * message_label() { return m_message_label; }
      const Label * message_label() const { return m_message_label; }

      ::function<void(int)> callback() const { return m_callback; }
      void set_callback(const ::function<void(int)> & callback) { m_callback = callback; }
   protected:
      ::function<void(int)> m_callback;
      Label * m_message_label;
};



} // namespace nanoui


