#pragma once


namespace user
{

   class CLASS_DECL_AURA place_holder_container :
      virtual public interaction
   {
   public:


      __pointer_array(place_holder)          m_placeholdera;


      place_holder_container();
      virtual ~place_holder_container();


      void install_message_routing(::channel * pchannel);


      virtual bool create_window(::user::interaction * puiParent,id id);


      virtual ::user::place_holder * get_new_place_holder(const ::rect & rectCreate);

      virtual bool remove_place_holder(::user::place_holder * pholder);


      virtual ::user::place_holder * place_hold(::user::interaction * pinteraction,const ::rect & rectCreate);

      virtual bool unplace(::user::interaction * pinteraction);

      virtual bool on_place_hold(::user::interaction * pinteraction, ::user::place_holder * pholder);
      virtual bool on_unplace(::user::interaction * pinteraction, ::user::place_holder * pholder);

   };


   class CLASS_DECL_AURA place_holder_container_ptra :
      virtual public __pointer_array(place_holder_container)
   {
   public:

      virtual place_holder_ptra place(::user::interaction * pinteraction, const ::rect & rectCreate);

      virtual i32 unplace(::user::interaction * pinteraction);

   };

} // namespace user
