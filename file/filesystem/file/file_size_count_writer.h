#pragma once


namespace file
{


   class size_count_writer:
      virtual public writer
   {
   public:
      file_pointer     _stream;
      filesize         _size;

      void SetStream(writer * stream)
      {
         _stream = stream;
      }

      void Init()
      {
         _size = 0;
      }

      filesize get_size() const
      {
         return _size;
      }

      void write(const void *data, memsize size, memsize * processedSize);

   };


} // namespace file
