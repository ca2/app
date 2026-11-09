#pragma once

#include "acme/user/micro/message_box.h"

namespace micro
{
   // A command is data: displaying or copying it never executes it.
   class command_message_box : virtual public ::micro::message_box
   {
   public:
      ::string m_strCommand;
      ::function<void(const ::string &)> m_copyCommand;

      void initialize_command_message_box(
         const ::scoped_string & message,
         const ::scoped_string & command,
         const ::function<void(const ::string &)> & copy_command,
         const ::scoped_string & title = "Terminal command")
      {
         m_strCommand = command;
         m_copyCommand = copy_command;
         initialize_message_box(::string(message) + "\n\n" + m_strCommand, title);
         add_button("Copy Command", e_dialog_result_yes, 'c');
         add_button("Cancel", e_dialog_result_cancel, 'a');
      }

      void set_dialog_response(const ::payload & result) override
      {
         if (result == e_dialog_result_yes)
         {
            // Copy is an action, not a completed dialog response. This also
            // handles keyboard activation without entering the close path.
            m_copyCommand(m_strCommand);
         }
         else if (result == e_dialog_result_cancel)
         {
            ::micro::message_box::set_dialog_response(result);
         }
      }
   };
}
