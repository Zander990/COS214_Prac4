#include "NotStartedState.h"
#include "InProgressState.h"
#include "ConstructionTask.h"

#include <iostream>

// GoF: State — ConcreteState
// NOTE: changeState() ends up calling ConstructionTask::setState(), which
// "delete"s the state object we are currently executing in. advance() therefore
// calls changeState() as its final statement and never touches members afterwards.

void NotStartedState::advance(ConstructionTask* task, bool /*inspectionPassed*/) {
    std::cout << "  [state] '" << task->getName()
              << "' Not Started -> In Progress\n";
    changeState(task, new InProgressState());
}

std::string NotStartedState::getName() const { return "Not Started"; }
