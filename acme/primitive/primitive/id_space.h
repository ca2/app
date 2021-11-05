#pragma once




inline index BaseSortCompare(const id & id1, const id & id2)
{


   return (index) (id1.m_psz - id2.m_psz);


}


//class ::mutex;


class CLASS_DECL_ACME id_space
{
protected:


   raw_array < char *  >      m_psza;
   critical_section *         m_pcs;


   bool find(const char * pszFind,index & iIndex);

   void free_all();



public:


   id_space();
   virtual ~id_space();


   const char * get_id(const char * pszFind);


   id operator()(const char * psz);
   id operator()(i64 i);

   static id_space *                            s_pidspace;

};




class CLASS_DECL_ACME strid_array :
   virtual public matter
{
protected:


   index_array                      stackLowerBound;
   index_array                      stackUpperBound;
   raw_array < char * >             m_idptra; // ordered as added
   index_array                      m_iaId; // ordered by id_cmp



   void sort();
   bool find(const char * psz, index & iIndex) const;


public:


   strid_array(bool bSynch);
   virtual ~strid_array();

   void add(const id & id);


   bool find(const id & id, index & iIndex) const;

   bool contains(const id & id) const { index iIndex; return find(id, iIndex); }


};




CLASS_DECL_ACME ::id_space & get_id_space();
