#ifndef WORKCOMPONENT_H
#define WORKCOMPONENT_H

#include <string>

// GoF: Composite — Component (common interface for leaves and composites)
// Also the element type produced by the Iterator pattern (TaskIterator::next()).
// Every operation that only makes sense on a composite (add/remove/createXIterator)
// has a safe default here so a Leaf never has to override it.
class TaskIterator; // forward declare — breaks the Component <-> Iterator cycle

class WorkComponent {
protected:
    std::string id;
    std::string name;

public:
    WorkComponent(const std::string& id, const std::string& name);
    virtual ~WorkComponent();                       // polymorphic base => virtual destructor

    virtual std::string getName() const;
    virtual std::string getId() const;

    // The ONLY override every concrete class is forced to provide.
    virtual std::string getStatusReport() const = 0;

    virtual double getCost() const;                 // default: 0.0

    // Composite-management operations. Default = no-op so a Leaf (ConstructionTask)
    // and the Decorators inherit harmless behaviour instead of type-checking.
    virtual void add(WorkComponent* component);
    virtual void remove(WorkComponent* component);

    // Iterator factory methods (GoF: Iterator — the ConcreteAggregate hook).
    // Default: nullptr — only WorkGroup returns real iterators.
    virtual TaskIterator* createFullIterator();
    virtual TaskIterator* createCriticalPathIterator();
};

#endif // WORKCOMPONENT_H
