#ifndef NOTSTARTEDSTATE_H
#define NOTSTARTEDSTATE_H

#include "TaskState.h"
#include <string>

// GoF: State — ConcreteState
// Lifecycle: NotStarted --advance--> InProgress
class NotStartedState : public TaskState {
public:
    void advance(ConstructionTask* task, bool inspectionPassed) override; // -> InProgressState
    std::string getName() const override;                                 // "Not Started"
};

#endif // NOTSTARTEDSTATE_H
