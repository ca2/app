#pragma once

//
//namespace extended
//{
//
//
//   template < typename T >
//   class transport :
//      public pointer < T >,
//      public ::extended::status
//   {
//   public:
//
//
//      transport() :
//         status(::error_not_initialized)
//      {
//
//      }
//
//      template < typename T2 >
//      transport(T2 * p) :
//         pointer<T>(p)
//      {
//
//         if (this->is_null())
//         {
//
//            add(::error_null_result);
//
//         }
//
//      }
//
//
//      template < typename TYPE >
//      transport(const ::pointer<TYPE>& p) :
//         pointer<T>(p),
//         ::extended::status(::is_null(this->m_p) ? error_null_result : ::success)
//      {
//
//      }
//
//
//      template < typename TYPE >
//      transport(::pointer<TYPE>& p) :
//         pointer<T>(::transfer(p)),
//         ::extended::status(::is_null(this->m_p) ? error_null_result : ::success)
//      {
//
//      }
//
//
//      template < typename TYPE >
//      transport(transport < TYPE > && p) :
//         pointer<T>(::transfer(p)),
//         ::extended::status(::transfer(p))
//      {
//
//
//      }
//
//
//      transport(nullptr_t) :
//         status(::error_failed)
//      {
//
//      }
//
//
//      transport(::enum_status estatus) :
//         status(estatus)
//      {
//
//
//      }
//
//
//      transport(const ::e_status & estatus) :
//         status(estatus)
//      {
//
//         add(estatus);
//
//      }
//
//
//      transport(const ::exception & e)
//      {
//
//         add(e);
//
//      }
//
//
//      transport(const std::initializer_list < ::exception > &list_base)
//      {
//
//         for (auto& e : list_base)
//         {
//
//            add(e);
//
//         }
//
//      }
//
//
//      transport(const ::extended::status & status) :
//         ::extended::status(status)
//      {
//
//           add(::error_null_result);
//
//      }
//
//
//      transport(const transport & transport) :
//         pointer < T >(transport),
//         status(transport)
//      {
//
//      }
//
//
//      transport(transport && transport) :
//         pointer < T >(::transfer(transport)),
//         status(::transfer(transport))
//      {
//
//      }
//
//
//      transport & operator =(nullptr_t)
//      {
//
//         this->release();
//
//         m_estatus = ::error_failed;
//
//         return *this;
//
//      }
//
//
//      // set main status
//      transport & operator =(const ::e_status & estatus)
//      {
//
//         m_estatus = estatus;
//
//         if (failed())
//         {
//
//            this->release();
//
//         }
//
//         return *this;
//
//      }
//
//
//      transport& operator =(const ::enum_status& estatus)
//      {
//
//         return this->operator = ((const void&) estatus);
//
//      }
//
//
//      transport & operator =(const ::extended::status & status)
//      {
//
//         this->release();
//
//         status::operator=(status);
//
//         if (succeeded())
//         {
//
//            add(::error_null_result);
//
//         }
//
//         return *this;
//
//      }
//
//
//      transport & operator =(extended::status && status)
//      {
//
//         this->release();
//
//         status::operator=(::transfer(status));
//
//         if (succeeded())
//         {
//
//            add(::error_null_result);
//
//         }
//
//         return *this;
//
//      }
//
//
//      transport & operator =(const transport & transport)
//      {
//
//         if (this != &transport)
//         {
//
//            pointer < T >::operator =(transport);
//
//
//            status::operator=(transport);
//
//         }
//
//         return *this;
//
//      }
//
//      transport & operator =(transport && transport)
//      {
//
//         pointer < T >::operator =(::transfer(transport));
//
//         status::operator=(::transfer(transport));
//
//         return *this;
//
//      }
//
//      template < typename T2 >
//      transport & operator =(T2 * p)
//      {
//
//         pointer < T >::operator =(p);
//
//         if (this->is_null())
//         {
//
//            add(::error_null_result);
//
//         }
//
//         return *this;
//
//      }
//
//
//      template < typename TYPE >
//      transport & operator =(const TYPE * p)
//      {
//
//         pointer < T >::operator =(p);
//
//         if (this->is_null())
//         {
//
//            if (::is_set(p))
//            {
//
//               add(::error_wrong_type);
//
//            }
//            else
//            {
//
//               add(::error_null_result);
//
//            }
//
//         }
//
//         return *this;
//
//      }
//
//
//      transport & operator =(const pointer < T > & p)
//      {
//
//         return this->operator = (p.m_p);
//
//      }
//
//
//      template < typename TYPE >
//      transport & operator =(const ::pointer<TYPE>& p)
//      {
//
//         return this->operator = (p.m_p);
//
//      }
//
//
//      bool is_initialized() const
//      {
//
//         return m_estatus != error_not_initialized;
//
//      }
//
//
//      bool not_initialized() const
//      {
//
//         return !is_initialized();
//
//      }
//
//
//      ::e_status estatus() const
//      {
//
//         return m_estatus;
//
//         //if (m_pexceptiona.is_null() || m_pexceptiona->is_empty())
//         //{
//
//         //   if (pointer < T >::is_null())
//         //   {
//
//         //      return error_null_result;
//
//         //   }
//         //   else
//         //   {
//
//         //      return ::success;
//
//         //   }
//
//         //}
//         //else if (m_pexceptiona->get_size() == 1)
//         //{
//
//         //   return m_pexceptiona->element_at(0).m_estatus;
//
//         //}
//         //else
//         //{
//
//         //   for (auto& e : *m_pexceptiona)
//         //   {
//
//         //      if (::failed(e.m_estatus))
//         //      {
//
//         //         return error_multiple;
//
//         //      }
//
//         //   }
//
//         //   return success_multiple;
//
//         //}
//
//      }
//
//      bool succeeded() const { return ::succeeded(estatus()); }
//
//      bool failed() const { return !succeeded(); }
//
//      operator bool() const { return succeeded(); }
//
//      operator void() const { return estatus(); }
//
//      bool operator !() const { return failed(); }
//
//      auto operator ->() { return pointer<T>::operator ->(); }
//
//      auto operator ->() const { return pointer<T>::operator ->(); }
//
//
//   };
//
//
//   template < typename OBJECT >
//   using sequence = ::sequence < OBJECT, ::extended::transport < OBJECT > >;
//
//
//   template < typename OBJECT >
//   using asynchronous = ::asynchronous < OBJECT, ::extended::transport < OBJECT >, ::extended::sequence < OBJECT > >;
//
//
//} // namespace extended
//


template < typename TYPE >
inline bool is_set(const ::extended::transport < TYPE > & t)
{

   return is_set(t.m_p);

}



