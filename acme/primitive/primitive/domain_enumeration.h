//
// Created by camilo on 6/12/24.
//
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

            throw ::exception(error_wrong_state);

        }

        m_eenum = (ENUM) domainid.m_iId;

        return *this;

    }

    domain_enumeration & operator =(const ::atom & atom)
    {

        if(atom.get_type() != ::atom::e_type_domainid)
        {

            throw ::exception(error_wrong_state);

        }

        return this->operator=(atom.as_domainid());

    }

};
