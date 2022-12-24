// Created by camilo on 2022-11-08 17:25 <3ThomasBorregaardSorensen!!
#pragma once


void copy(::string & str, const ::payload & payload);
void copy(::payload & payload, const int & i);
void copy(::payload & payload, const ::string & str);


namespace acme
{


    namespace container
    {


        template < primitive_container CONTAINER1, primitive_container CONTAINER2 >
        CONTAINER1& append(CONTAINER1& container1, const CONTAINER2& container2)
        {

            for (auto& item : container2)
            {

                ::copy(container1.add_new(), item);

            }

            return container1;

        }


        template < primitive_container CONTAINER1, primitive_container CONTAINER2 >
        CONTAINER1& copy(CONTAINER1& container1, const CONTAINER2& container2)
        {

            container1.clear();

            return append(container1, container2);

        }


    } // namespace container


} // namespace acme



