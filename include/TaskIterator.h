#ifndef TASKITERATOR_H
#define TASKITERATOR_H

// GoF: Iterator — Iterator (abstract iterator interface)
// Client code (main.cpp) is only ever handed a TaskIterator* and may only call
// hasNext()/next(). It never sees WorkGroup's internal std::vector.
class WorkComponent; // forward declare — avoids pulling the whole hierarchy in here

class TaskIterator {
public:
    virtual ~TaskIterator();                 // polymorphic base => virtual destructor
    virtual bool hasNext() const = 0;
    virtual WorkComponent* next() = 0;
};

#endif // TASKITERATOR_H
