#ifndef PERMITREQUIREDDECORATOR_H
#define PERMITREQUIREDDECORATOR_H

#include "TaskDecorator.h"

// GoF: Decorator — ConcreteDecorator (stackable)
// Adds a fixed permit cost and appends a note to the status report,
// then defers to the wrapped component for everything else.
class PermitRequiredDecorator : public TaskDecorator {
private:
    double extraCost;
public:
    PermitRequiredDecorator(WorkComponent* component, double extraCost);
    std::string getStatusReport() const override;
    double getCost() const override;
};

#endif // PERMITREQUIREDDECORATOR_H
