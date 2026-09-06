#include "PermitRequiredDecorator.h"

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

PermitRequiredDecorator::PermitRequiredDecorator(WorkComponent* component, double extraCost)
    : TaskDecorator(component), extraCost(extraCost) {}

std::string PermitRequiredDecorator::getStatusReport() const {
    return TaskDecorator::getStatusReport()
         + "  {+ permit required: " + money(extraCost) + "}";
}

double PermitRequiredDecorator::getCost() const {
    return TaskDecorator::getCost() + extraCost;
}
