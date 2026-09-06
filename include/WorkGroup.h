#ifndef WORKGROUP_H
#define WORKGROUP_H

#include "WorkComponent.h"
#include <string>
#include <vector>

// GoF: Composite — Composite (holds children, implements add/remove/getCost)
// GoF: Iterator  — ConcreteAggregate (createFullIterator / createCriticalPathIterator)
//
// The children vector is PRIVATE and never returned. The only two types allowed
// to see it are the two concrete iterators, granted via "friend" below, so that
// client code can traverse the tree without ever touching the container.
class WorkGroup : public WorkComponent {
private:
    std::vector<WorkComponent*> children; // owned: this group deletes every child

    friend class FullSiteIterator;
    friend class CriticalPathIterator;

public:
    WorkGroup(const std::string& id, const std::string& name);
    ~WorkGroup() override;                         // deletes every pointer in children

    std::string getStatusReport() const override;
    double getCost() const override;              // sum of children's getCost()

    void add(WorkComponent* component) override;
    void remove(WorkComponent* component) override; // detaches only; does NOT delete

    TaskIterator* createFullIterator() override;
    TaskIterator* createCriticalPathIterator() override;
};

#endif // WORKGROUP_H
