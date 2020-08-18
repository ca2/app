#pragma once


namespace draw2d
{

   

   class CLASS_DECL_AURA bitmap :
      virtual public ::draw2d::object
   {
   public:


      int                  m_iStride;

#ifdef WINDOWS_DESKTOP

      HBITMAP              m_hbitmapGet;

#endif



      bitmap();
      virtual ~bitmap();

      virtual void dump(dump_context & dumpcontext) const;

      template < typename POINTER >
      inline POINTER get_os_data(i8 i = 0) const
      {

         return (POINTER)m_osdata[i];

      }


      inline void* get_os_data(i8 i = 0) const
      {

         return get_os_data < void * >(i);

      }


      virtual bool CreateBitmap(::draw2d::graphics * pgraphics, const ::size & size, UINT nPlanes, UINT nBitcount, const void * pBits, i32 stride);

      virtual bool CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP pBitmap);

      virtual bool CreateCompatibleBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight);
      virtual bool CreateDiscardableBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight);

      virtual bool CreateDIBSection(::draw2d::graphics * pgraphics, const ::size& size, UINT usage, void** ppcolorref, int* piScan, HANDLE hSection, u32 offset);
      virtual bool HostDIBSection(::draw2d::graphics * pgraphics, const pixmap * ppximap, UINT usage, HANDLE hSection, u32 offset);
      virtual bool CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy, u32 flInit, const void *pjBits, UINT iUsage);

      virtual bool attach(void * posdata);
      virtual void * detach();

      //virtual ::size SetBitmapDimension(i32 nWidth, i32 nHeight);
      //virtual ::size set_size(const ::size & size);

      virtual ::size GetBitmapDimension() const;
      virtual ::size get_size() const;
      virtual ::size size() const;

      // Operations
      virtual u32 SetBitmapBits(u32 dwCount, const void * pBits);

      virtual u32 GetBitmapBits(u32 dwCount, LPVOID pBits) const;




#ifdef WINDOWS_DESKTOP

      virtual HBITMAP GetHBITMAP();
      virtual void ReleaseHBITMAP(HBITMAP hbitmap);

      virtual HBITMAP _GetHBITMAP();
      virtual void _ReleaseHBITMAP(HBITMAP hbitmap);

#endif


   };


   typedef pointer < bitmap > bitmap_pointer;


} // namespace draw2d


#ifdef WINDOWS_DESKTOP


CLASS_DECL_AURA HBITMAP CreateHBITMAP(pixmap * ppixmap);
CLASS_DECL_AURA HBITMAP CreateHBITMAP2(pixmap * ppixmap);


#endif



