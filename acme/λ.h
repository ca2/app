// Created by camilo on 2025-04-21 04:00 <3ThomasBorregaardSørensen!!
#pragma once

//#include <type_traits>
#include <functional>

template < typename PREDICATE >
std::invoke_result_t<PREDICATE> λsafe_return(PREDICATE predicate)
{

    std::invoke_result_t<PREDICATE> result;

    try
    {

        result = predicate();

    }
    catch (::exception & exception)
    {

        ::debug() << exception << "safe_pointer got exception!! going to return nullptr";

    }
    catch (...)
    {

        ::exception exception(error_catch_all_exception, "could not get pointer");

        ::debug() << exception << "safe_pointer got exception!! going to return nullptr";

    }

    return result;

}
