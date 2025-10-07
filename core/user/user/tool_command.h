#pragma once


#include "apex/message/command.h"


namespace user
{

   class tool_command :
      public ::message::command        // class private to this file !
   {
   public: // re-implementations only


      tool_command();
      virtual ~tool_command();

      virtual void enable(bool bOn);
      virtual void SetCheck(int nCheck);
      virtual void SetText(const ::scoped_string & scopedstrText);

   };

   struct toolbar_data
   {
      unsigned short wVersion;
      unsigned short wWidth;
      unsigned short wHeight;
      unsigned short wItemCount;
      //unsigned short aItems[wItemCount]

      unsigned short* items()
         { return (unsigned short*)(this+1); }
   };

} // namespace user

