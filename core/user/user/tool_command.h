#pragma once


namespace user
{

   class tool_command :
      public ::message::command        // class private to this file !
   {
   public: // re-implementations only


      tool_command();
      virtual ~tool_command();

      virtual void enable(bool bOn);
      virtual void SetCheck(i32 nCheck);
      virtual void SetText(const char * pszText);

   };

   struct toolbar_data
   {
      ::u16 wVersion;
      ::u16 wWidth;
      ::u16 wHeight;
      ::u16 wItemCount;
      //::u16 aItems[wItemCount]

      ::u16* items()
         { return (::u16*)(this+1); }
   };

} // namespace user

