#pragma once


struct CLASS_DECL_ACME matter :
   virtual public matter
{

   
   __pointer(property_set)    m_ppropertyset;


   matter() { }
   virtual ~matter();


   virtual stream & do_property_exchange(stream & stream) const;
   virtual stream & do_property_exchange(stream & stream);
   virtual void exchange(::stream & stream);


   virtual stream & write(::stream & stream) const override;
   virtual stream & read(::stream & stream) override;

   using matter::cast;

   inline bool has_property(const atom & atom) const;
   inline property * lookup_property(const atom & atom) const;
   inline bool erase_key(const atom & atom);

   inline property_set & get_propset();
   inline const property_set & get_propset() const;
   inline property_set & propset();
   inline const property_set & propset() const;
   inline bool contains(const property_set & set) const;

   inline property & set(const ::atom & atom);

   
   inline ::papaya::topic topic(const ::atom & atom);


   inline property * find_property(const ::atom & atom) const;


   inline ::payload attribute(const ::atom & atom);
   ::property * find_attribute(const ::atom & atom);

   template < typename TYPE >
   inline bool find_attribute(const ::atom & atom, TYPE & t);
 
   inline ::payload find_value(const ::atom & atom) const;
   inline ::payload find_value(const ::atom & atom, const ::payload & varDefault) const;
   
   
   inline ::payload & matter(const ::atom & atom);


   inline ::payload operator()(const ::atom & atom) const;
   inline ::payload operator()(const ::atom & atom, const ::payload & varDefault) const;


   inline property & operator[](const ::atom & atom);


   inline ::payload operator[](const ::atom & atom) const;


   inline ::payload value(const ::atom & atom) const;
   inline ::payload value(const ::atom & atom, const ::payload & varDefault) const;


   inline string find_string(const ::atom & atom, const ansichar * pszDefault = nullptr) const;


   inline ::i32 find_i32(const ::atom & atom, ::i32 iDefault = 0) const;


   inline ::u32 find_u32(const ::atom & atom, ::u32 iDefault = 0) const;


   template < typename TYPE > inline TYPE & get_cast(const ::atom & atom, TYPE * pDefault = nullptr);
   template < typename TYPE > inline __pointer(TYPE) cast(const ::atom & atom) const;


   inline void defer_propset();


   inline bool is_true(const ::atom & atom) const;
   inline bool is_true(const ::atom & atom, const ::payload & varDefault, bool bDefault) const;


}; // struct matter



