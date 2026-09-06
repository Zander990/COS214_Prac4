#ifndef COMPLETEDSTATE_H
#define COMPLETEDSTATE_H

#include "TaskState.h"
#include <string>

// GoF: State — ConcreteState
// Terminal state: advance() is an invalid transition (rejected, logged, no change).
class CompletedState : public TaskState {
public:
    void advance(ConstructionTask* task, bool inspectionPassed) override; // invalid: log + do nothing
    std::string getName() const override;                                 // "Completed"
};

#endif // COMPLETEDSTATE_H
