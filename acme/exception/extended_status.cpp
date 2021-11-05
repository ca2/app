//
// Created by camilo on 2020-11-06.
//
#include "framework.h"


namespace extended
{


    i32 g_iSkipCallStack = SKIP_callstack;




    status::status() :
       m_estatus(undefined) 
    { 
    
    }

    
    status::status(::enum_status estatus) : 
       m_estatus(estatus) 
    { 
    
    }

    
    status::status(const ::e_status& estatus) : 
       m_estatus(estatus) 
    { 
    
    }

    
    status::status(const std::initializer_list < ::e_status >& list) :
       m_estatus(undefined)
    {
    
       add(list);

    }


    status::status(const status& status) :
       m_estatus(status.m_estatus),
       m_pexceptiona(status.m_pexceptiona)
    {

    }


    status::status(status&& status) :
       m_estatus(status.m_estatus),
       m_pexceptiona(move(status.m_pexceptiona))
    {

    }


    status::status(const ::exception& e) :
       m_estatus(undefined) 
    { 
       
       add(e); 
    
    }


    status::status(const std::initializer_list < ::exception >& list) :
       m_estatus(undefined)
    { 
       
       add(list); 

    }


    status::~status() 
    {
    
    }


    void status::set(const ::e_status& estatus)
    { 
       
       set(estatus.m_estatus); 
    
    }


    void status::set(::enum_status estatus)
    {

       m_pexceptiona.release();

       m_estatus = estatus;

    }


    void status::add(const ::e_status & estatus)
    {

       add(estatus.m_estatus);

    }


    void status::add(::enum_status estatus)
    {

        if (m_estatus == undefined)
        {

            m_estatus = estatus;

        }
        else
        {

            add(::exception(estatus,nullptr, g_iSkipCallStack));

        }

    }


    void status::set_skip_callstack(i32 iSkip)
    {

        g_iSkipCallStack = iSkip;

    }


    i32 status::get_skip_callstack()
    {

        return g_iSkipCallStack;

    }




    void status::add(const ::exception& e)
    {

       if (m_pexceptiona.is_null())
       {

          m_pexceptiona = __new(::array < ::exception >);

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



       //void status::add(::enum_status estatus)
       //{

       //   add(::exception(estatus));

       //}


    bool status::get_exception(::exception& e, const ::e_status& estatus)
    {

       if (m_estatus == estatus)
       {

          e = ::exception(m_estatus);

          return true;

       }

       if (!m_pexceptiona)
       {

          return false;

       }

       for (auto& exception : *m_pexceptiona)
       {

          if (exception.m_estatus == estatus)
          {

             e = exception;

             return true;

          }

       }

       return false;

    }


    ::e_status status::get_greatest_exception_on_range(enum_status estatusOpenStart, enum_status estatusOpenEnd) const
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


    bool status::has(const ::e_status& estatus) const
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


    //void status::add(const std::initializer_list < ::exception >& list)
    //{

    //   for (auto& e : list)
    //   {

    //      add(e);

    //   }

    //}


    void status::add(const std::initializer_list < ::e_status     >& list)
    {

       for (auto& e : list)
       {

          add(e);

       }

    }


    void status::add(const std::initializer_list < ::exception >& list)
    {

       for (auto& e : list)
       {

          add(e);

       }

    }

    
    bool status::get_exit_status(::e_status& estatus) const
    {

       auto estatusExit = get_greatest_exception_on_range(error_exit_start, error_exit_end);

       if(estatusExit == error_not_found)
       {

          return false;

       }

       estatus = estatusExit;

       return true;

    }


    void status::add(const status& status)
    {

       if (status.m_pexceptiona.is_set() && status.m_pexceptiona->has_elements())
       {

          for (auto& pexception : *status.m_pexceptiona)
          {

             add(pexception);

          }

       }
       else if (status.m_estatus != undefined)
       {

          add(status.m_estatus);

       }

    }

    void status::set_error(const ::e_status& estatus)
    {

       set(estatus);

       if (succeeded())
       {

          m_estatus = error_status;

       }

    }

} // namespace status


