#ifndef TASKSTATE_H
#define TASKSTATE_H

#include <string>

// GoF: State — State (abstract state)
// Each ConstructionTask delegates advance() to its current TaskState object.
// Transitions are performed by the state itself via the protected changeState()
// helper, which is the ONLY way to reach ConstructionTask::setState() (friendship).
class ConstructionTask; // forward declare

class TaskState {
public:
    virtual ~TaskState();                                  // polymorphic base => virtual destructor

    // inspectionPassed is only meaningful for AwaitingInspectionState; it is part
    // of the uniform interface so every state overrides the same signature.
    virtual void advance(ConstructionTask* task, bool inspectionPassed) = 0;
    virtual std::string getName() const = 0;

protected:
    // Drives the transition: forwards to ConstructionTask::setState(), which
    // deletes the outgoing state and adopts newState.
    void changeState(ConstructionTask* task, TaskState* newState) const;
};

#endif // TASKSTATE_H
