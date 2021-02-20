#pragma once


class CLASS_DECL_ACME id_matter :
   virtual public matter
{
public:


   ::id                                m_id;


   id_matter() { }
   id_matter(const ::id & id) : m_id(id) {}
   id_matter(const id_matter & object);
   id_matter(id_matter && object) :
      matter(::move(object)),
      m_id(::move(object.m_id))
   {  }
   virtual ~id_matter();


};



