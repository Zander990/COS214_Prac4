#ifndef CRITICALPATHITERATOR_H
#define CRITICALPATHITERATOR_H

#include "TaskIterator.h"
#include <cstddef>
#include <vector>

// GoF: Iterator — ConcreteIterator (filtered walk: "the critical path")
//
// SNAPSHOT POLICY: identical to FullSiteIterator. The filtered set is computed
// once, in the constructor. Membership is decided THEN: a task that is Blocked or
// In Progress at construction time is included; a task that changes state later
// does not join or leave this iterator. Build a fresh iterator to see the change.
class WorkGroup;
class WorkComponent;

class CriticalPathIterator : public TaskIterator {
private:
    std::vector<WorkComponent*> filtered;
    size_t position;

    // Recursive helper: keeps only ConstructionTask nodes whose current state is
    // "Blocked" or "In Progress". A filtering iterator selecting by concrete leaf
    // type is a legitimate Iterator use; no client code performs this check.
    void collect(WorkComponent* node);

public:
    explicit CriticalPathIterator(WorkGroup* root); // builds `filtered` up front (the snapshot)
    bool hasNext() const override;
    WorkComponent* next() override;
};

#endif // CRITICALPATHITERATOR_H
