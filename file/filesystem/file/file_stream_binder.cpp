// StreamBinder.cpp
// from 7-zip on dawn of 13/01/2001 - Thursday
#include "framework.h"


namespace file
{


   class reader_for_binder:
      public ::file::file
   {
   public:

      
      stream_binder * m_StreamBinder;


      ~reader_for_binder() { m_StreamBinder->CloseRead(); }
      
      virtual memsize read(void *data, memsize size);

      void set_binder(stream_binder *streamBinder) { m_StreamBinder = streamBinder; }

   };

   memsize reader_for_binder::read(void *data, memsize size)
   { 
      return m_StreamBinder->read(data, size); 
   }

   class writer_for_binder:
      public ::file::file
   {
   public:


      stream_binder *m_StreamBinder;

      
      ~writer_for_binder() {  m_StreamBinder->CloseWrite(); }

      virtual void write(const void *lpBuf, memsize nCount, memsize * dwWritten);

      void set_binder(stream_binder *streamBinder) { m_StreamBinder = streamBinder; }

   };

   void writer_for_binder::write(const void *data, memsize size, memsize *processedSize)
   { 
      return m_StreamBinder->write(data, size, processedSize); 
   }


   //////////////////////////
   // stream_binder
   // (_thereAreBytesToReadEvent && _bufferSize == 0) means that stream is finished.

   HRes stream_binder::CreateEvents()
   {
      _allBytesAreWritenEvent.SetEvent();
      _thereAreBytesToReadEvent.ResetEvent();
      _readStreamIsClosedEvent.ResetEvent();
      return S_OK;
   }

   void stream_binder::ReInit()
   {
      _thereAreBytesToReadEvent.ResetEvent();
      _readStreamIsClosedEvent.ResetEvent();
      ProcessedSize = 0;
   }



   stream_binder::stream_binder(::layered * pobjectContext) :
      ::object(pobject)
   {
   }


   void stream_binder::CreateStreams(__pointer(::file::file) & inStream, __pointer(::file::file) & outStream)
   {
      
      reader_for_binder * inStreamSpec = new reader_for_binder;
      inStreamSpec->set_binder(this);
      inStream = inStreamSpec;

      writer_for_binder *outStreamSpec = new writer_for_binder;
      outStreamSpec->set_binder(this);
      outStream = outStreamSpec;

      _data = nullptr;
      _size = 0;
      ProcessedSize = 0;

   }

   memsize stream_binder::read(void *data, memsize size)
   {
      memsize sizeToRead = size;
      if(size > 0)
      {
         _thereAreBytesToReadEvent.wait();
         sizeToRead = minimum(_size, size);
         if(_size > 0)
         {
            ::memcpy_dup(data, _data, sizeToRead);
            _data += sizeToRead;
            _size -= sizeToRead;
            if(_size <= 0)
            {
               _thereAreBytesToReadEvent.ResetEvent();
               _allBytesAreWritenEvent.SetEvent();
            }
         }
      }
      ProcessedSize += sizeToRead;
      return sizeToRead;
   }

   
   void stream_binder::CloseRead()
   {
      
      _readStreamIsClosedEvent.SetEvent();

   }


   void stream_binder::write(const void *data, memsize size, memsize * processedSize)
   {
      if (size > 0)
      {
         _data = (byte *) data;
         _size = size;
         _allBytesAreWritenEvent.ResetEvent();
         _thereAreBytesToReadEvent.SetEvent();

         synchronization_array eva(get_object());
         eva.add(&_allBytesAreWritenEvent);
         eva.add(&_readStreamIsClosedEvent);
         if(!eva.wait(false, duration::infinite()).signaled())
         {
            __throw(resource_exception());
         }
      }
      if (processedSize != nullptr)
         *processedSize = size;
   }


   void stream_binder::CloseWrite()
   {
      // _bufferSize must be = 0
      _thereAreBytesToReadEvent.SetEvent();
   }


} // namespace file



