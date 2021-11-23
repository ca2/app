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


      status();
      status(::enum_status estatus) ;
      status(const ::e_status& estatus);
      status(const std::initializer_list < ::e_status >& list);
      status(const status& status);
      status(status&& status);
      status(const ::exception& e);
      status(const std::initializer_list < ::exception >& list);
      ~status();


      static void set_skip_callstack(i32 iStack);
      static i32 get_skip_callstack();

      void set(const ::e_status& estatus);

      void set(::enum_status estatus);

      void add(const ::e_status& estatus);

      void add(::enum_status estatus);

      void add(const ::exception& e);


      void add(const std::initializer_list < ::exception >& list);
      

      void add(const std::initializer_list < ::e_status     >& list);

      //bool get_exception(::exception& e, const ::e_status& estatus);

      bool get_exit_status(::e_status& estatus) const;
      ::e_status get_greatest_exception_on_range(enum_status estatusOpenStart, enum_status estatusOpenEnd) const;

      bool has(const ::e_status& estatus) const;
      

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


      void add(const status& status);

      void set_error(const ::e_status& estatus);


   };



} // namespace extended


//using exception_pointer = ::exception::exception_pointer;

template < typename EXCEPTION >
inline __pointer(EXCEPTION) __move_throw_exception(EXCEPTION * pexceptionNew);

CLASS_DECL_ACME __pointer(::exception) __trace_context_move_throw_exception(::matter * pobject, ::exception * pexceptionNew);







//#define rp(T) ::transport < T >


using unexpected_situation = ::exception;




