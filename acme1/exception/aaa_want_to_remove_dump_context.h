#pragma once


class CLASS_DECL_ACME dump_context :
   virtual public ::generic
   //public text_stream
{
public:

   file_pointer   m_p;

   dump_context(file_pointer pfile = nullptr);


   i32 GetDepth() const;      // 0 => this generic, 1 => children objects
   void SetDepth(i32 nNewDepth);


   void write(const char * psz);


#ifdef WINDOWS

   void write(const unichar * psz) ; // automatically thinned

#endif

   void write(const string & str) ;
   void write(const void * p);
          
   void write(const ::generic * pobject) ;
   void write(const ::generic & generic) ;
   void write(char i) ;
   void write(uchar ui) ;
   void write(i16 i) ;
   void write(u16 ui) ;
   void write(i32 i) ;
   void write(u32 ui) ;
   void write(i64 i) ;
   void write(u64 ui) ;
   void hex_dump(i8 i);
   void hex_dump(u8 i);
   void hex_dump(i16 i);
   void hex_dump(u16 i);
   void hex_dump(i32 i);
   void hex_dump(u32 i);
   void hex_dump(i64 i);
   void hex_dump(u64 i);
   void write(float f);
   void write(double d);
   void write(oswindow h);
   void write(HDC h);

#ifdef WINDOWS
   void write(HMENU h);
   void write(HACCEL h);
   void write(HFONT h);

#endif

   void hex_dump(const char * pszLine, BYTE* pby, i32 nBytes, i32 nWidth);

   void flush();

   void output_string(const char * psz);

protected:

   i32 m_nDepth;


};



