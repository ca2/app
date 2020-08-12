// Common/DynamicBuffer.h
#pragma once


namespace file
{


   template <class T> class dynamic_buffer: public buffer<T>
   {
     void GrowLength(size_t size)
     {
       size_t delta;
       if (this->GetCapacity() > 64)
         delta = this->GetCapacity() / 4;
       else if (this->GetCapacity() > 8)
         delta = 16;
       else
         delta = 4;
       delta = MAX(delta, size);
       size_t newCap = this->GetCapacity() + delta;
       if (newCap < delta)
         newCap = this->GetCapacity() + size;
         buffer < T > ::SetCapacity(newCap);
     }
   public:
     dynamic_buffer(): buffer<T>() {};
     dynamic_buffer(const dynamic_buffer &buffer): ::file::buffer<T>(buffer) {};
     dynamic_buffer(size_t size): buffer<T>(size) {};
     dynamic_buffer& operator=(const dynamic_buffer &buffer)
     {
       this->remove_all();
       if (buffer.get_size() > 0)
       {
         this->SetCapacity(buffer.get_size());
         __memmov(this->get_data(), buffer.get_data(), buffer.get_size() * sizeof(T));
       }
       return *this;
     }
     void EnsureCapacity(size_t capacity)
     {
       if (this->GetCapacity() < capacity)
         GrowLength(capacity - this->GetCapacity());
     }

   };


   typedef dynamic_buffer < char >     char_dynamic_buffer;
   typedef dynamic_buffer < unichar > wchar_dynamic_buffer;
   typedef dynamic_buffer < byte >     byte_dynamic_buffer;


} // namespace file




