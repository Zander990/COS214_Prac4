#ifndef OVERTIMEDECORATOR_H
#define OVERTIMEDECORATOR_H

#include "TaskDecorator.h"

// GoF: Decorator — ConcreteDecorator (stackable)
// Adds a fixed overtime-shift cost and appends a note to the status report,
// then defers to the wrapped component for everything else.
class OvertimeDecorator : public TaskDecorator {
private:
    double extraCost;
public:
    OvertimeDecorator(WorkComponent* component, double extraCost);
    std::string getStatusReport() const override;
    double getCost() const override;
};

#endif // OVERTIMEDECORATOR_H
