#include "CompletedState.h"
#include "ConstructionTask.h"

#include <iostream>

// GoF: State — ConcreteState (terminal)

void CompletedState::advance(ConstructionTask* task, bool /*inspectionPassed*/) {
    // Invalid transition: a completed task has nowhere to advance to.
    std::cout << "  [state] REJECTED: '" << task->getName()
              << "' is already Completed; advance() ignored.\n";
}

std::string CompletedState::getName() const { return "Completed"; }
