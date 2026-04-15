//
// Adapted by camilo on beginning of 2026-April <3ThomasBorregaardSorensen!!
//
#pragma once


#include "innate_subsystem/drawing/Cursor.h"
#include "subsystem_windows/_common_header.h"


namespace innate_subsystem
{


   class CursorInterface :
      virtual public particle_interface<::innate_subsystem::CursorInterface>
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

      virtual void initialize_cursor(::innate_subsystem::CursorInterface * picon) = 0;
      virtual void initialize_cursor(::innate_subsystem::BitmapInterface *bitmap) = 0;
      virtual void initialize_cursor(::innate_subsystem::BitmapInterface *bitmap, ::innate_subsystem::BitmapInterface *mask) = 0;
      virtual void initialize_with_system_cursor(enum_cursor ecursor) = 0;

      //void initi(HICON icon);
      //Icon(Bitmap *bitmap);
      //Icon(Bitmap *bitmap, Bitmap *mask);
      //Icon(DWORD icon);

   //protected:
      virtual void fromBitmap(::innate_subsystem::BitmapInterface *bitmap, ::innate_subsystem::BitmapInterface *mask) = 0;

   // protected:
//      HCURSOR m_hcursor;
  //    bool m_bHasOwnCursor;
   };
    
    
   class CLASS_DECL_INNATE_SUBSYSTEM Cursor :
      virtual public composite<::innate_subsystem::CursorInterface>
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

      void initialize_cursor(::innate_subsystem::CursorInterface * picon) override;
      void initialize_cursor(::innate_subsystem::BitmapInterface *bitmap) override;
      void initialize_cursor(::innate_subsystem::BitmapInterface *bitmap, ::innate_subsystem::BitmapInterface *mask) override;
      void initialize_with_system_cursor(::enum_cursor ecursor) override;

      //void initi(HICON icon);
      //Icon(Bitmap *bitmap);
      //Icon(Bitmap *bitmap, Bitmap *mask);
      //Icon(DWORD icon);

   //protected:
      void fromBitmap(::innate_subsystem::BitmapInterface *bitmap, ::innate_subsystem::BitmapInterface *mask) override;

   // protected:
//      HCURSOR m_hcursor;
  //    bool m_bHasOwnCursor;
   };



    class CLASS_DECL_SUBSYSTEM File :
    virtual public aggregate< FileComposite >
    {
    public:

        implement_baseø(File);

    };




} // namespace innate_subsystem


