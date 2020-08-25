#pragma once


namespace user
{

   class tool_command :
      public ::user::command        // class private to this file !
   {
   public: // re-implementations only


      tool_command();
      virtual ~tool_command();

      virtual void Enable(bool bOn);
      virtual void SetCheck(i32 nCheck);
      virtual void SetText(const char * pszText);

   };

   struct toolbar_data
   {
      WORD wVersion;
      WORD wWidth;
      WORD wHeight;
      WORD wItemCount;
      //WORD aItems[wItemCount]

      WORD* items()
         { return (WORD*)(this+1); }
   };

} // namespace user

