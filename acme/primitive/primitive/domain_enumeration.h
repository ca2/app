//
// Created by camilo on 2024-06-12 17:06 <3ThomasBorregaardSorensen!!
//
#pragma once


template < typename ENUM, enum_domain t_edomain >
class domain_enumeration
{
public:


    ENUM m_eenum;


    constexpr domain_enumeration() :m_eenum(ENUM(0)){}


    constexpr domain_enumeration(ENUM eenum) :m_eenum(eenum){}


    constexpr domain_enumeration(const ::domain_id & domainid)
    {

        if(domainid.m_edomain != t_edomain)
        {

            m_eenum = (ENUM) 0;

        }
        else
        {

            m_eenum = (ENUM) domainid.m_iId;

        }

    }


    domain_enumeration(const ::atom & atom)
    {

        if(atom.get_type() != ::atom::e_type_domainid)
        {

            m_eenum = (ENUM)0;

        }
        else
        {

            this->operator=(atom.as_domainid());

        }

    }


    constexpr ::domain_id as_domainid()
    {

        return {t_edomain, m_eenum};

    }


    constexpr domain_enumeration & operator =(const domain_enumeration & domainenumeration)
    {

        m_eenum = domainenumeration.m_eenum;

        return *this;

    }


    constexpr bool operator == (const domain_enumeration & domainenumeration) const
    {

        return m_eenum == domainenumeration.m_eenum;

    }


    constexpr bool is_ok() const { return m_eenum != (ENUM) 0; }


    constexpr bool is_nok() const { return !this->is_ok(); }


    explicit constexpr operator ::u32hash() const { return (::u32) m_eenum; }


};


#define DECLARE_DOMAIN_ENUMERATION(EENUM, ENUM, EDOMAIN) \
using EENUM = domain_enumeration<ENUM, EDOMAIN>; \
inline constexpr ::domain_id as_domainid(const EENUM & eenum) {return {EDOMAIN, (::i32) eenum.m_eenum};}



