#pragma once

#include "radix/flags.h"

namespace check
{

   typedef flags < enum_check > check;

} // namespace check


#ifdef _WIN64
template <>
inline u32 u32_hash(iptr key)
{
	// default identity hash - works for most primitive values
	return (DWORD)(((DWORD_PTR)key)>>32);
}
#else
template <>
inline u32 u32_hash(iptr key)
{
	// default identity hash - works for most primitive values
	return (DWORD)(((DWORD_PTR)key)>>16);
}
#endif

namespace user
{

   typedef ::collection::map < INT_PTR, INT_PTR, ::user::primitive *, ::user::primitive * > int_to_window_interface;
   typedef address_array < interaction > interaction_array;

} // namespace user

typedef ref_array < ::channel > command_target_ptra;

namespace user
{

   namespace win
   {

      namespace message
      {

         class CLASS_DECL_AURA DispatchHandlerItemArray :
            public ref_array < DispatchHandlerItemBase >
         {
         public:
            bool HasSignalizable(::object* psignalizable);
         };

         class DispatchSignalPtrArray :
            public ref_array < DispatchSignal >
         {
         };

         class DispatchSignalArray :
            public array_ptr_alloc < DispatchSignal , DispatchSignal & >
         {
         public:
            virtual ~SignalArray();
            void GetSignalsByMessage(SignalPtrArray & signalptra, UINT uiMessage, UINT uiCode, UINT uiId);
            Signal * GetSignalByMessage(UINT uiMessage, UINT uiCode, UINT uiIdStart, UINT uiIdEnd);
         };

      } // namespace message

   } // namespace win

} // namespace user


