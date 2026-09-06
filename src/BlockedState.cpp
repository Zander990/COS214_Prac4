#include "BlockedState.h"
#include "InProgressState.h"
#include "ConstructionTask.h"

#include <iostream>

// GoF: State — ConcreteState
// NOTE: changeState() deletes the state object we are executing in, so it is the
// final statement of advance() and no members are touched afterwards.

BlockedState::BlockedState(const std::string& reason) : blockReason(reason) {}

std::string BlockedState::getReason() const { return blockReason; }

void BlockedState::advance(ConstructionTask* task, bool /*inspectionPassed*/) {
    std::cout << "  [state] '" << task->getName()
              << "' Blocked (" << blockReason << ") -> In Progress (unblocked)\n";
    changeState(task, new InProgressState());
}

std::string BlockedState::getName() const { return "Blocked"; }
