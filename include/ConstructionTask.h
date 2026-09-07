#ifndef CONSTRUCTIONTASK_H
#define CONSTRUCTIONTASK_H

#include "WorkComponent.h"

// GoF: Composite — Leaf   (has no children; inherits the no-op add/remove)
// GoF: State   — Context (holds a TaskState* and delegates advance() to it)
class TaskState;

class ConstructionTask : public WorkComponent {
private:
    TaskState* state;   // owned: current state object, replaced on every transition
    double baseCost;

    friend class TaskState; // only TaskState (and its subclasses via changeState) may transition us
    void setState(TaskState* newState); // deletes the old state, adopts newState

public:
    ConstructionTask(const std::string& id, const std::string& name, double baseCost);
    ~ConstructionTask() override;        // deletes the current state object

    std::string getStatusReport() const override;
    double getCost() const override;    // returns baseCost (Leaf cost)

    // Lifecycle driver. inspectionPassed only matters while Awaiting Inspection;
    // it defaults to true so ordinary "advance()" calls still read naturally.
    void advance(bool inspectionPassed = true);
    std::string getStateName() const;   // delegates to state->getName()
};

#endif // CONSTRUCTIONTASK_H
