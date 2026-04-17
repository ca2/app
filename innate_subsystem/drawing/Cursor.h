//
// Adapted by camilo on beginning of 2026-April <3ThomasBorregaardSorensen!!
//
#pragma once


#include "innate_subsystem/drawing/Cursor.h"
#include "subsystem_windows/_common_header.h"


namespace innate_subsystem
{


   class CursorInterface :
      virtual public ::Particle
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
    
    
   class CLASS_DECL_INNATE_SUBSYSTEM CursorComposite :
      virtual public Composite<::innate_subsystem::CursorInterface>
   {
   public:

      ImplementCompositeø(Cursor, cursor)

      //Cursor();
      // Icon(HICON icon);
      // Icon(Bitmap *bitmap);
      // Icon(Bitmap *bitmap, Bitmap *mask);
      // Icon(DWORD icon);
      //~Cursor() override;

         void* _HCURSOR() override
      {

         return m_pcursor->_HCURSOR();
      }
      void _setHCURSOR(void* p) override
      {

         m_pcursor->_setHCURSOR(p);
      }

      void initialize_cursor(::innate_subsystem::CursorInterface* picon) override
      {
         m_pcursor->initialize_cursor(picon);
      }
      void initialize_cursor(::innate_subsystem::BitmapInterface* bitmap) override
      {
         m_pcursor->initialize_cursor(bitmap);
      }
      void initialize_cursor(::innate_subsystem::BitmapInterface* bitmap, ::innate_subsystem::BitmapInterface* mask) override
      {
         m_pcursor->initialize_cursor(bitmap, mask);
      }
      void initialize_with_system_cursor(::enum_cursor ecursor) override
      {
         m_pcursor->initialize_with_system_cursor(ecursor);
      }

      //void initi(HICON icon);
      //Icon(Bitmap *bitmap);
      //Icon(Bitmap *bitmap, Bitmap *mask);
      //Icon(DWORD icon);

   //protected:
      void fromBitmap(::innate_subsystem::BitmapInterface* bitmap, ::innate_subsystem::BitmapInterface* mask) override
      {
         m_pcursor->fromBitmap(bitmap, mask);
      }

   // protected:
//      HCURSOR m_hcursor;
  //    bool m_bHasOwnCursor;
   };



    class CLASS_DECL_SUBSYSTEM CursorAggregate :
    virtual public Aggregate< CursorComposite >
    {
    public:

        ImplementBaseø(Cursor);

    };


   class CLASS_DECL_SUBSYSTEM Cursor :
   virtual public Object< CursorAggregate >
   {
   public:


   };


} // namespace innate_subsystem


