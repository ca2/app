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
      _allBytesAreWritenEvent.set_happening();
      _thereAreBytesToReadEvent.reset_happening();
      _readStreamIsClosedEvent.reset_happening();
      return S_OK;
   }

   void stream_binder::ReInit()
   {
      _thereAreBytesToReadEvent.reset_happening();
      _readStreamIsClosedEvent.reset_happening();
      ProcessedSize = 0;
   }



   stream_binder::stream_binder(::particle * pparticle) :
      ::object(pparticle)
   {
   }


   void stream_binder::CreateStreams(::pointer<::file::file>& inStream, ::pointer<::file::file> outStream)
   {
      
      reader_for_binder * inStreamSpec = ___new reader_for_binder();
      inStreamSpec->set_binder(this);
      inStream = inStreamSpec;

      writer_for_binder *outStreamSpec = ___new writer_for_binder();
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
            ::memory_copy(data, _data, sizeToRead);
            _data += sizeToRead;
            _size -= sizeToRead;
            if(_size <= 0)
            {
               _thereAreBytesToReadEvent.reset_happening();
               _allBytesAreWritenEvent.set_happening();
            }
         }
      }
      ProcessedSize += sizeToRead;
      return sizeToRead;
   }

   
   void stream_binder::CloseRead()
   {
      
      _readStreamIsClosedEvent.set_happening();

   }


   void stream_binder::write(const void *data, memsize size, memsize * processedSize)
   {
      if (size > 0)
      {
         _data = (unsigned char *) data;
         _size = size;
         _allBytesAreWritenEvent.reset_happening();
         _thereAreBytesToReadEvent.set_happening();

         synchronization_array eva(this);
         eva.add(&_allBytesAreWritenEvent);
         eva.add(&_readStreamIsClosedEvent);
         if(!eva.wait(false, time::infinite()).signaled())
         {
            throw ::exception(error_resource);
         }
      }
      if (processedSize != nullptr)
         *processedSize = size;
   }


   void stream_binder::CloseWrite()
   {
      // _bufferSize must be = 0
      _thereAreBytesToReadEvent.set_happening();
   }


} // namespace file



