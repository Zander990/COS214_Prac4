#include "TaskIterator.h"

// GoF: Iterator — Iterator (abstract iterator interface)
// Out-of-line virtual destructor: gives the class a definitive translation unit
// (a "key function") and a single home for its vtable.
TaskIterator::~TaskIterator() {}
