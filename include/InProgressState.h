#ifndef INPROGRESSSTATE_H
#define INPROGRESSSTATE_H

#include "TaskState.h"
#include <string>

// GoF: State — ConcreteState
// Lifecycle: InProgress --advance--> AwaitingInspection
class InProgressState : public TaskState {
public:
    void advance(ConstructionTask* task, bool inspectionPassed) override; // -> AwaitingInspectionState
    std::string getName() const override;                                 // "In Progress"
};

#endif // INPROGRESSSTATE_H
