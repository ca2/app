#pragma once


CLASS_DECL_AURA const char * status_message(const ::estatus & estatus);


namespace status
{


   class CLASS_DECL_AURA result
   {
   public:


      static i32 s_iSkipCallStack;

      /// Curitiba, 2 de abril de 2019
      ///
      /// m_estatus is light-weight failure/success indication
      /// Also it is cached information.
      /// It is required. So if exceptions are added to
      /// m_pexceptionptra, they should reflect just more detailed
      /// information about a properly filled m_estatus.
      /// No specific exception or detailed information is really required
      /// through m_pexceptionptra.
      /// m_estatus indication is enough.
      /// This way two things are enabled:
      /// - Success/failure compact indication is easily available (through m_estatus)
      /// - Simple/frequent failures/exceptions doesn't require the implementator
      ///   to fill and spend resources creating exception data that would be
      ///   rarely queried.

      ::estatus                                m_estatus;
      __pointer(__pointer_array(::exception::exception))     m_pexceptionptra;


      result():m_estatus(undefined) { }
      result(::enum_status estatus) : m_estatus(estatus) { }
      result(const ::estatus & estatus) : m_estatus(estatus) { }
      result(const std::initializer_list < ::estatus > & list) :
      m_estatus(undefined)
      {
         add(list);

      }
      result(const result & result) :
         m_estatus(result.m_estatus),
         m_pexceptionptra(result.m_pexceptionptra)
      {
      }
      result(result && result) :
         m_estatus(result.m_estatus),
         m_pexceptionptra(move(result.m_pexceptionptra))
      {
      }
      result(::exception::exception * pe) :m_estatus(undefined){  add(pe); }
      result(const std::initializer_list < ::exception_pointer > & list) :m_estatus(undefined){ add(list);}
      ~result() {}


      static void set_skip_callstack(i32 iStack);

      void set(const ::estatus & estatus) { set(estatus.m_estatus);}

      void set(::enum_status estatus)
      {

         m_pexceptionptra.release();

         m_estatus = estatus;

      }

      void add(const ::estatus & estatus) { add(estatus.m_estatus);}

      void add(::enum_status estatus)
      {

         if (m_estatus == undefined)
         {

            m_estatus = estatus;

         }
         else
         {

            add(__new(::exception::exception(estatus, s_iSkipCallStack)));

         }

      }

      void add(::exception::exception * pe)
      {

         if (m_pexceptionptra.is_null())
         {

            m_pexceptionptra = __new(__pointer_array(::exception::exception));

            if (m_estatus != undefined)
            {

               add(m_estatus);

            }

         }

         m_pexceptionptra->add(pe);

         if (m_estatus == undefined)
         {

            if (::succeeded(pe->m_estatus))
            {

               m_estatus = error_exception;

            }
            else
            {

               m_estatus = pe->m_estatus;

            }

         }
         else
         {

            m_estatus = error_multiple;

         }

      }


      void add(const std::initializer_list < ::exception_pointer > & list)
      {

         for (auto & e : list)
         {

            add(e);

         }

      }


      void add(const std::initializer_list < ::estatus     > & list)
      {

         for (auto & e : list)
         {

            add(e);

         }

      }

      template < typename EXCEPTION >
      __pointer(EXCEPTION) get_exception()
      {

         if (m_pexceptionptra.is_null())
         {

            if (::failed(m_estatus))
            {

               return __new(::exception::exception(m_estatus, s_iSkipCallStack));

            }

            return nullptr;

         }

         for (auto & pexception : *m_pexceptionptra)
         {

            __pointer(EXCEPTION) pe = pexception;

            if (pe.is_set())
            {

               return pe;

            }

         }

         return nullptr;

      }

      template < typename TYPE >
      bool has() const
      {

         if (m_pexceptionptra.is_set())
         {

            if(m_pexceptionptra->has < TYPE >())
            {

               return true;

            }

         }

         return false;

      }

      static string get_error_text(const ::estatus & estatus);

      ::estatus     status() const
      {

         return m_estatus == undefined ? ::estatus(::success) : m_estatus;
      }

      bool succeeded() const { return ::succeeded(status()); }

      bool failed() const { return !succeeded(); }

      operator bool() const { return succeeded(); }

      bool operator !() const { return failed(); }

      result & operator =(const ::estatus & estatus)
      {

         set(estatus);

         return *this;

      }

      result & operator =(::enum_status estatus){return operator =((const ::estatus &) estatus);}

      result & operator =(const result & result)
      {

         if (this != &result)
         {

            m_estatus         = result.m_estatus;
            m_pexceptionptra  = result.m_pexceptionptra;

         }

         return *this;

      }


      result & operator =(result && result)
      {

         m_estatus = result.m_estatus;
         m_pexceptionptra = ::move(result.m_pexceptionptra);

         return *this;

      }


      void clear() { m_pexceptionptra.release(); m_estatus = undefined; }


      void add(const result & result)
      {

         if (result.m_pexceptionptra.is_set() && result.m_pexceptionptra->has_elements())
         {

            for (auto & pexception : result.m_pexceptionptra->ptra())
            {

               add(pexception);

            }

         }
         else if (result.m_estatus != undefined)
         {

            add(result.m_estatus);

         }

      }

      void set_error(const ::estatus & estatus)
      {

         set(estatus);

         if (succeeded())
         {

            m_estatus = error_status;

         }

      }


   };


} // namespace status


using exception_pointer = ::exception::exception_pointer;

template < typename EXCEPTION >
inline __pointer(EXCEPTION) __move_throw_exception(EXCEPTION * pexceptionNew);

CLASS_DECL_AURA __pointer(::exception::exception) __trace_context_move_throw_exception(::object * pobject, ::exception::exception * pexceptionNew);



#define __throw(...) throw(::exception_pointer(__new(__VA_ARGS__)))
#define __rethrow(pe) throw pe;
#define __throw_exit(estatus) __throw(exit_exception(estatus))


template < typename T >
class result_pointer :
   public __pointer(T),
   public ::status::result
{
public:


   result_pointer() :
      result(::error_failed)
   {

   }


   result_pointer(T * point) :
      pointer<T>(point)
   {

      if (this->is_null())
      {

         add(::error_null_result);

      }

   }

   template < typename TYPE >
   result_pointer(const __pointer(TYPE) & p) :
      pointer<T>(p)
   {

      if (this->is_null())
      {

         add(::error_null_result);

      }

   }

   template < typename TYPE >
   result_pointer(result_pointer && point) :
      pointer<T>(::move(point)),
      ::status::result(::move(point))
   {


   }

   result_pointer(std::nullptr_t) :
      result(::error_failed)
   {

   }

   result_pointer(::enum_status estatus) :
      result(estatus)
   {


   }


   result_pointer(const ::estatus & estatus) :
      result(estatus)
   {

      if (succeeded())
      {

         add(::error_null_result);

      }

   }


   result_pointer(::exception::exception * pe) :
      ::status::result(pe)
   {

      if (succeeded())
      {

         add(::error_exception);

      }

   }


   result_pointer(const std::initializer_list < ::exception::exception_pointer > & list) :
      result(list)
   {

      if (succeeded())
      {

         add(::error_exception);

      }

   }


   result_pointer(const ::status::result & result) :
      ::status::result(result)
   {

      if (succeeded())
      {

         add(::error_null_result);

      }

   }


   result_pointer(const result_pointer & result_pointer) :
      __pointer(T)(result_pointer),
      result(result_pointer)
   {

   }


   result_pointer(result_pointer && result_pointer) :
      __pointer(T)(::move(result_pointer)),
      result(::move(result_pointer))
   {

   }


   result_pointer & operator =(std::nullptr_t)
   {

      this->release();

      result::operator=(::error_failed);

      return *this;

   }


   result_pointer & operator =(const ::estatus & estatus)
   {

      this->release();

      add(estatus);

      if (succeeded())
      {

         add(::error_null_result);

      }

      return *this;

   }


   result_pointer & operator =(const ::status::result & result)
   {

      this->release();

      result::operator=(result);

      if (succeeded())
      {

         add(::error_null_result);

      }

      return *this;

   }


   result_pointer & operator =(status::result && result)
   {

      this->release();

      result::operator=(::move(result));

      if (succeeded())
      {

         add(::error_null_result);

      }

      return *this;

   }


   result_pointer & operator =(const result_pointer & result_pointer)
   {

      if (this != &result_pointer)
      {

         __pointer(T)::operator =(result_pointer);


         result::operator=(result_pointer);

      }

      return *this;

   }

   result_pointer & operator =(result_pointer && result_pointer)
   {

      __pointer(T)::operator =(::move(result_pointer));

      result::operator=(::move(result_pointer));

      return *this;

   }

   result_pointer & operator =(const T * p)
   {

      __pointer(T)::operator =(p);

      if (this->is_null())
      {

         add(::error_null_result);

      }

      return *this;

   }


   template < typename TYPE >
   result_pointer & operator =(const TYPE * p)
   {

      __pointer(T)::operator =(p);

      if (this->is_null())
      {

         if(::is_set(p))
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


   result_pointer & operator =(const __pointer(T) & p)
   {

      return this->operator = (p.m_p);

   }


   template < typename TYPE >
   result_pointer & operator =(const __pointer(TYPE) & p)
   {

      return this->operator = (p.m_p);

   }


   ::estatus status() const
   {

      if (m_pexceptionptra.is_null() || m_pexceptionptra->is_empty())
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
      else if (m_pexceptionptra->get_size() == 1)
      {

         return m_pexceptionptra->element_at(0)->m_estatus;

      }
      else
      {

         for (auto & e : m_pexceptionptra->ptra())
         {

            if (::failed(e->m_estatus))
            {

               return error_multiple;

            }

         }

         return success_multiple;

      }

   }

   bool succeeded() const { return ::succeeded(status()); }

   bool failed() const { return !succeeded(); }

   operator bool() const { return succeeded(); }

   bool operator !() const { return failed(); }

};


#define rp(T) ::result_pointer < T >


using unexpected_situation = ::exception::exception;




