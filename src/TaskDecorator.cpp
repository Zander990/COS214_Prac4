#include "TaskDecorator.h"

// GoF: Decorator — Decorator (abstract)

// id/name are seeded from the wrapped component so a decorated task still reports
// a sensible identity.
TaskDecorator::TaskDecorator(WorkComponent* component)
    : WorkComponent(component ? component->getId() : std::string(),
                    component ? component->getName() : std::string()),
      wrapped(component) {}

TaskDecorator::~TaskDecorator() {
    delete wrapped; // the decorator owns exactly what it wraps
}

std::string TaskDecorator::getName() const {
    return wrapped->getName();
}

std::string TaskDecorator::getStatusReport() const {
    return wrapped->getStatusReport();
}

double TaskDecorator::getCost() const {
    return wrapped->getCost();
}
