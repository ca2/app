#pragma once


namespace file
{


   class dynamic_buffered_writer:
      virtual public ::file::file
   {
   public:


      byte_dynamic_buffer _buffer;
      size_t _size;


      dynamic_buffered_writer() :
      _size(0)
      {
      }

      void Init()
      {
         _size = 0;  
      }
      
      size_t GetSize() const
      {
         return _size; 
      }
      
      const byte *GetBuffer() const
      {
         return _buffer; 
      }

      void CopyToBuffer(byte_buffer &dest) const;
      
      byte *GetBufPtrForWriting(size_t addSize);
      
      void UpdateSize(size_t addSize)
      {
         _size += addSize; 
      }

      using ::file::file::write;
      void write(const void *data, uptr size, uptr *processedSize);


   };


} // namespace file




