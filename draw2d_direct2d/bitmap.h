#pragma once


namespace draw2d_direct2d
{


   class CLASS_DECL_DRAW2D_DIRECT2D bitmap :
      virtual public ::draw2d_direct2d::object,
      virtual public ::draw2d::bitmap

   {
   public:


      enum e_data
      {

         data_bitmap,
         data_bitmap1,

      };


      Microsoft::WRL::ComPtr<ID2D1Bitmap>    m_pbitmap;
      Microsoft::WRL::ComPtr<ID2D1Bitmap1>   m_pbitmap1;
      D2D1_MAPPED_RECT                       m_map;
      memory                                 m_memory;



      bitmap();
      virtual ~bitmap();


      bool LoadBitmap(const char * lpszResourceName);
      bool LoadBitmap(UINT nIDResource);
      bool LoadOEMBitmap(UINT nIDBitmap); // for OBM_/OCR_/OIC_


      virtual bool CreateBitmap(::draw2d::graphics * pgraphics, const ::size& size, UINT nPlanes, UINT nBitcount, const void * lpBits, int stride) override;
      virtual bool CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP lpBitmap);
      virtual bool CreateCompatibleBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight);
      virtual bool CreateDiscardableBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight);
      virtual bool create_bitmap(::draw2d::graphics * pgraphics, const ::size & size, void **ppvBits, int * stride) override;
      virtual bool CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy, u32 flInit, const void *pjBits, UINT iUsage) override;


      virtual bool attach(void * posdata);
      virtual void * detach();

      virtual void defer_update(::draw2d::graphics * pgraphics) const;

      u32 SetBitmapBits(u32 dwCount, const void * lpBits);
      u32 GetBitmapBits(u32 dwCount, LPVOID lpBits) const;
      //::size SetBitmapDimension(int nWidth, int nHeight);
      ::size GetBitmapDimension() const;

      virtual void dump(dump_context & dumpcontext) const;

      virtual void destroy() override;


   };


} // namespace draw2d_direct2d



