// StreamBinder.h
// from 7-zip on dawn of 13/01/2001 - Thursday
#pragma once





namespace file
{

   class CLASS_DECL_CA2_FILE stream_binder :
      virtual public ::object
   {
   public:
      
      
      manual_reset_event   _allBytesAreWritenEvent;
      manual_reset_event   _thereAreBytesToReadEvent;
      manual_reset_event   _readStreamIsClosedEvent;
      byte *               _data;
      uptr            _size;
      uptr            ProcessedSize;


      stream_binder(::layered * pobjectContext);
      HRes CreateEvents();

      virtual void CreateStreams(__pointer(::file::file) & inStream, __pointer(::file::file) & outStream);

      virtual memsize read(void *lpBuf, memsize nCount);
      virtual void CloseRead();

      virtual void write(const void *lpBuf, memsize nCount, memsize * dwWritten);
      virtual void CloseWrite();

      virtual void ReInit();
   };


} // namespace file




