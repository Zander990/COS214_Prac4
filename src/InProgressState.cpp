#include "InProgressState.h"
#include "AwaitingInspectionState.h"
#include "ConstructionTask.h"

#include <iostream>

// GoF: State — ConcreteState
// NOTE: changeState() deletes the state object we are executing in, so it is the
// final statement of advance() and no members are touched afterwards.

void InProgressState::advance(ConstructionTask* task, bool /*inspectionPassed*/) {
    std::cout << "  [state] '" << task->getName()
              << "' In Progress -> Awaiting Inspection\n";
    changeState(task, new AwaitingInspectionState());
}

std::string InProgressState::getName() const { return "In Progress"; }
