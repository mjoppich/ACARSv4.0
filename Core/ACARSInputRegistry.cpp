#include "ACARSInputRegistry.h"
#include <Core/ACARSInput.h>

ACARSInputRegistry::ACARSInputRegistry(ACARSSystem *pParent)
{
    m_vInputs.clear();
}

void ACARSInputRegistry::RegisterInput(ACARSInput *pInput)
{
    m_vInputs.append(pInput);
}

bool ACARSInputRegistry::ClickEvent(QMouseEvent *pEvent, QVector<ACARSActionEvent *> *ResultVector)
{

    ACARSActionEvent* pReturnValue;
    int i;

    for (i = 0; i < m_vInputs.size(); ++i) {

        pReturnValue = m_vInputs.at(i)->EvaluateClick(pEvent);

        if (pReturnValue)
            ResultVector->append(pReturnValue);

    }

    return i;

}
