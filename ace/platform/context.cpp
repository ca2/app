// create by camilo on 2024-05-24 16:30 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "context.h"

namespace ace
{


    context::context()
    {

    }

    context::~context()
    {

    }




     void context::information_log(const char * psz)
    {



    }

     void context::informationf_log(const char * psz,...)
    {


    }


     void context::error_log(const char * psz)
    {


    }


    void context::errorf_log(const char * psz,...)
    {


    }


    ::ace::shell * context::shell()
    {

        if(!m_pshell)
        {

            m_pshell = {transfer_t, new ::ace::shell()};

        }

        return nullptr;

    }

} // namespace ace