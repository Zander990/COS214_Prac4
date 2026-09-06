#ifndef AWAITINGINSPECTIONSTATE_H
#define AWAITINGINSPECTIONSTATE_H

#include "TaskState.h"
#include <string>

// GoF: State — ConcreteState
// Lifecycle: AwaitingInspection --advance(true)--> Completed
//            AwaitingInspection --advance(false)--> Blocked
class AwaitingInspectionState : public TaskState {
public:
    // inspectionPassed == true  -> CompletedState
    // inspectionPassed == false -> BlockedState
    void advance(ConstructionTask* task, bool inspectionPassed) override;
    std::string getName() const override;                                 // "Awaiting Inspection"
};

#endif // AWAITINGINSPECTIONSTATE_H
