#ifndef BLOCKEDSTATE_H
#define BLOCKEDSTATE_H

#include "TaskState.h"
#include <string>

// GoF: State — ConcreteState
// Lifecycle: Blocked --advance--> InProgress (unblocked)
class BlockedState : public TaskState {
private:
    std::string blockReason;
public:
    explicit BlockedState(const std::string& reason);
    std::string getReason() const;
    void advance(ConstructionTask* task, bool inspectionPassed) override; // -> InProgressState (unblocked)
    std::string getName() const override;                                 // "Blocked"
};

#endif // BLOCKEDSTATE_H
