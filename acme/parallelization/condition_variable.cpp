#include "framework.h"
#include "acme/operating_system.h"


//condition_variable

condition_variable::construct * condition_variable::s_pconstruct = (condition_variable::construct *)&::InitializeConditionVariable;
//static destruct * s_pdestruct;
