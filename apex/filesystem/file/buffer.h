//// Common/Buffer.h
//// from 7-zip
//#pragma once
//
//
//namespace file
//{
//
//
//   template <class T>
//   class buffer :
//      virtual public raw_array < T >
//   {
//   public:
//
//
//      buffer()
//      {
//
//      }
//
//      buffer(const buffer & buffer) :
//         raw_array < T > (buffer)
//      {
//
//      }
//
//      buffer(memsize size)
//      {
//
//         SetCapacity(size);
//
//      }
//
//      virtual ~buffer()
//      {
//
//      }
//
//      operator T *()
//      {
//
//         return this->get_data();
//
//      }
//
//      operator const T *() const
//      {
//
//         return this->get_data();
//
//      }
//
//
//      memsize GetCapacity() const
//      {
//
//         return  this->get_size();
//
//      }
//
//      void SetCapacity(memsize newCapacity)
//      {
//
//         this->allocate(newCapacity);
//
//      }
//
//      buffer & operator = (const buffer &buffer)
//      {
//
//         SetCapacity(buffer.GetCapacity());
//
//         if (buffer.GetCapacity() > 0)
//         {
//            ::memcpy_dup(this->get_data(), buffer.get_data(), buffer.GetCapacity() * sizeof(T));
//         }
//
//         return *this;
//
//      }
//
//
//      bool operator == (const buffer < T > & b) const
//      {
//
//         if(this->GetCapacity() != b.GetCapacity())
//            return false;
//
//         for (memsize i = 0; i < this->GetCapacity(); i++)
//            if (this->operator[](i) != b[i])
//               return false;
//
//         return true;
//
//      }
//
//
//      bool operator != (const buffer < T > & b) const
//      {
//         return !(*this == b);
//      }
//
//   };
//
//
//
//   typedef CLASS_DECL_APEX buffer < char >      char_buffer;
//   typedef CLASS_DECL_APEX buffer < unichar >   wchar_buffer;
//   typedef CLASS_DECL_APEX buffer < byte >      byte_buffer;
//
//
//} // namespace file
//
//
//
//
