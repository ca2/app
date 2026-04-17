// Copyright (C) 2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the TightVNC software.  Please visit our Web site:
//
//                       http://www.tightvnc.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

#pragma once


#include "acme/operating_system/window.h"
#include "subsystem/_common_header.h"
#ifndef CAPTUREBLT
#define CAPTUREBLT          (DWORD)0x40000000 /* Include layered windows */
#endif


//#include "subsystem/Screen.h"

namespace innate_subsystem
{


      // This clas is a primitive wrapper to a DIB section.
   class  DibSectionInterface :
      virtual public ::Particle
   {
   public:
      // Note that if the compatibleWin doesn't specify or is zero the class will create an
      // DC for the entire screen. In this case an this object owner must provide
      // destructor calling from the same thread that called the constructor.
      // In default the created DC will used as a target DC for the blitting operations.
      // It may be changed many times later. Note that changed DC must be compatible with
      // the DIB section.
      //DibSection(const PixelFormat & pf, const ::int_size & dim, HWND compatibleWin = 0);
      //DibSection();
      //virtual ~DibSectionInterface() = 0 ;


      virtual void initialize_dib_section(const ::innate_subsystem::PixelFormat & pf, const ::int_size & dim, const ::operating_system::window & operatingsystemwindow = {}) = 0;

      // This function changes the target DC. In default target DC is a DC that has been
      // got from a compatible window on object creation. This function can be call many times.
      virtual void setTargetDeviceContext(::innate_subsystem::DeviceContextInterface * pdevicecontext) = 0;

      virtual void *getBuffer() = 0;

      // This function copies a block of bits from a source DC (that has been used to create the
      // DIB section) to the DIB section.
      // Note that this function does not copy any transparent windows.
      // This function throwing an exception on a failure.
      virtual void blitToDibSection(const ::int_rectangle &  rect) = 0;

      // This function copies a block of bits from a source DC (that has been used to create the
      // DIB section) to the DIB section.
      // Note that this function copies transparent windows too.
      // This function throwing an exception on a failure.
      virtual void blitTransparentToDibSection(const ::int_rectangle &  rect) = 0;

      // This function copies a block of bits from the DIB section to the source DC
      // (that has been used to create the compatible DIB section).
      // Note that this function does not copy any transparent windows.
      // This function throwing an exception on a failure.
      virtual void blitFromDibSection(const ::int_rectangle &  rect) = 0;

      // This function copies with strech a block of bits from the DIB section to the source DC
      // (that has been used to create the compatible DIB section).
      // Note that this function does not copy any transparent windows.
      // This function throwing an exception on a failure.
      virtual void stretchFromDibSection(const ::int_rectangle &  srcRect,const ::int_rectangle & dstRect) = 0;

   //private:
      // Opens a new DIB section.
      // If targetDC == 0 the function will use a current desktop DC.
      //virtual void openDIBSection(const PixelFormat & pf, const ::int_size & dim, HWND compatibleWin) = 0;
      virtual void closeDIBSection() = 0;
      virtual void releaseTargetDC() = 0;

      // This function throwing an exception on a failure.
      virtual void blitToDibSection(const ::int_rectangle &  rect, unsigned int flags) = 0;

      // This function throwing an exception on a failure.
      virtual void blitFromDibSection(const ::int_rectangle &  rect, unsigned int flags) = 0;
      virtual void stretchFromDibSection(const ::int_rectangle &  srcRect,const ::int_rectangle & dstRect, unsigned int flags) = 0;

      //void setupBMIStruct(BITMAPINFO *pBmi, const PixelFormat & pf, const ::int_size & dim);

      // bool m_isOwnTargetDC;
      // HDC m_targetDC;
      // HDC m_memDC;
      // HBITMAP m_hbmOld;
      // HBITMAP m_hbmDIB;
      // // Coordinates of the source dc can be negative.
      // int m_srcOffsetX;
      // int m_srcOffsetY;
      //
      // void *m_buffer;
      //
      // Screen m_screen;
   };



   // This clas is a primitive wrapper to a DIB section.
   class CLASS_DECL_INNATE_SUBSYSTEM DibSectionComposite :
   virtual public Composite < DibSectionInterface >
   {
   public:


      ImplementCompositeø(DibSection, dibsection)

      // Note that if the compatibleWin doesn't specify or is zero the class will create an
      // DC for the entire screen. In this case an this object owner must provide
      // destructor calling from the same thread that called the constructor.
      // In default the created DC will used as a target DC for the blitting operations.
      // It may be changed many times later. Note that changed DC must be compatible with
      // the DIB section.
      //DibSection(const ::innate_subsystem::PixelFormat & pf, const ::int_size & dim, const ::operating_system::window & operatingsystemwindowCompatible = {});
      //DibSection();
      //~DibSection() override;


         void initialize_dib_section(const ::innate_subsystem::PixelFormat& pf, const ::int_size& dim, const ::operating_system::window& operatingsystemwindowCompatible = {}) override
      {

         m_pdibsection->initialize_dib_section(pf, dim, operatingsystemwindowCompatible);
      }

      // This function changes the target DC. In default target DC is a DC that has been
      // got from a compatible window on object creation. This function can be call many times.
      void setTargetDeviceContext(::innate_subsystem::DeviceContextInterface* pdevicecontext) override
      {
         m_pdibsection->setTargetDeviceContext(pdevicecontext);
      }

      void* getBuffer() override
      {

         return m_pdibsection->getBuffer();
      }

      // This function copies a block of bits from a source DC (that has been used to create the
      // DIB section) to the DIB section.
      // Note that this function does not copy any transparent windows.
      // This function throwing an exception on a failure.
      void blitToDibSection(const ::int_rectangle& rect) override
      {

         m_pdibsection->blitToDibSection(rect);
      }

      // This function copies a block of bits from a source DC (that has been used to create the
      // DIB section) to the DIB section.
      // Note that this function copies transparent windows too.
      // This function throwing an exception on a failure.
      void blitTransparentToDibSection(const ::int_rectangle& rect) override
      {
         m_pdibsection->blitTransparentToDibSection(rect);
      }

      // This function copies a block of bits from the DIB section to the source DC
      // (that has been used to create the compatible DIB section).
      // Note that this function does not copy any transparent windows.
      // This function throwing an exception on a failure.
      void blitFromDibSection(const ::int_rectangle& rect) override
      { m_pdibsection->blitFromDibSection(rect);
      }

      // This function copies with strech a block of bits from the DIB section to the source DC
      // (that has been used to create the compatible DIB section).
      // Note that this function does not copy any transparent windows.
      // This function throwing an exception on a failure.
      void stretchFromDibSection(const ::int_rectangle& srcRect, const ::int_rectangle& dstRect) override
      {
         m_pdibsection->stretchFromDibSection(srcRect, dstRect);
      }

   //private:
      // Opens a new DIB section.
      // If targetDC == 0 the function will use a current desktop DC.
      //void openDIBSection(const PixelFormat & pf, const ::int_size & dim, HWND compatibleWin);
      void closeDIBSection() override { m_pdibsection->closeDIBSection();
      }
      void releaseTargetDC() override { m_pdibsection->releaseTargetDC();
      }

      // This function throwing an exception on a failure.
      void blitToDibSection(const ::int_rectangle& rect, unsigned int flags) override
      {
         m_pdibsection->blitToDibSection(rect, flags);
      }

      // This function throwing an exception on a failure.
      void blitFromDibSection(const ::int_rectangle& rect, unsigned int flags) override
      {
         m_pdibsection->blitFromDibSection(rect, flags);
      }
      void stretchFromDibSection(const ::int_rectangle& srcRect, const ::int_rectangle& dstRect, unsigned int flags)
      {
         m_pdibsection->stretchFromDibSection(srcRect, dstRect, flags);
      }

      //void setupBMIStruct(BITMAPINFO *pBmi, const ::innate_subsystem::PixelFormat & pf, const ::int_size & dim);

      //
      // bool m_isOwnTargetDC;
      // HDC m_targetDC;
      // HDC m_memDC;
      // HBITMAP m_hbmOld;
      // HBITMAP m_hbmDIB;
      // // Coordinates of the source dc can be negative.
      // int m_srcOffsetX;
      // int m_srcOffsetY;
      //
      // void* m_buffer;
      //
      // Screen m_screen;
   };

   // This clas is a primitive wrapper to a DIB section.
   class CLASS_DECL_INNATE_SUBSYSTEM DibSectionAggregate :
   virtual public Composite < DibSectionComposite >
   {
   public:

      ImplementBaseø(DibSection)

   };

   class CLASS_DECL_INNATE_SUBSYSTEM DibSection :
   virtual public Object < DibSectionAggregate >
   {
   public:

   };


} // namespace innate_subsystem
