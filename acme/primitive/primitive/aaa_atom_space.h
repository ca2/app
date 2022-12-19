#pragma once

//
//
//
//inline index BaseSortCompare(const atom & id1, const atom & id2)
//{
//
//
//   return (index) (id1.m_psz - id2.m_psz);
//
//
//}


//class ::pointer < ::mutex >;

//
//class CLASS_DECL_ACME atom_space
//{
//protected:
//
//
//   raw_array < char *  >      m_psza;
//   critical_section           m_criticalsection;
//
//
//   bool find(const scoped_string & strFind,index & iIndex);
//
//   void free_all();
//
//
//
//public:
//
//
//   atom_space();
//   virtual ~atom_space();
//
//
//   const char * get_id(const scoped_string & strFind);
//
//
//   atom operator()(const scoped_string & str);
//   atom operator()(i64 i);
//
//   static atom_space *                            s_pidspace;
//
//};
//


//
//class CLASS_DECL_ACME strid_array :
//   virtual public matter
//{
//protected:
//
//
//   index_array                      stackLowerBound;
//   index_array                      stackUpperBound;
//   raw_array < char * >             m_idptra; // ordered as added
//   index_array                      m_iaId; // ordered by id_cmp
//
//
//
//   void sort();
//   bool find(const scoped_string & str, index & iIndex) const;
//
//
//public:
//
//
//   strid_array(bool bSynch);
//   virtual ~strid_array();
//
//   void add(const atom & atom);
//
//
//   bool find(const atom & atom, index & iIndex) const;
//
//   bool contains(const atom & atom) const { index iIndex; return find(atom, iIndex); }
//
//
//};
//
//
//
//
//CLASS_DECL_ACME ::atom_space & get_id_space();
