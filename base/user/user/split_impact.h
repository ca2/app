#pragma once


#include "impact_host.h"
#include "split_layout.h"
#include "show.h"


namespace user
{


   class CLASS_DECL_BASE split_impact :
      virtual public ::user::impact_host,
      virtual public ::user::show < split_layout >
   {
   public:


      bool     m_bAutoCreate;


      split_impact();
      ~split_impact() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      void install_message_routing(::channel * pchannel) override;
      bool pre_create_window(::user::system * pusersystem) override;

      void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;
      virtual bool create_split_impact();
      virtual void on_create_split_impact();

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);

      template < class VIEW >
      inline ::pointer<VIEW>create_pane_impact(::collection::index iPane, atom atom = ::atom(), ::user::interaction * pviewLast = nullptr);
      ::pointer<::user::impact>create_pane_impact(const ::type_atom & typeatom, ::collection::index iPane, atom atom = ::atom(), ::user::interaction * pviewLast = nullptr);

      bool on_prepare_impact_data(::user::impact_data* pimpactdata) override;


   };


   template < class VIEW >
   inline ::pointer<VIEW>split_impact::create_pane_impact(::collection::index iPane, atom atom, ::user::interaction * pviewLast)
   {

      return create_impact < VIEW >(get_pane_holder(iPane), atom, pviewLast);

   }

} // namespace user



