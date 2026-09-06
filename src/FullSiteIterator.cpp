#include "FullSiteIterator.h"
#include "WorkComponent.h"
#include "WorkGroup.h"

// GoF: Iterator — ConcreteIterator (full pre-order walk)

FullSiteIterator::FullSiteIterator(WorkGroup* root) : position(0) {
    // Whole traversal is materialised now -> this is the snapshot.
    if (root) collect(root);
}

void FullSiteIterator::collect(WorkComponent* node) {
    if (!node) return;
    flattened.push_back(node); // pre-order: visit the node itself first

    // Descend only into composites. friend access lets us read children directly
    // without WorkGroup ever exposing the container to client code.
    WorkGroup* group = dynamic_cast<WorkGroup*>(node);
    if (group) {
        for (size_t i = 0; i < group->children.size(); ++i) {
            collect(group->children[i]);
        }
    }
}

bool FullSiteIterator::hasNext() const {
    return position < flattened.size();
}

WorkComponent* FullSiteIterator::next() {
    if (!hasNext()) return nullptr;
    return flattened[position++];
}
