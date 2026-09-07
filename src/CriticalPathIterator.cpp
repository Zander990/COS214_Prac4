#include "CriticalPathIterator.h"
#include "WorkComponent.h"
#include "WorkGroup.h"
#include "ConstructionTask.h"

// GoF: Iterator — ConcreteIterator (filtered "critical path" walk)

CriticalPathIterator::CriticalPathIterator(WorkGroup* root) : position(0) {
    // Filtered traversal is materialised now -> this is the snapshot.
    if (root) collect(root);
}

void CriticalPathIterator::collect(WorkComponent* node) {
    if (!node) return;

    // Keep leaf tasks that are currently on the critical path.
    ConstructionTask* task = dynamic_cast<ConstructionTask*>(node);
    if (task) {
        std::string s = task->getStateName();
        if (s == "Blocked" || s == "In Progress") {
            filtered.push_back(task);
        }
    }

    // Recurse into composites via friend access to WorkGroup::children.
    WorkGroup* group = dynamic_cast<WorkGroup*>(node);
    if (group) {
        for (size_t i = 0; i < group->children.size(); ++i) {
            collect(group->children[i]);
        }
    }
}

bool CriticalPathIterator::hasNext() const {
    return position < filtered.size();
}

WorkComponent* CriticalPathIterator::next() {
    if (!hasNext()) return nullptr;
    return filtered[position++];
}
