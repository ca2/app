#pragma once


namespace extended
{


   template < typename T >
   class transport :
      public __pointer(T),
      public ::extended::status
   {
   public:


      transport() :
         status(::error_not_initialized)
      {

      }


      transport(T * p) :
         ___pointer<T>(p)
      {

         if (this->is_null())
         {

            add(::error_null_result);

         }

      }


      template < typename TYPE >
      transport(const __pointer(TYPE) & p) :
         ___pointer<T>(p)
      {

         if (this->is_null())
         {

            add(::error_null_result);

         }

      }


      template < typename TYPE >
      transport(transport < TYPE > && p) :
         ___pointer<T>(::move(p)),
         ::extended::status(::move(p))
      {


      }


      transport(std::nullptr_t) :
         status(::error_failed)
      {

      }


      transport(::enum_status estatus) :
         status(estatus)
      {


      }


      transport(const ::e_status & estatus) :
         status(estatus)
      {

         add(estatus);

      }


      transport(const ::exception & e)
      {

         add(e);

      }


      transport(const std::initializer_list < ::exception > &list)
      {

         for (auto& e : list)
         {

            add(e);

         }

      }


      transport(const ::extended::status & status) :
         ::extended::status(status)
      {

           add(::error_null_result);

      }


      transport(const transport & transport) :
         __pointer(T)(transport),
         status(transport)
      {

      }


      transport(transport && transport) :
         __pointer(T)(::move(transport)),
         status(::move(transport))
      {

      }


      transport & operator =(std::nullptr_t)
      {

         this->release();

         m_estatus = ::error_failed;

         return *this;

      }


      transport & operator =(const ::e_status & estatus)
      {

         this->release();

         add(estatus);

         if (succeeded())
         {

            add(::error_null_result);

         }

         return *this;

      }


      transport & operator =(const ::extended::status & status)
      {

         this->release();

         status::operator=(status);

         if (succeeded())
         {

            add(::error_null_result);

         }

         return *this;

      }


      transport & operator =(extended::status && status)
      {

         this->release();

         status::operator=(::move(status));

         if (succeeded())
         {

            add(::error_null_result);

         }

         return *this;

      }


      transport & operator =(const transport & transport)
      {

         if (this != &transport)
         {

            __pointer(T)::operator =(transport);


            status::operator=(transport);

         }

         return *this;

      }

      transport & operator =(transport && transport)
      {

         __pointer(T)::operator =(::move(transport));

         status::operator=(::move(transport));

         return *this;

      }


      transport & operator =(const T * p)
      {

         __pointer(T)::operator =(p);

         if (this->is_null())
         {

            add(::error_null_result);

         }

         return *this;

      }


      template < typename TYPE >
      transport & operator =(const TYPE * p)
      {

         __pointer(T)::operator =(p);

         if (this->is_null())
         {

            if (::is_set(p))
            {

               add(::error_wrong_type);

            }
            else
            {

               add(::error_null_result);

            }

         }

         return *this;

      }


      transport & operator =(const __pointer(T) & p)
      {

         return this->operator = (p.m_p);

      }


      template < typename TYPE >
      transport & operator =(const __pointer(TYPE) & p)
      {

         return this->operator = (p.m_p);

      }


      bool not_initialized() const
      {

         return m_estatus == error_not_initialized;

      }


      ::e_status estatus() const
      {

         if (m_pexceptiona.is_null() || m_pexceptiona->is_empty())
         {

            if (__pointer(T)::is_null())
            {

               return error_null_result;

            }
            else
            {

               return ::success;

            }

         }
         else if (m_pexceptiona->get_size() == 1)
         {

            return m_pexceptiona->element_at(0).m_estatus;

         }
         else
         {

            for (auto& e : *m_pexceptiona)
            {

               if (::failed(e.m_estatus))
               {

                  return error_multiple;

               }

            }

            return success_multiple;

         }

      }

      bool succeeded() const { return ::succeeded(estatus()); }

      bool failed() const { return !succeeded(); }

      operator bool() const { return succeeded(); }

      operator ::e_status() const { return estatus(); }

      bool operator !() const { return failed(); }

      auto operator ->() { return ___pointer<T>::operator ->(); }

      auto operator ->() const { return ___pointer<T>::operator ->(); }


   };


   template < typename OBJECT >
   using sequence = ::sequence < OBJECT, ::extended::transport < OBJECT > >;


   template < typename OBJECT >
   using asynchronous = ::asynchronous < OBJECT, ::extended::transport < OBJECT >, ::extended::sequence < OBJECT > >;


} // namespace extended



template < typename TYPE >
inline bool is_set(const ::extended::transport < TYPE > & t)
{

   return is_set(t.m_p);

}



