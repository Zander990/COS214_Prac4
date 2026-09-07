#ifndef TASKDECORATOR_H
#define TASKDECORATOR_H

#include "WorkComponent.h"

// GoF: Decorator — Decorator (abstract)
// Is-a WorkComponent AND has-a WorkComponent, so decorators stack arbitrarily.
// Ownership: a decorator OWNS the component it wraps and deletes it. Therefore the
// object added to a WorkGroup must be the OUTERMOST decorator, never the raw task
// as well — otherwise it would be deleted twice.
class TaskDecorator : public WorkComponent {
protected:
    WorkComponent* wrapped; // owned

public:
    explicit TaskDecorator(WorkComponent* component);
    ~TaskDecorator() override;                       // deletes wrapped

    std::string getName() const override;            // delegate
    std::string getStatusReport() const override;    // delegate (concrete decorators append)
    double getCost() const override;                 // delegate (concrete decorators add)
};

#endif // TASKDECORATOR_H
