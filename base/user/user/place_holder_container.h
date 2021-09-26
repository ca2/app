#pragma once


namespace user
{

   class CLASS_DECL_BASE place_holder_container :
      virtual public interaction
   {
   public:


      __pointer_array(place_holder)          m_placeholdera;


      place_holder_container();
      virtual ~place_holder_container();


      void install_message_routing(::channel * pchannel);


      //virtual bool create_interaction(::user::interaction * puiParent,id id);


      virtual ::user::place_holder * get_new_place_holder(const ::rectangle_i32 & rectangleCreate);

      virtual bool erase_place_holder(::user::place_holder * pholder);


      virtual ::user::place_holder * place_hold(::user::interaction * pinteraction,const ::rectangle_i32 & rectangleCreate);

      virtual bool unplace(::user::interaction * pinteraction);

      virtual bool on_place_hold(::user::interaction * pinteraction, ::user::place_holder * pholder);
      virtual bool on_unplace(::user::interaction * pinteraction, ::user::place_holder * pholder);

   };


   class CLASS_DECL_BASE place_holder_container_ptra :
      virtual public __pointer_array(place_holder_container)
   {
   public:

      virtual place_holder_ptra place(::user::interaction * pinteraction, const ::rectangle_i32 & rectangleCreate);

      virtual i32 unplace(::user::interaction * pinteraction);

   };

} // namespace user
