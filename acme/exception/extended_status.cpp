//
// Created by camilo on 2020-11-06.
//
#include "framework.h"




namespace extended
{


    i32 g_iSkipCallStack = SKIP_callstack;


    void status::add(::enum_status estatus)
    {

        if (m_estatus == undefined)
        {

            m_estatus = estatus;

        }
        else
        {

            add(__new(::exception::exception(nullptr, estatus, g_iSkipCallStack)));

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


} // namespace status


