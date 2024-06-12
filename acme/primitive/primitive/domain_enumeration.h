//
// Created by camilo on 2024-06-12 17:06 <3ThomasBorregaardSorensen!!
//
#pragma once


template < typename ENUM, enum_domain t_edomain >
class domain_enumeration
{
public:

    ENUM m_eenum;

    domain_enumeration() :m_eenum(ENUM(0)){}
    domain_enumeration(ENUM eenum) :m_eenum(eenum){}

    ::domain_id as_domainid()
    {

        return {t_edomain, m_eenum};

    }


    domain_enumeration & operator =(const domain_id & domainid)
    {

        if(domainid.m_edomain != t_edomain)
        {

            m_eenum = (ENUM) 0;

        }
        else
        {

            m_eenum = (ENUM) domainid.m_iId;

        }

        return *this;

    }


    domain_enumeration & operator =(const ::atom & atom)
    {

        if(atom.get_type() != ::atom::e_type_domainid)
        {

            m_eenum = (ENUM)0;

        }
        else
        {

            this->operator=(atom.as_domainid());

        }

        return *this;

    }

};


#define DECLARE_DOMAIN_ENUMERATION(EENUM, ENUM, EDOMAIN) \
using EENUM = domain_enumeration<ENUM, EDOMAIN>; \
::domain_id as_domainid(const EENUM & eenum) {return {EDOMAIN, (::i32) eenum.m_eenum};}



