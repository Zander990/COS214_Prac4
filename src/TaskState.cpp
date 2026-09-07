#include "TaskState.h"
#include "ConstructionTask.h"

// GoF: State — State (abstract state)

TaskState::~TaskState() {}

// The transition itself. setState() is private on ConstructionTask; TaskState is a
// friend, so this helper is the single, controlled entry point for every concrete
// state. setState() deletes the outgoing state object (i.e. *this) and then adopts
// newState; concrete states must therefore call changeState() as their LAST action
// and must not touch *this afterwards.
void TaskState::changeState(ConstructionTask* task, TaskState* newState) const {
    task->setState(newState);
}
