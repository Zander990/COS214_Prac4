#include "ConstructionTask.h"
#include "TaskState.h"
#include "NotStartedState.h"

#include <sstream>

// GoF: Composite — Leaf ;  GoF: State — Context

namespace {
    // File-local formatting helper (not a class, not part of the public interface).
    std::string money(double v) {
        std::ostringstream os;
        os.setf(std::ios::fixed);
        os.precision(2);
        os << "R" << v;
        return os.str();
    }
}

ConstructionTask::ConstructionTask(const std::string& id, const std::string& name, double baseCost)
    : WorkComponent(id, name), state(new NotStartedState()), baseCost(baseCost) {}

ConstructionTask::~ConstructionTask() {
    delete state; // the task owns exactly one state object at all times
}

void ConstructionTask::setState(TaskState* newState) {
    delete state;       // release the outgoing state
    state = newState;   // adopt the incoming one
}

std::string ConstructionTask::getStatusReport() const {
    std::ostringstream os;
    os << "[" << id << "] " << name
       << "  |  state: " << state->getName()
       << "  |  cost: " << money(baseCost);
    return os.str();
}

double ConstructionTask::getCost() const { return baseCost; }

void ConstructionTask::advance(bool inspectionPassed) {
    state->advance(this, inspectionPassed); // State pattern: behaviour depends on current state
}

std::string ConstructionTask::getStateName() const {
    return state->getName();
}
