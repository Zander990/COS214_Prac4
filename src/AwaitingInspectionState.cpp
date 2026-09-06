#include "AwaitingInspectionState.h"
#include "CompletedState.h"
#include "BlockedState.h"
#include "ConstructionTask.h"

#include <iostream>

// GoF: State — ConcreteState
// NOTE: changeState() deletes the state object we are executing in, so each
// branch calls it as its final statement and touches no members afterwards.

void AwaitingInspectionState::advance(ConstructionTask* task, bool inspectionPassed) {
    if (inspectionPassed) {
        std::cout << "  [state] '" << task->getName()
                  << "' Awaiting Inspection -> Completed (inspection passed)\n";
        changeState(task, new CompletedState());
    } else {
        std::cout << "  [state] '" << task->getName()
                  << "' Awaiting Inspection -> Blocked (inspection failed)\n";
        changeState(task, new BlockedState("Failed safety inspection"));
    }
}

std::string AwaitingInspectionState::getName() const { return "Awaiting Inspection"; }
