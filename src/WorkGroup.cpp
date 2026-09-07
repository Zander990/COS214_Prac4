#include "WorkGroup.h"
#include "FullSiteIterator.h"
#include "CriticalPathIterator.h"

#include <algorithm>
#include <sstream>

// GoF: Composite — Composite ;  GoF: Iterator — ConcreteAggregate

namespace {
    std::string money(double v) {
        std::ostringstream os;
        os.setf(std::ios::fixed);
        os.precision(2);
        os << "R" << v;
        return os.str();
    }
}

WorkGroup::WorkGroup(const std::string& id, const std::string& name)
    : WorkComponent(id, name) {}

// Destruction policy: a WorkGroup OWNS its children. Deleting the root recursively
// deletes the whole tree exactly once. (Decorators own what they wrap, so a
// decorated child is deleted through its outermost decorator here.)
WorkGroup::~WorkGroup() {
    for (size_t i = 0; i < children.size(); ++i) {
        delete children[i];
    }
    children.clear();
}

std::string WorkGroup::getStatusReport() const {
    std::ostringstream os;
    os << "[" << id << "] " << name
       << "  (group: " << children.size() << " direct child(ren)"
       << ", subtotal: " << money(getCost()) << ")";
    return os.str();
}

double WorkGroup::getCost() const {
    double total = 0.0;
    for (size_t i = 0; i < children.size(); ++i) {
        total += children[i]->getCost(); // polymorphic: Leaf, Composite or Decorator
    }
    return total;
}

void WorkGroup::add(WorkComponent* component) {
    if (component) children.push_back(component);
}

// remove() only DETACHES the child (used when moving a task between groups).
// It never deletes — the caller becomes responsible for the pointer.
void WorkGroup::remove(WorkComponent* component) {
    std::vector<WorkComponent*>::iterator it =
        std::find(children.begin(), children.end(), component);
    if (it != children.end()) children.erase(it);
}

TaskIterator* WorkGroup::createFullIterator() {
    return new FullSiteIterator(this);
}

TaskIterator* WorkGroup::createCriticalPathIterator() {
    return new CriticalPathIterator(this);
}
