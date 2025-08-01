#pragma once


//////#include "acme/prototype/prototype/object.h"
//
//
//// template < typename FILE >
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
//   int GetDepth() const;      // 0 => this matter, 1 => children objects
//   void SetDepth(int nNewDepth);
//
//
//   //void write(const ::scoped_string & scopedstr) override;
//
////
////#ifdef WINDOWS
////
////   void write(const unichar * psz) ; // automatically thinned
////
////#endif
////
////   void write(const ::scoped_string & scopedstr) override ;
////   void write(const void * p);
////          
////   void write(const ::particle * pparticle) override;
////   void write(const ::matter & matter) override;
////   void write(char i) override;
////   void write(uchar u)  override;
////   void write(short i) override;
////   void write(unsigned short u) override;
////   void write(int i) override;
////   void write(unsigned int u)  override;
////   void write(long long i)  override;
////   void write(unsigned long long u)  override;
////   void hex_dump(char i);
////   void hex_dump(unsigned char i);
////   void hex_dump(short i);
////   void hex_dump(unsigned short i);
////   void hex_dump(int i);
////   void hex_dump(unsigned int i);
////   void hex_dump(long long i);
////   void hex_dump(unsigned long long i);
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
////   void hex_dump(const ::scoped_string & scopedstrLine, unsigned char* pby, int nBytes, int nWidth);
////
////   void flush() override;
////
//   void output_string(const ::scoped_string & scopedstr);
//
//protected:
//
//   int m_nDepth;
//
//
//};
//
//
//
