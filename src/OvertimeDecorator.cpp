#include "OvertimeDecorator.h"

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

OvertimeDecorator::OvertimeDecorator(WorkComponent* component, double extraCost)
    : TaskDecorator(component), extraCost(extraCost) {}

std::string OvertimeDecorator::getStatusReport() const {
    return TaskDecorator::getStatusReport()
         + "  {+ overtime shift: " + money(extraCost) + "}";
}

double OvertimeDecorator::getCost() const {
    return TaskDecorator::getCost() + extraCost;
}
