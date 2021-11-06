#pragma once

namespace user
{

   class scroll_info
   {
      public:
         ::u32     cbSize;
         ::u32     fMask;
         i32      nMin;
         i32      nMax;
         i32      nPage;
         i32      nPos;
         i32      nTrackPos;
   };


} // namespace user
