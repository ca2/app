#pragma once


class CLASS_DECL_ACME obj_ref_dbg
{
public:


   class item
   {
   public:

      ::index                 m_iStep;
      matter* m_p;
      string                  m_strNote;

   };


   ::index                    m_iStep;
   array < item >             m_itema;


   obj_ref_dbg();
   virtual ~obj_ref_dbg();

};




