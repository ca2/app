// create by camilo on 2024-05-24 16:30 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "context.h"

namespace acid
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


    ::acid::shell * context::shell()
    {

        if(!m_pshell)
        {

            m_pshell = {transfer_t, new ::acid::shell()};

        }

        return nullptr;

    }

} // namespace acid