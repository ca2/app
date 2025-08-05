#pragma once


#include "place_holder.h"


namespace user
{


   class CLASS_DECL_BERG place_holder_container :
      virtual public interaction
   {
   public:


      pointer_array < place_holder >          m_placeholdera;


      place_holder_container();
      ~place_holder_container() override;



      void destroy() override;


      void install_message_routing(::channel * pchannel) override;


      //virtual bool create_interaction(::user::interaction * puiParent,atom atom);


      virtual ::user::place_holder * get_new_place_holder(const ::int_rectangle & rectangleCreate);

      virtual bool erase_place_holder(::user::place_holder * pholder);


      virtual ::user::place_holder * place_hold(::user::interaction * pinteraction,const ::int_rectangle & rectangleCreate);

      virtual bool unplace(::user::interaction * pinteraction);

      virtual bool on_place_hold(::user::interaction * pinteraction, ::user::place_holder * pholder);
      virtual bool on_unplace(::user::interaction * pinteraction, ::user::place_holder * pholder);

   };


   class CLASS_DECL_BERG place_holder_container_ptra :
      virtual public pointer_array < place_holder_container >
   {
   public:

      virtual place_holder_ptra place(::user::interaction * pinteraction, const ::int_rectangle & rectangleCreate);

      virtual int unplace(::user::interaction * pinteraction);

   };


} // namespace user



