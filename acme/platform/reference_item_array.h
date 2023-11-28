//
//  reference_count_debug.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 20/06/20.
//  More work on 2023-11-22 12:47 <3ThomasBorregaardSorensen
//
#pragma once


class reference_item;
class referencing_debugging;


class CLASS_DECL_ACME reference_item_array
{
public:


   ::reference_item_array *                                       m_preferenceitemarrayParent = nullptr;
   ::i64                                                          m_iSerial;
   int                                                            m_iStep;
   ::particle *                                                   m_pparticle;
   ::particle *                                                   m_pparticleParent;
   ::string                                                       m_strDebug;
   bool                                                           m_bFirstReference;
   ::iptr                                                         m_iLastReferenceCount;
   ::non_particle_comparable_array < reference_item * >           m_itema;
   ::non_particle_comparable_array < reference_item_array * >     m_item2a;


   reference_item_array(::particle * pparticle, ::particle * pparticleParent);
   ~reference_item_array();


//   virtual void initialize_reference_item_array(::referencing_debugging * preferencingdebugging);

   virtual void add_item_array(reference_item_array * pitema);
   virtual bool erase_item_array(reference_item_array * pitema);



   virtual void add_item(REFERENCING_DEBUGGING_PARAMETERS);
   
   
   virtual ::index find_item(REFERENCING_DEBUGGING_PARAMETERS);

   
   virtual bool erase_item(REFERENCING_DEBUGGING_PARAMETERS);


   virtual bool replace_item(REFERENCING_DEBUGGING_PARAMETERS);


   virtual void dump_pending_releases(::string & strDump);


};




