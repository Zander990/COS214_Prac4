#include "WorkComponent.h"
#include "TaskIterator.h"

// GoF: Composite — Component (default behaviour lives here)

WorkComponent::WorkComponent(const std::string& id, const std::string& name)
    : id(id), name(name) {}

WorkComponent::~WorkComponent() {}

std::string WorkComponent::getName() const { return name; }

std::string WorkComponent::getId() const { return id; }

double WorkComponent::getCost() const { return 0.0; }

// Default composite operations: a Leaf has no children, so these do nothing.
void WorkComponent::add(WorkComponent* /*component*/) {}
void WorkComponent::remove(WorkComponent* /*component*/) {}

// A Leaf cannot be traversed as an aggregate.
TaskIterator* WorkComponent::createFullIterator() { return nullptr; }
TaskIterator* WorkComponent::createCriticalPathIterator() { return nullptr; }
