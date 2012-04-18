#include "ACARSInputRegistry.h"
#include <Core/ACARSInput.h>

ACARSInputRegistry::ACARSInputRegistry(ACARSMainWindow *pParent)
{
}

void ACARSInputRegistry::RegisterInput(ACARSInput *pInput)
{
    m_vInputs.append(pInput);
}

ACARSInputEvent* ACARSInputRegistry::ClickEvent(QMouseEvent *pEvent)
{

    if (m_vInputs.constBegin() != m_vInputs.constEnd())
    {
        return ((ACARSInput*)(m_vInputs.begin()))->EvaluateClick(pEvent);
    }

    return NULL;

}
