// Interface/IProgress.h
// from 7-zip
#pragma once
/*#define __IPROGRESS_H

#include "../Common/MyUnknown.h"
#include "../Common/Types.h"

#include "IDecl.h"*/

#define CA2_EX1_progress_interface(x) \
  virtual HRes SetTotal(huge_natural total) x; \
  virtual HRes SetCompleted(const huge_natural *completeValue) x; \

namespace apex
{

   class CLASS_DECL_APEX progress_interface :
      virtual public ::object
   {
   public:
      CA2_EX1_progress_interface(= 0)
   };

} // namespace apex

/*
// {23170F69-40C1-278A-0000-000000050002}
DEFINE_GUID(IID_IProgress2,
0x23170F69, 0x40C1, 0x278A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x02);
MIDL_INTERFACE("23170F69-40C1-278A-0000-000000050002")
IProgress2: public IUnknown
{
public:
  HRes SetTotal)(const huge_natural *total) PURE;
  HRes SetCompleted)(const huge_natural *completeValue) PURE;
};
*/
