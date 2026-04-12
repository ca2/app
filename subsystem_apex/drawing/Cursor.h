//
// Adapted by camilo on beginning of 2026-April <3ThomasBorregaardSorensen!!
//
#pragma once


#include "subsystem_apex/drawing/Cursor.h"
#include "subsystem_win32/_common_header.h"


namespace subsystem_apex
{


   class CursorInterface :
      virtual public ::subsystem::particle_interface<::subsystem_apex::CursorInterface>
   {
   public:

      //CursorInterface();
      // Icon(HICON icon);
      // Icon(Bitmap *bitmap);
      // Icon(Bitmap *bitmap, Bitmap *mask);
      // Icon(DWORD icon);
      //virtual ~CursorInterface() = 0;

      virtual void * _HCURSOR() = 0;
      virtual void _setHCURSOR(void * p) = 0;

      virtual void initialize_cursor(::subsystem_apex::CursorInterface * picon) = 0;
      virtual void initialize_cursor(::subsystem_apex::BitmapInterface *bitmap) = 0;
      virtual void initialize_cursor(::subsystem_apex::BitmapInterface *bitmap, ::subsystem_apex::BitmapInterface *mask) = 0;
      virtual void initialize_with_system_cursor(enum_cursor ecursor) = 0;

      //void initi(HICON icon);
      //Icon(Bitmap *bitmap);
      //Icon(Bitmap *bitmap, Bitmap *mask);
      //Icon(DWORD icon);

   //protected:
      virtual void fromBitmap(::subsystem_apex::BitmapInterface *bitmap, ::subsystem_apex::BitmapInterface *mask) = 0;

   // protected:
//      HCURSOR m_hcursor;
  //    bool m_bHasOwnCursor;
   };
    
    
   class CLASS_DECL_APEX Cursor :
      virtual public ::subsystem::composite<::subsystem_apex::CursorInterface>
   {
   public:

      Cursor();
      // Icon(HICON icon);
      // Icon(Bitmap *bitmap);
      // Icon(Bitmap *bitmap, Bitmap *mask);
      // Icon(DWORD icon);
      ~Cursor() override;

      void * _HCURSOR() override;
      void _setHCURSOR(void * p) override;

      void initialize_cursor(::subsystem_apex::CursorInterface * picon) override;
      void initialize_cursor(::subsystem_apex::BitmapInterface *bitmap) override;
      void initialize_cursor(::subsystem_apex::BitmapInterface *bitmap, ::subsystem_apex::BitmapInterface *mask) override;
      void initialize_with_system_cursor(::enum_cursor ecursor) override;

      //void initi(HICON icon);
      //Icon(Bitmap *bitmap);
      //Icon(Bitmap *bitmap, Bitmap *mask);
      //Icon(DWORD icon);

   //protected:
      void fromBitmap(::subsystem_apex::BitmapInterface *bitmap, ::subsystem_apex::BitmapInterface *mask) override;

   // protected:
//      HCURSOR m_hcursor;
  //    bool m_bHasOwnCursor;
   };



} // namespace subsystem_apex


