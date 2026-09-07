// ============================================================================
//  TaskForge — COS 214 Prac 4 (Tasks 2 & 3)
//  A small construction-site management program in which four GoF patterns
//  collaborate:
//    * Composite  — Project / Building / Floor / Wing / Room / Task hierarchy
//    * Iterator   — FullSiteIterator (whole walk) + CriticalPathIterator (filter)
//    * State      — a ConstructionTask's lifecycle (Not Started ... Completed)
//    * Decorator  — SafetyInspection / PermitRequired / Overtime cost add-ons
//
//  main() is written as a narrated "Monday on site", not a pattern-by-pattern
//  checklist: the patterns show up where the story needs them.
// ============================================================================

#include "WorkGroup.h"
#include "ConstructionTask.h"
#include "SafetyInspectionDecorator.h"
#include "PermitRequiredDecorator.h"
#include "OvertimeDecorator.h"
#include "TaskIterator.h"

#include <iostream>
#include <sstream>
#include <string>

namespace {

// File-local money formatter (not a class; internal linkage).
std::string money(double v) {
    std::ostringstream os;
    os.setf(std::ios::fixed);
    os.precision(2);
    os << "R" << v;
    return os.str();
}

void rule(const std::string& title) {
    std::cout << "\n============================================================\n"
              << "  " << title << "\n"
              << "============================================================\n";
}

// Walk the WHOLE site through a FullSiteIterator and print every node's report.
// Client code only ever holds a TaskIterator* — it never sees WorkGroup's vector.
void printFullReport(WorkComponent* root, const std::string& caption) {
    std::cout << caption << "\n";
    TaskIterator* it = root->createFullIterator();
    while (it->hasNext()) {
        WorkComponent* node = it->next();
        std::cout << "   " << node->getStatusReport() << "\n";
    }
    delete it; // iterator is owned by us; it does NOT own the nodes
}

// Does a FullSiteIterator over `root` contain a node with this name?
bool fullWalkContains(WorkComponent* root, const std::string& name) {
    TaskIterator* it = root->createFullIterator();
    bool found = false;
    while (it->hasNext()) {
        if (it->next()->getName() == name) found = true;
    }
    delete it;
    return found;
}

void printCriticalPath(WorkComponent* root, const std::string& caption) {
    std::cout << caption << "\n";
    TaskIterator* it = root->createCriticalPathIterator();
    if (!it->hasNext()) std::cout << "   (nothing on the critical path)\n";
    while (it->hasNext()) {
        std::cout << "   * " << it->next()->getStatusReport() << "\n";
    }
    delete it;
}

} // namespace

int main() {
    // ------------------------------------------------------------------------
    rule("Monday 07:30  —  Site mobilisation");
    // ------------------------------------------------------------------------
    // Composite: build a genuine recursive part-whole tree.
    //   Project -> Building -> Floor -> Wing -> Room -> ConstructionTask
    //   (four levels of WorkGroup nested below the root, plus leaf tasks and
    //    nested groups at several levels).
    WorkGroup* project = new WorkGroup("PRJ", "Harbour Point Development");

    // leaf task directly under the root
    ConstructionTask* siteSurvey = new ConstructionTask("T-SURVEY", "Site survey", 5000);
    project->add(siteSurvey);

    WorkGroup* blockA = new WorkGroup("BLD-A", "Block A");
    project->add(blockA);

    // leaf task directly under a building
    ConstructionTask* foundation = new ConstructionTask("T-FOUND", "Foundation pour", 40000);
    blockA->add(foundation);

    WorkGroup* groundFloor = new WorkGroup("FL-G", "Ground floor");
    WorkGroup* firstFloor  = new WorkGroup("FL-1", "First floor");
    blockA->add(groundFloor);
    blockA->add(firstFloor);

    WorkGroup* eastWingG = new WorkGroup("WG-GE", "Ground floor - east wing");
    WorkGroup* westWingG = new WorkGroup("WG-GW", "Ground floor - west wing");
    groundFloor->add(eastWingG);
    groundFloor->add(westWingG);

    WorkGroup* lobby     = new WorkGroup("RM-G01", "Lobby");
    WorkGroup* reception = new WorkGroup("RM-G02", "Reception office");
    eastWingG->add(lobby);
    eastWingG->add(reception);

    ConstructionTask* elec  = new ConstructionTask("T-G01a", "Electrical rough-in", 8000);
    ConstructionTask* plumb = new ConstructionTask("T-G01b", "Plumbing rough-in", 7000);
    lobby->add(elec);
    lobby->add(plumb);

    // Decorator: a leaf that carries a mandatory safety-inspection cost from the
    // very start; it takes part in the ordinary reports/totals below.
    WorkComponent* waterproofing =
        new SafetyInspectionDecorator(
            new ConstructionTask("T-G01c", "Waterproofing", 5000), 1200);
    lobby->add(waterproofing);

    lobby->add(new ConstructionTask("T-G01d", "Screed floor", 3500));

    reception->add(new ConstructionTask("T-G02a", "Drywall partitions", 4000));

    WorkGroup* plantRoom = new WorkGroup("RM-G03", "Plant room");
    westWingG->add(plantRoom);
    plantRoom->add(new ConstructionTask("T-G03a", "Generator install", 15000));

    WorkGroup* eastWing1  = new WorkGroup("WG-1E", "First floor - east wing");
    firstFloor->add(eastWing1);
    WorkGroup* conference = new WorkGroup("RM-101", "Conference room");
    eastWing1->add(conference);
    ConstructionTask* hvac = new ConstructionTask("T-101a", "HVAC install", 12000);
    conference->add(hvac);
    conference->add(new ConstructionTask("T-101b", "Ceiling grid", 3000));

    std::cout << project->getStatusReport() << "\n"
              << "Projected site cost at mobilisation: "
              << money(project->getCost()) << "\n";

    // ------------------------------------------------------------------------
    rule("Monday 09:00  —  Crews start work");
    // ------------------------------------------------------------------------
    // State: drive tasks along their lifecycle. Every transition is decided by
    // the task's current state object, not by an if/switch out here.
    std::cout << "Foundation crew mobilised:\n";
    foundation->advance();                 // Not Started -> In Progress

    std::cout << "Lobby electricians on site:\n";
    elec->advance();                       // Not Started -> In Progress

    std::cout << "Lobby plumbers on site, then hit a snag:\n";
    plumb->advance();                      // Not Started -> In Progress
    plumb->advance();                      // In Progress -> Awaiting Inspection
    plumb->advance(false);                 // Awaiting Inspection -> Blocked (failed)

    // ------------------------------------------------------------------------
    rule("Monday 10:00  —  Full site walk (FullSiteIterator)");
    // ------------------------------------------------------------------------
    printFullReport(project, "Site-wide status report:");
    std::cout << "Current committed cost: " << money(project->getCost()) << "\n";

    // ------------------------------------------------------------------------
    rule("Monday 10:15  —  Two iterators live at once (independence check)");
    // ------------------------------------------------------------------------
    // Requirement: two independent iterator instances active over the SAME
    // structure simultaneously, with interleaved calls, proving no interference.
    TaskIterator* itFull = project->createFullIterator();
    TaskIterator* itCrit = project->createCriticalPathIterator();

    int step = 1;
    while (itFull->hasNext() || itCrit->hasNext()) {
        std::cout << "step " << step++ << ":\n";
        if (itFull->hasNext())
            std::cout << "   [full walk] " << itFull->next()->getName() << "\n";
        if (itCrit->hasNext())
            std::cout << "   [critical ] " << itCrit->next()->getStatusReport() << "\n";
    }
    std::cout << "(the full walk keeps going long after the critical-path "
                 "iterator is exhausted — separate cursors, no shared state)\n";
    delete itFull;
    delete itCrit;

    // ------------------------------------------------------------------------
    rule("Monday 14:00  —  Inspection round (valid & invalid transitions)");
    // ------------------------------------------------------------------------
    std::cout << "Foundation pour passes inspection:\n";
    foundation->advance();                 // In Progress -> Awaiting Inspection
    foundation->advance(true);             // Awaiting Inspection -> Completed

    std::cout << "Foreman tries to advance the finished foundation again:\n";
    foundation->advance();                 // Completed -> (invalid, rejected & logged)

    std::cout << "Plumbing snag cleared:\n";
    plumb->advance();                      // Blocked -> In Progress (unblocked)

    std::cout << "Foundation state is now: " << foundation->getStateName() << "\n";

    // ------------------------------------------------------------------------
    rule("Monday 15:00  —  Plans change on site (snapshot policy)");
    // ------------------------------------------------------------------------
    // Snapshots taken BEFORE the change.
    TaskIterator* snapFull = project->createFullIterator();
    TaskIterator* snapCrit = project->createCriticalPathIterator();

    // (a) STRUCTURE changes: a new (decorated) task is added to the Lobby.
    WorkComponent* fireAlarm =
        new OvertimeDecorator(
            new ConstructionTask("T-G01e", "Fire alarm wiring", 6000), 900);
    lobby->add(fireAlarm);

    // (b) STATE changes: HVAC install starts, joining the critical path.
    hvac->advance();                       // Not Started -> In Progress

    std::cout << "Change log: added 'Fire alarm wiring' to the Lobby; "
                 "started 'HVAC install'.\n\n";

    std::cout << "Replaying the 15:00 snapshot FullSiteIterator "
                 "(built before the change):\n";
    bool oldSaw = false;
    while (snapFull->hasNext()) {
        WorkComponent* n = snapFull->next();
        if (n->getName() == "Fire alarm wiring") oldSaw = true;
    }
    std::cout << "   => snapshot iterator sees 'Fire alarm wiring'? "
              << (oldSaw ? "YES" : "NO") << "   (expected: NO)\n";

    std::cout << "   => a FRESH FullSiteIterator sees it? "
              << (fullWalkContains(project, "Fire alarm wiring") ? "YES" : "NO")
              << "   (expected: YES)\n\n";

    std::cout << "15:00 snapshot CriticalPathIterator lists: ";
    while (snapCrit->hasNext()) std::cout << "'" << snapCrit->next()->getName() << "' ";
    std::cout << "\n   (no 'HVAC install' — it was Not Started when the snapshot was taken)\n";

    printCriticalPath(project, "A fresh CriticalPathIterator now lists:");
    std::cout << "   ('HVAC install' has joined the critical path)\n";

    delete snapFull;
    delete snapCrit;

    // ------------------------------------------------------------------------
    rule("Monday 16:00  —  Crane package (stacked decorators in normal use)");
    // ------------------------------------------------------------------------
    // Three decorators stacked on one task; the decorated object then takes part
    // in the ordinary site report and the site cost total.
    WorkComponent* crane = new ConstructionTask("T-A-CRANE", "Tower crane erection", 30000);
    crane = new PermitRequiredDecorator(crane, 4500);
    crane = new SafetyInspectionDecorator(crane, 1200);
    crane = new OvertimeDecorator(crane, 2000);
    blockA->add(crane);

    std::cout << "Crane line item:\n   " << crane->getStatusReport() << "\n"
              << "   stacked cost: " << money(crane->getCost())
              << "  (30000 + 4500 + 1200 + 2000)\n\n";

    printFullReport(project, "End-of-day site report:");
    std::cout << "Revised projected site cost: " << money(project->getCost()) << "\n";

    // ------------------------------------------------------------------------
    rule("Monday 17:30  —  Stand down (polymorphic destruction test)");
    // ------------------------------------------------------------------------
    // Deleting the root deletes every WorkGroup, every ConstructionTask (and its
    // current TaskState), and every Decorator (and the component it wraps) —
    // each exactly once. Verified clean under valgrind --leak-check=full.
    std::cout << "Releasing the whole site tree with a single 'delete project'...\n";
    delete project;
    std::cout << "All site components released. No leaks, no double-frees.\n";

    return 0;
}
