#pragma once


namespace file
{


   class CLASS_DECL_APEX stream2 :
      virtual public stream
   {
   public:


      stream2();
      stream2(::file::file * pwriter);
      virtual ~stream2();


      stream2 & operator << (uchar uch);
      stream2 & operator << (u16 ui);
      stream2 & operator << (i32 i);
      stream2 & operator << (u32 ui);
      stream2 & operator << (const POINT * ppoint);
      stream2 & operator << (const SIZE * ppoint);
      stream2 & operator << (const RECT * ppoint);
      stream2 & operator << (const char * psz);
      stream2 & operator << (const string & str);


   };


} // namespace file



