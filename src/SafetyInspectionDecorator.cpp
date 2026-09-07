#include "SafetyInspectionDecorator.h"

#include <sstream>

// GoF: Decorator — ConcreteDecorator

namespace {
    std::string money(double v) {
        std::ostringstream os;
        os.setf(std::ios::fixed);
        os.precision(2);
        os << "R" << v;
        return os.str();
    }
}

SafetyInspectionDecorator::SafetyInspectionDecorator(WorkComponent* component, double extraCost)
    : TaskDecorator(component), extraCost(extraCost) {}

std::string SafetyInspectionDecorator::getStatusReport() const {
    return TaskDecorator::getStatusReport()
         + "  {+ safety inspection: " + money(extraCost) + "}";
}

double SafetyInspectionDecorator::getCost() const {
    return TaskDecorator::getCost() + extraCost;
}
