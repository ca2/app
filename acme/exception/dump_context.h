#pragma once


//////#include "acme/primitive/primitive/object.h"
//
//
//template < typename FILE >
//class CLASS_DECL_ACME dump_context :
//   virtual public text_stream <
//{
//public:
//
//
//   ::pointer<text_stream>    m_pstream;
//
//   
//   dump_context(::file::file * pfile = nullptr);
//   ~dump_context() override;
//
//
//   //virtual void destroy() override;
//
//
//   i32 GetDepth() const;      // 0 => this matter, 1 => children objects
//   void SetDepth(i32 nNewDepth);
//
//
//   //void write(const char * psz) override;
//
////
////#ifdef WINDOWS
////
////   void write(const unichar * psz) ; // automatically thinned
////
////#endif
////
////   void write(const ::string & str) override ;
////   void write(const void * p);
////          
////   void write(const ::particle * pparticle) override;
////   void write(const ::matter & matter) override;
////   void write(char i) override;
////   void write(uchar u)  override;
////   void write(i16 i) override;
////   void write(u16 u) override;
////   void write(i32 i) override;
////   void write(u32 u)  override;
////   void write(i64 i)  override;
////   void write(u64 u)  override;
////   void hex_dump(i8 i);
////   void hex_dump(u8 i);
////   void hex_dump(i16 i);
////   void hex_dump(u16 i);
////   void hex_dump(i32 i);
////   void hex_dump(u32 i);
////   void hex_dump(i64 i);
////   void hex_dump(u64 i);
////   void write(float f) override;
////   void write(double d) override;
//////   void write(oswindow h);
//////   void write(HDC h);
//////
//////#ifdef WINDOWS
//////   void write(HMENU h);
//////   void write(HACCEL h);
//////   void write(HFONT h);
//////
//////#endif
//////
////   void hex_dump(const char * pszLine, byte* pby, i32 nBytes, i32 nWidth);
////
////   void flush() override;
////
//   void output_string(const char * psz);
//
//protected:
//
//   i32 m_nDepth;
//
//
//};
//
//
//
