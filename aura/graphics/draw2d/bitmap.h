#pragma once


namespace draw2d
{



   class CLASS_DECL_AURA bitmap :
      virtual public ::draw2d::object
   {
   public:


      ::size_i32               m_size;
      int                  m_iStride;

//#ifdef WINDOWS_DESKTOP
//
//      HBITMAP              m_hbitmapGet;
//
//#endif



      bitmap();
      virtual ~bitmap();

      void dump(dump_context & dumpcontext) const override;

      template < typename POINTER >
      inline POINTER get_os_data(i8 i = 0) const
      {

         return (POINTER)m_osdata[i];

      }


      inline void* get_os_data(i8 i = 0) const
      {

         return get_os_data < void * >(i);

      }


      virtual bool CreateBitmap(::draw2d::graphics * pgraphics, const ::size_i32 & size, ::u32 nPlanes, ::u32 nBitcount, const void * pBits, i32 stride);

      //virtual bool CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP pBitmap);

      virtual bool CreateCompatibleBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight);
      virtual bool CreateDiscardableBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight);

      virtual bool create_bitmap(::draw2d::graphics * pgraphics, const ::size_i32& size, void** ppcolorref, int* piScan);
      virtual bool host_bitmap(::draw2d::graphics* pgraphics, const pixmap* ppximap);
      virtual bool CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy, u32 flInit, const void *pjBits, ::u32 iUsage);

      virtual bool attach(void * posdata);
      virtual void * detach();

      //virtual ::size_i32 SetBitmapDimension(i32 nWidth, i32 nHeight);
      //virtual ::size_i32 set_size(const ::size_i32 & size);

      virtual ::size_i32 GetBitmapDimension() const;
      virtual ::size_i32 get_size() const;
      virtual ::size_i32 size() const;

      // Operations
      virtual u32 SetBitmapBits(u32 dwCount, const void * pBits);

      virtual u32 GetBitmapBits(u32 dwCount, void * pBits) const;


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


   typedef ___pointer < bitmap > bitmap_pointer;


} // namespace draw2d





