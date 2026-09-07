#ifndef FULLSITEITERATOR_H
#define FULLSITEITERATOR_H

#include "TaskIterator.h"
#include <cstddef>
#include <vector>

// GoF: Iterator — ConcreteIterator (full pre-order walk of the whole hierarchy)
//
// SNAPSHOT POLICY: the traversal set is built completely in the constructor.
// The iterator reflects the hierarchy exactly as it was at construction time.
// Nodes added or removed afterwards are NOT seen by this iterator; create a new
// iterator to observe structural changes. (State values are read live from each
// node when next() hands it back, but the SET of nodes is frozen.)
class WorkGroup;
class WorkComponent;

class FullSiteIterator : public TaskIterator {
private:
    std::vector<WorkComponent*> flattened;
    size_t position;

    // Recursive pre-order helper. Uses friend access to WorkGroup::children to
    // descend into composites; the dynamic_cast here is an internal traversal
    // detail of the Iterator, not client-side type switching.
    void collect(WorkComponent* node);

public:
    explicit FullSiteIterator(WorkGroup* root); // builds `flattened` up front (the snapshot)
    bool hasNext() const override;
    WorkComponent* next() override;
};

#endif // FULLSITEITERATOR_H
