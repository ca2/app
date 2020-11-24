#pragma once


struct CLASS_DECL_ACME matter :
   virtual public matter
{

   
   __pointer(property_set)    m_pset;


   matter() { }
   virtual ~matter();


   virtual stream & do_property_exchange(stream & stream) const;
   virtual stream & do_property_exchange(stream & stream);
   virtual void exchange(::stream & stream);


   virtual stream & write(::stream & stream) const override;
   virtual stream & read(::stream & stream) override;

   using matter::cast;

   inline bool has_property(const id & id) const;
   inline property * lookup_property(const id & id) const;
   inline bool remove_key(const id & id);

   inline property_set & get_propset();
   inline const property_set & get_propset() const;
   inline property_set & propset();
   inline const property_set & propset() const;
   inline bool contains(const property_set & set) const;

   inline property & set(const ::id & id);

   
   inline ::papaya::topic topic(const ::id & id);


   inline property * find_property(const ::id & id) const;


   inline payload attribute(const ::id & id);
   ::property * find_attribute(const ::id & id);

   template < typename TYPE >
   inline bool find_attribute(const ::id & id, TYPE & t);
 
   inline payload find_value(const ::id & id) const;
   inline payload find_value(const ::id & id, const payload & varDefault) const;
   
   
   inline payload & matter(const ::id & id);


   inline payload operator()(const ::id & id) const;
   inline payload operator()(const ::id & id, const payload & varDefault) const;


   inline property & operator[](const ::id & id);


   inline payload operator[](const ::id & id) const;


   inline payload value(const ::id & id) const;
   inline payload value(const ::id & id, const payload & varDefault) const;


   inline string find_string(const ::id & id, const ansichar * pszDefault = nullptr) const;


   inline ::i32 find_i32(const ::id & id, ::i32 iDefault = 0) const;


   inline ::u32 find_u32(const ::id & id, ::u32 iDefault = 0) const;


   template < typename TYPE > inline TYPE & get_cast(const ::id & id, TYPE * pDefault = nullptr);
   template < typename TYPE > inline __pointer(TYPE) cast(const ::id & id) const;


   inline void defer_propset();


   inline bool is_true(const ::id & id) const;
   inline bool is_true(const ::id & id, const payload & varDefault, bool bDefault) const;


}; // struct matter



