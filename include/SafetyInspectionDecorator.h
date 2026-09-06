#ifndef SAFETYINSPECTIONDECORATOR_H
#define SAFETYINSPECTIONDECORATOR_H

#include "TaskDecorator.h"

// GoF: Decorator — ConcreteDecorator (stackable)
// Adds a fixed safety-inspection cost and appends a note to the status report,
// then defers to the wrapped component for everything else.
class SafetyInspectionDecorator : public TaskDecorator {
private:
    double extraCost;
public:
    SafetyInspectionDecorator(WorkComponent* component, double extraCost);
    std::string getStatusReport() const override;
    double getCost() const override;
};

#endif // SAFETYINSPECTIONDECORATOR_H
