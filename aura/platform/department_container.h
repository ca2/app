#pragma once


class CLASS_DECL_AURA department_container_base :
   virtual public ::object
{
public:


   department_container_base();
   virtual ~department_container_base();


   ::aura::application * get_department_app();


};


template < class SECTION >
class department_container :
   virtual public department_container_base
{
public:


   __pointer(SECTION) m_pdepartment;


   department_container()
   {

   }


   virtual ~department_container()
   {
   }

};


