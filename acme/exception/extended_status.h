#pragma once


CLASS_DECL_ACME const char * status_message(const ::e_status & estatus);


namespace extended
{


   class CLASS_DECL_ACME status
   {
   public:



      /// Curitiba, 2 de abril de 2019
      ///
      /// m_estatus is light-weight failure/success indication
      /// Also it is cached information.
      /// It is required. So if exceptions are added to
      /// m_pexceptiona, they should reflect just more detailed
      /// information about a properly filled m_estatus.
      /// No specific exception or detailed information is really required
      /// through m_pexceptiona.
      /// m_estatus indication is enough.
      /// This way two things are enabled:
      /// - Success/failure compact indication is easily available (through m_estatus)
      /// - Simple/frequent failures/exceptions doesn't require the implementator
      ///   to fill and spend resources creating exception data that would be
      ///   rarely queried.

      ::e_status                       m_estatus;
      __pointer(::exception_array)     m_pexceptiona;


      status():m_estatus(undefined) { }
      status(::enum_status estatus) : m_estatus(estatus) { }
      status(const ::e_status & estatus) : m_estatus(estatus) { }
      status(const std::initializer_list < ::e_status > & list) :
      m_estatus(undefined)
      {
         add(list);

      }
      status(const status& status) :
         m_estatus(status.m_estatus),
         m_pexceptiona(status.m_pexceptiona)
      {
      }
      status(status&& status) :
         m_estatus(status.m_estatus),
         m_pexceptiona(move(status.m_pexceptiona))
      {
      }
      status(const ::exception::exception & e) :m_estatus(undefined){  add(e); }
      status(const std::initializer_list < ::exception::exception > & list) :m_estatus(undefined){ add(list);}
      ~status() {}


      static void set_skip_callstack(i32 iStack);
      static i32 get_skip_callstack();

      void set(const ::e_status & estatus) { set(estatus.m_estatus);}

      void set(::enum_status estatus)
      {

         m_pexceptiona.release();

         m_estatus = estatus;

      }

      void add(const ::e_status & estatus) { add(estatus.m_estatus);}

      void add(::enum_status estatus) { add(::exception::exception(estatus)); }

      void add(const ::exception::exception & e)
      {

         if (m_pexceptiona.is_null())
         {

            m_pexceptiona = __new(::array < ::exception::exception >);

            if (m_estatus != undefined)
            {

               add(m_estatus);

            }

         }

         m_pexceptiona->add(e);

         if (m_estatus == undefined)
         {

            if (::succeeded(e.m_estatus))
            {

               m_estatus = error_exception;

            }
            else
            {

               m_estatus = e.m_estatus;

            }

         }
         else
         {

            m_estatus = error_multiple;

         }

      }


      void add(const std::initializer_list < ::exception::exception > & list)
      {

         for (auto & e : list)
         {

            add(e);

         }

      }


      void add(const std::initializer_list < ::e_status     > & list)
      {

         for (auto & e : list)
         {

            add(e);

         }

      }


      bool get_exception(::exception::exception & e, const ::e_status & estatus)
      {

         if (m_estatus == estatus)
         {

            e = ::exception::exception(m_estatus);

            return true;

         }

         if (!m_pexceptiona)
         {

            return false;

         }

         for (auto & exception : *m_pexceptiona)
         {

            if (exception.m_estatus == estatus)
            {

               e = exception;

               return true;

            }

         }

         return false;

      }


      bool get_exit_status(::e_status & estatus) const
      {

         auto estatusExit = get_greatest_exception_on_range(error_exit_start, error_exit_end);

         if (estatusExit == error_not_found)
         {

            return false;

         }

         estatus = estatusExit;

         return true;

      }


      ::e_status get_greatest_exception_on_range(enum_status estatusOpenStart, enum_status estatusOpenEnd) const
      {

         ::e_status estatus = ::error_not_found;

         if (m_pexceptiona)
         {

            for (auto& exception : *m_pexceptiona)
            {

               if (exception.m_estatus > estatusOpenStart
                  && exception.m_estatus < estatusOpenEnd)
               {

                  if (estatus == error_not_found ||
                     estatus > exception.m_estatus)
                  {

                     estatus = exception.m_estatus;

                  }

               }

            }

         }

         return estatus;

      }


      bool has(const ::e_status & estatus) const
      {

         if (m_estatus == estatus)
         {

            return true;

         }

         if (m_pexceptiona.is_set())
         {

            for (auto& exception : *m_pexceptiona)
            {

               if (exception.m_estatus == estatus)
               {

                  return true;

               }

            }

         }

         return false;

      }


      static string get_error_text(const ::e_status & estatus);

      
      ::e_status estatus() const
      {

         return m_estatus == undefined ? ::e_status(::success) : m_estatus;
      }

      bool succeeded() const { return ::succeeded(estatus()); }

      bool failed() const { return !succeeded(); }

      operator bool() const { return succeeded(); }

      bool operator !() const { return failed(); }

      status & operator =(const ::e_status & estatus)
      {

         set(estatus);

         return *this;

      }

      status& operator =(::enum_status estatus){return operator =((const ::e_status &) estatus);}

      status& operator =(const status& status)
      {

         if (this != &status)
         {

            m_estatus         = status.m_estatus;
            m_pexceptiona  = status.m_pexceptiona;

         }

         return *this;

      }


      status& operator =(status&& status)
      {

         m_estatus = status.m_estatus;
         m_pexceptiona = ::move(status.m_pexceptiona);

         return *this;

      }


      void clear() { m_pexceptiona.release(); m_estatus = undefined; }


      void add(const status& status)
      {

         if (status.m_pexceptiona.is_set() && status.m_pexceptiona->has_elements())
         {

            for (auto & pexception : *status.m_pexceptiona)
            {

               add(pexception);

            }

         }
         else if (status.m_estatus != undefined)
         {

            add(status.m_estatus);

         }

      }

      void set_error(const ::e_status & estatus)
      {

         set(estatus);

         if (succeeded())
         {

            m_estatus = error_status;

         }

      }


   };


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
      transport(transport&& p) :
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


      transport(const ::exception::exception & e)
      {

         add(e);

      }


      transport(const std::initializer_list < ::exception::exception > &list)
      {

         for(auto & e : list)
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

         result::operator=(::error_failed);

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


      transport & operator =(extended::status&& status)
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

      bool operator !() const { return failed(); }

      auto operator ->() { return ___pointer<T>::operator ->(); }

      auto operator ->() const { return ___pointer<T>::operator ->(); }


   };

   template < typename OBJECT >
   using future = ::future < OBJECT, ::extended::transport < OBJECT > >;

   template < typename OBJECT >
   using asynchronous = ::asynchronous < OBJECT, ::extended::transport < OBJECT >, ::extended::future < OBJECT > >;


} // namespace extended


//using exception_pointer = ::exception::exception_pointer;

template < typename EXCEPTION >
inline __pointer(EXCEPTION) __move_throw_exception(EXCEPTION * pexceptionNew);

CLASS_DECL_ACME __pointer(::exception::exception) __trace_context_move_throw_exception(::matter * pobject, ::exception::exception * pexceptionNew);



#define __throw(...) throw(::exception::exception(__VA_ARGS__))
#define __rethrow(pe) throw pe;
#define __throw_exit(estatus) __throw(exit_exception(estatus))




//#define rp(T) ::transport < T >


using unexpected_situation = ::exception::exception;




