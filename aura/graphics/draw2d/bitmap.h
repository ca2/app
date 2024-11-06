#pragma once


#include "object.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/geometry2d/size.h"


namespace draw2d
{



   class CLASS_DECL_AURA bitmap :
      virtual public ::draw2d::object
   {
   public:


      ::int_size               m_size;
      int                  m_iStride;

//#ifdef WINDOWS_DESKTOP
//
//      HBITMAP              m_hbitmapGet;
//
//#endif



      bitmap();
      ~bitmap() override;


      // void dump(dump_context & dumpcontext) const override;


      template < typename POINTER >
      inline POINTER get_os_data(char i = 0) const
      {

         return (POINTER)m_osdata[i];

      }


      inline void* get_os_data(char i = 0) const
      {

         return get_os_data < void * >(i);

      }


      virtual void CreateBitmap(::draw2d::graphics * pgraphics, const ::int_size & size, unsigned int nPlanes, unsigned int nBitcount, const void * pBits, int stride);

      //virtual bool CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP pBitmap);

      virtual void CreateCompatibleBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight);
      virtual void CreateDiscardableBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight);

      virtual void create_bitmap(::draw2d::graphics * pgraphics, const ::int_size& size, void** ppcolorref, int* piScan);
      virtual bool host_bitmap(::draw2d::graphics* pgraphics, pixmap* ppximap);
      virtual void CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy, unsigned int flInit, const void *pjBits, unsigned int iUsage);

      virtual int stride_for_width(int iWidth);

      virtual void attach(void * posdata);
      virtual void * detach();

      //virtual ::int_size SetBitmapDimension(int nWidth, int nHeight);
      //virtual ::int_size set_size(const ::int_size & size);

      virtual ::int_size GetBitmapDimension() const;
      virtual ::int_size get_size() const;
      virtual ::int_size size() const;

      
      virtual unsigned int SetBitmapBits(unsigned int dwCount, const void * pBits);

      virtual unsigned int GetBitmapBits(unsigned int dwCount, void * pBits) const;


//
//
//#ifdef WINDOWS_DESKTOP
//
//      virtual HBITMAP GetHBITMAP();
//      virtual void ReleaseHBITMAP(HBITMAP hbitmap);
//
//      virtual HBITMAP _GetHBITMAP();
//      virtual void _ReleaseHBITMAP(HBITMAP hbitmap);
//
//#endif
//

   };


   typedef ::pointer<bitmap>bitmap_pointer;


} // namespace draw2d





