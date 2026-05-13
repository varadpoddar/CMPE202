# CMPE 202 — Final Exam Study Guide
**Exam: Wednesday May 13, 2026 at 5:30 PM**

---

## TABLE OF CONTENTS
1. [Recursion](#1-recursion)
2. [Backtracking](#2-backtracking)
3. [Multithreading — Race Conditions](#3-multithreading--race-conditions)
4. [Mutex & lock_guard (RAII)](#4-mutex--lock_guard-raii)
5. [Thread Yielding](#5-thread-yielding)
6. [Reader-Writer Lock](#6-reader-writer-lock)
7. [Producer-Consumer](#7-producer-consumer)
8. [Dining Philosophers (Deadlock)](#8-dining-philosophers-deadlock)
9. [Single Responsibility Principle (SRP)](#9-single-responsibility-principle-srp)
10. [Open-Closed Principle (OCP)](#10-open-closed-principle-ocp)
11. [Law of Demeter](#11-law-of-demeter)
12. [Template Method Pattern](#12-template-method-pattern)
13. [Strategy Pattern](#13-strategy-pattern)
14. [Factory Method Pattern](#14-factory-method-pattern)
15. [Abstract Factory Pattern](#15-abstract-factory-pattern)
16. [Adapter Pattern](#16-adapter-pattern)
17. [Facade Pattern](#17-facade-pattern)
18. [Iterator Pattern](#18-iterator-pattern)
19. [Visitor Pattern](#19-visitor-pattern)
20. [Observer Pattern](#20-observer-pattern)
21. [State Pattern](#21-state-pattern)
22. [Singleton Pattern](#22-singleton-pattern)
23. [Composite Pattern](#23-composite-pattern)
24. [Decorator Pattern](#24-decorator-pattern)
25. [Lambda Expressions](#25-lambda-expressions)
26. [Functors (Function Objects)](#26-functors-function-objects)
27. [Smart Pointers — unique_ptr](#27-smart-pointers--unique_ptr)
28. [Smart Pointers — shared_ptr](#28-smart-pointers--shared_ptr)
29. [Move Semantics](#29-move-semantics)

---

## 1. Recursion

**Concept:** A function solves a problem by calling itself on a smaller version of the same problem. Every recursive function needs:
- **Base case** — the simplest input that can be solved directly (no recursion).
- **Recursive case** — break the problem into a smaller version + recurse.

**Key insight:** Each recursive call has its own stack frame. Never modify the original data structure if you need it after the call — pass copies or use indices.

**Lab:** [labs/Program15.1-Largest/](labs/Program15.1-Largest/)
```cpp
int largest(vector<int> v) {
    if (v.size() == 1) return v[0];         // Base case
    int first = v[0];
    v.erase(v.begin());
    int rest = largest(v);                  // Recursive case
    return first > rest ? first : rest;
}
```

**Lab:** [labs/Program15.2-Reverse/](labs/Program15.2-Reverse/) — reverses a string recursively.

**Lab:** [labs/Program15.3-Towers/](labs/Program15.3-Towers/) — Tower of Hanoi: move N disks via 3 pegs.
```cpp
void solve(int n, char src, char tmp, char dst) {
    if (n == 1) { cout << src << " ==> " << dst << endl; return; }
    solve(n-1, src, dst, tmp);   // Move top n-1 out of the way
    solve(1,   src, tmp, dst);   // Move the big disk
    solve(n-1, tmp, src, dst);   // Move top n-1 to destination
}
```

**Lab:** [labs/Program15.5-Quicksort/](labs/Program15.5-Quicksort/) — divide-and-conquer sort.
```cpp
void Quicksort::sort(int left, int right) {
    if (right - left + 1 < 2) return;       // Base case: 0 or 1 element
    int pivot = partition(left, right);
    sort(left, pivot - 1);                  // Sort left partition
    sort(pivot + 1, right);                 // Sort right partition
}
```

**Lab:** [labs/Program15.6-Fibonacci/](labs/Program15.6-Fibonacci/) — shows exponential vs memoized recursion.

---

## 2. Backtracking

**Concept:** Backtracking is recursion with an **undo step**. Try a choice → recurse → if it fails, undo the choice and try the next one. Used when you must explore all possible solutions.

**Pattern:**
```
for each candidate:
    if candidate is valid:
        place candidate
        if at solution: record it
        else: recurse deeper
        remove candidate    ← THE BACKTRACK
```

**Lab:** [labs/Program15.7-Queens/](labs/Program15.7-Queens/) — N-Queens: place N queens so none attack each other.
```cpp
void Queens::search_for_solutions(int col) {
    for (int row = 0; row < SIZE; row++) {
        if (is_safe_square(row, col)) {
            occupied[row][col] = true;
            if (col == SIZE - 1) print();           // Found a solution
            else search_for_solutions(col + 1);     // Go deeper
            occupied[row][col] = false;             // BACKTRACK
        }
    }
}
```

**Lab:** [labs/Program15.8-Sudoku/](labs/Program15.8-Sudoku/) — Sudoku solver with constraint checking.
```cpp
bool Sudoku::does_solution_exist(int row, int col) {
    if (row == GRID_SIZE-1 && col == GRID_SIZE) return true;  // Solved!
    if (col == GRID_SIZE) { row++; col = 0; }
    if (grid[row][col] != 0) return does_solution_exist(row, col+1); // Skip fixed
    for (int n = 1; n <= GRID_SIZE; n++) {
        if (is_number_ok(row, col, n)) {
            grid[row][col] = n;
            if (does_solution_exist(row, col+1)) return true;
        }
    }
    grid[row][col] = 0;   // BACKTRACK
    return false;
}
```

---

## 3. Multithreading — Race Conditions

**Concept:** When multiple threads access shared resources without synchronization, their operations interleave unpredictably — this is a **race condition**. Output becomes garbled; data gets corrupted.

**Lab:** [labs/Program16.1-Printing-unprotected/](labs/Program16.1-Printing-unprotected/) — three threads write to `cout` simultaneously without any lock.
```cpp
void print(string text) {
    for (const char& ch : text) cout << ch;  // No protection — garbled output
}
int main() {
    thread t1(print, "Hello, world!\n");
    thread t2(print, "Use good design!\n");
    thread t3(print, "Go multithreaded!\n");
    t1.join(); t2.join(); t3.join();
}
```

**Key rules:**
- Always `join()` threads before the owning scope exits.
- Any shared mutable state needs a synchronization mechanism.

---

## 4. Mutex & lock_guard (RAII)

**Concept:** A **mutex** (mutual exclusion) ensures only one thread enters a critical section at a time. `lock_guard` uses RAII — the lock is acquired on construction and **automatically released** when the guard goes out of scope, even if an exception is thrown.

**Lab:** [labs/Program16.2a-noyields/](labs/Program16.2a-noyields/) — manual `lock()`/`unlock()`. Risky: if you forget `unlock()` or an exception is thrown, the mutex is never released (deadlock).
```cpp
mutex print_mutex;
void print(string text) {
    print_mutex.lock();
    for (const char& ch : text) cout << ch;
    print_mutex.unlock();   // Risky: exception would skip this
}
```

**Lab:** [labs/Program16.2c-lockguard/](labs/Program16.2c-lockguard/) — `lock_guard` (preferred).
```cpp
mutex print_mutex;
void print(string text) {
    lock_guard<mutex> guard(print_mutex);   // Locked here
    for (const char& ch : text) cout << ch;
}   // Automatically unlocked when guard goes out of scope
```

**Why prefer `lock_guard`:** Exception-safe. Cannot forget to unlock. Follows RAII.

---

## 5. Thread Yielding

**Concept:** `this_thread::yield()` voluntarily relinquishes the CPU, giving the scheduler a hint to run another thread. Useful to improve fairness and reduce starvation when holding a lock over a loop.

**Lab:** [labs/Program16.2b-yields/](labs/Program16.2b-yields/)
```cpp
void print(string text) {
    for (int i = 0; i < COUNT; i++) {
        print_mutex.lock();
        for (const char& ch : text) cout << ch;
        this_thread::yield();   // Let other threads run
        print_mutex.unlock();
    }
}
```

---

## 6. Reader-Writer Lock

**Concept:** Multiple readers can read concurrently (no data modification). Only one writer is allowed, and no readers are allowed while a writer holds the lock. C++17 provides `shared_mutex` for this.

| Lock type | Writers | Readers |
|-----------|---------|---------|
| `unique_lock<shared_mutex>` | Exclusive | Blocks all |
| `shared_lock<shared_mutex>` | Blocked if writer | Multiple OK |

**Lab:** [labs/Program16.3-ReaderWriter/](labs/Program16.3-ReaderWriter/)
```cpp
shared_mutex meter_mutex;

void Meter::set_meter(int id) {       // WRITER
    unique_lock<shared_mutex> lk(meter_mutex);
    setting = rand() % MAX + 1;
}
void Meter::log_meter(int id) {       // READER
    shared_lock<shared_mutex> lk(meter_mutex);
    printf("LOGGER #%d: logging %d\n", id, setting);
}
```

---

## 7. Producer-Consumer

**Concept:** Producers generate items into a shared bounded queue; consumers remove and process them. Need synchronization to prevent:
- **Overflow** — producer adding to a full queue.
- **Underflow** — consumer removing from an empty queue.

**Lab:** [labs/Program16.4-ProducerConsumer/](labs/Program16.4-ProducerConsumer/)
```cpp
class SharedQueue {
public:
    bool is_empty() const { return data.size() == 0; }
    bool is_full()  const { return data.size() == capacity; }
    void enter(int v) { data.push(v); }
    int  remove()    { int v = data.front(); data.pop(); return v; }
    mutex& get_mutex() { return queue_mutex; }
private:
    queue<int> data;
    size_t capacity;
    mutex queue_mutex;
};
```

---

## 8. Dining Philosophers (Deadlock)

**Concept:** 5 philosophers alternate between thinking and eating, sharing 5 chopsticks. Naive implementation deadlocks (everyone picks up left chopstick and waits forever for right). Solutions use `atomic` state, `condition_variable`, or ordered resource acquisition.

**Lab:** [labs/DiningPhilosophers/](labs/DiningPhilosophers/)
```cpp
enum class PhilosopherState { Thinking, Hungry, Filling, Eating, Done };

class Philosopher {
    atomic<PhilosopherState> state;
    mutex mtx;
    condition_variable cv;
    bool using_chopstick() const {
        auto s = state.load();
        return s == PhilosopherState::Filling || s == PhilosopherState::Eating;
    }
};
```

**Deadlock conditions (all 4 must hold):**
1. Mutual exclusion
2. Hold and wait
3. No preemption
4. Circular wait

Break any one to prevent deadlock.

---

## 9. Single Responsibility Principle (SRP)

**Concept:** A class should have only **one reason to change**. If a class handles multiple concerns (storage + search + formatting), a change to any concern forces recompilation and retesting of the whole class.

**Bad — [labs/Program2.1-Books-1/](labs/Program2.1-Books-1/):** `Catalogue` handles storage, search logic, AND string comparison.
```cpp
class Catalogue {
    void add(string title, string last, string first);
    vector<Book*> find(const Book& target) const;
    // Also has string comparison helpers -- three responsibilities!
    static bool equal_ignore_case(string s1, string s2);
};
```

**Good — [labs/Program2.5-Books-5/](labs/Program2.5-Books-5/):** Separate classes: `Book` (data), `Attributes` (metadata), `Catalogue` (only storage).

**Progression:** Programs 2.1 → 2.2 → 2.3 → 2.4 → 2.5 each extract one more responsibility.

---

## 10. Open-Closed Principle (OCP)

**Concept:** Software should be **open for extension, closed for modification**. Add new behavior by adding new classes, not by modifying existing ones.

**Bad — [labs/Program4.1-Automobile-1/](labs/Program4.1-Automobile-1/):** Adding a new vehicle type requires modifying existing switch statements.

**Good — [labs/Program4.4-VehicleInterface/](labs/Program4.4-VehicleInterface/):** Define an interface; new types just implement it.
```cpp
class MotorVehicleInterface {
public:
    virtual void start_engine()  = 0;
    virtual void stop_engine()   = 0;
    virtual void accelerate()    = 0;
    virtual void apply_brakes()  = 0;
    virtual void drive()         = 0;
};
// Car, Truck, Motorcycle implement this — no changes to existing code
```

**Progression:** 4.1 (concrete) → 4.2 (abstract base) → 4.3 (abstract class) → 4.4 (pure interface).

---

## 11. Law of Demeter

**Concept:** "Only talk to your immediate friends." A method should only call methods on:
- `this`
- Its own fields
- Parameters passed to it
- Objects it created

**Violation:** `obj.get_sub_object()->do_something()` — you are reaching into another object's internals.

**Bad — [labs/Program5.7-DemeterAuto/](labs/Program5.7-DemeterAuto/):**
```cpp
// Reaching into Engine to get a Sparkplug — Demeter violation
Sparkplug *plug = engine.get_sparkplug();
plug->replace();
```

**Good — delegate:**
```cpp
engine.replace_sparkplug();  // Engine manages its own sparkplug
```

**Bad — [labs/Program5.8-HiddenDate-1/](labs/Program5.8-HiddenDate-1/):** Returns internal pointer.
```cpp
Date *get_birthdate() { return birthdate; }  // Caller can mutate internals
```

**Good — [labs/Program5.9-HiddenDate-2/](labs/Program5.9-HiddenDate-2/):** Returns a copy.
```cpp
Date *get_birthdate() { return new Date(*birthdate); }  // Safe copy
```

---

## 12. Template Method Pattern

**Concept:** Define the **skeleton of an algorithm** in a base class, deferring some steps to subclasses. The overall sequence is fixed; only the varying parts are overridden.

**Bad — [labs/Program8.1-Reports/](labs/Program8.1-Reports/):** `BaseballReport` and `VolleyballReport` each duplicate the full `generate_report()` flow.

**Good — [labs/Program8.2-Reports-TemplateDP/](labs/Program8.2-Reports-TemplateDP/):**
```cpp
class GameReport {                          // Base: defines the template
public:
    void generate_report() {                // FIXED sequence
        print_header();
        acquire_data();                     // abstract — subclass fills in
        analyze_data();                     // abstract — subclass fills in
        print_report();                     // abstract — subclass fills in
        print_footer();
    }
protected:
    void print_header() const { cout << title << endl; }   // Concrete
    void print_footer() const { cout << "End of report" << endl; }
    virtual void acquire_data()  = 0;      // Pure virtual
    virtual void analyze_data()  = 0;
    virtual void print_report() const = 0;
};
```

**When to use:** Same sequence of steps, but steps vary per type. Eliminates code duplication.

---

## 13. Strategy Pattern

**Concept:** Define a family of algorithms, encapsulate each one, and make them interchangeable. Lets you change behavior at runtime without modifying the class that uses the behavior.

**Bad — [labs/Program8.3-Sports/](labs/Program8.3-Sports/):** Recruitment and venue logic hardcoded inside `Sport`.

**Good — [labs/Program8.4-Sports-StrategyDP/](labs/Program8.4-Sports-StrategyDP/):**
```cpp
class PlayerStrategy { public: virtual string strategy() const = 0; };
class VenueStrategy  { public: virtual string strategy() const = 0; };

class Sport {
public:
    Sport(Type t, PlayerStrategy *ps, VenueStrategy *vs)
        : player_strategy(ps), venue_strategy(vs) {}
    string recruit_players() const { return player_strategy->strategy(); }
    string reserve_venue()   const { return venue_strategy->strategy(); }
    void set_player_strategy(PlayerStrategy *ps) { player_strategy = ps; } // Swap at runtime
private:
    PlayerStrategy *player_strategy;
    VenueStrategy  *venue_strategy;
};
```

**vs. Template Method:** Strategy uses composition (has-a); Template Method uses inheritance (is-a). Strategy can change at runtime.

---

## 14. Factory Method Pattern

**Concept:** Define an interface for creating an object, but let subclasses decide which class to instantiate. The creator class defers instantiation to subclasses via a virtual factory method.

**Lab:** [labs/Program7.7-Toys-4/](labs/Program7.7-Toys-4/) — `ToyFactory::make()` centralizes creation.
```cpp
class ToyFactory {
public:
    static Toy *make(Kind kind) {
        switch (kind) {
            case Kind::CAR:      return new ToyCar(new Roll(), new Engine());
            case Kind::AIRPLANE: return new ModelAirplane(new Fly(), new Engine());
            case Kind::TRAIN:    return new TrainSet(new Roll(), new ChooChoo());
            default: return nullptr;
        }
    }
};
```

**Lab:** [labs/Program9.2-Provisions-FactoryDP/](labs/Program9.2-Provisions-FactoryDP/) — abstract factory method in base class.
```cpp
class AthleticsDept {
public:
    void generate_report(const Type& type) {
        Sport *s = create_sport(type);   // Delegates to subclass
        s->generate_report();
    }
private:
    virtual Sport *create_sport(const Type& type) = 0;  // Factory method
};
class VarsityDept : public AthleticsDept {
    Sport *create_sport(const Type& type) override { /* varsity sport */ }
};
```

**Progression:** 7.4 (plain hierarchy) → 7.5 → 7.6 → 7.7 (factory).

---

## 15. Abstract Factory Pattern

**Concept:** Provides an interface for creating **families of related objects** without specifying their concrete classes. Instead of one factory method, you have a factory with multiple methods — one per product in the family.

**Lab:** [labs/Program9.3-Provisions-AbsFactoryDP/](labs/Program9.3-Provisions-AbsFactoryDP/)
```cpp
class ProvisionsFactory {
public:
    virtual PlayerStrategy *make_players(const Type& type) = 0;
    virtual VenueStrategy  *make_venue() = 0;
};
class VarsityFactory : public ProvisionsFactory {
public:
    PlayerStrategy *make_players(const Type& type) override { /* varsity players */ }
    VenueStrategy  *make_venue()                   override { return new Stadium(); }
};
class IntramuralFactory : public ProvisionsFactory {
public:
    PlayerStrategy *make_players(const Type& type) override { /* intramural players */ }
    VenueStrategy  *make_venue()                   override { return new Gym(); }
};
```

**Factory Method vs Abstract Factory:**
- Factory Method: one product, one factory method, subclasses override it.
- Abstract Factory: a whole *family* of products, each with its own factory method in one factory object.

---

## 16. Adapter Pattern

**Concept:** Converts the interface of a class into another interface that clients expect. Allows incompatible interfaces to work together without modifying either.

**Bad — [labs/Program10.1-Fans/](labs/Program10.1-Fans/):** `AttendanceReport` has multiple overloaded `print()` methods for each incompatible data source.

**Good — [labs/Program10.2-Fans-AdapterDP/](labs/Program10.2-Fans-AdapterDP/):** One inner `ConvertedData` adapter class wraps each foreign type to the expected interface.
```cpp
class AttendanceReport {
private:
    class ConvertedData : public AttendanceData {   // Adapter
    public:
        ConvertedData(Venue v, int a) : venue(v), attendance(a) {}
        Venue get_venue()      const override { return venue; }
        int   get_attendance() const override { return attendance; }
    };
    void legacy_print(const AttendanceData& data) const;  // Single print method
};
// Usage: legacy_print(ConvertedData(football_info.venue(), football_info.fans()));
```

**Variation — [labs/Program10.3-Fans-AdapterDPx/](labs/Program10.3-Fans-AdapterDPx/):** Multiple separate adapter classes.

---

## 17. Facade Pattern

**Concept:** Provides a simplified interface to a complex subsystem. Clients use the facade; they don't need to know the subsystem's internals.

**Bad — [labs/Program10.4-Funds/](labs/Program10.4-Funds/):** Client must know and call `Administration`, `Alumni`, `AthleticsDept`, `BoosterClubs`, `Students` independently.

**Good — [labs/Program10.5-Funds-FacadeDP/](labs/Program10.5-Funds-FacadeDP/):**
```cpp
class FundRaiser {                          // Facade
public:
    void do_fund_raising() {                // Single entry point
        Alumni     alumni;    alumni.send_solicitations();
        BoosterClubs clubs;   clubs.schedule_meetings();
        Students   students;  students.collect_fees();
    }
};
// Client only knows FundRaiser, not the 3 subsystem classes
```

---

## 18. Iterator Pattern

**Concept:** Provides a way to access elements of a collection sequentially without exposing the underlying representation (array, vector, map, tree, etc.).

**Lab:** [labs/Program11.2-PlayersIteratorDP/](labs/Program11.2-PlayersIteratorDP/)
```cpp
class Iterator {
public:
    virtual Player *next()      = 0;
    virtual bool   has_next() const = 0;
};
class VectorIterator : public Iterator {
public:
    VectorIterator(vector<Player*> ps) : players(ps), cursor(players.begin()) {}
    Player *next()      override { return *(cursor++); }
    bool   has_next() const override { return cursor != players.end(); }
};
class MapIterator : public Iterator { /* same interface, different container */ };
```

Client code uses only `has_next()` / `next()` — doesn't know if it's a vector, map, or array underneath.

---

## 19. Visitor Pattern

**Concept:** Lets you add new operations to a class hierarchy **without modifying those classes**. The object "accepts" a visitor; the visitor performs the operation. Separates algorithms from the objects they operate on.

**Lab:** [labs/Program11.4-Results-VisitorDP/](labs/Program11.4-Results-VisitorDP/)
```cpp
class Node {
public:
    virtual void accept(Visitor& v) = 0;   // Accept any visitor
};
class Visitor {
public:
    virtual void visit_Sport(Sport *n) = 0;
    virtual void visit_Game(Game *n)   = 0;
    virtual void visit_Hall(Hall *n)   = 0;
};
// Add a new report type: just create a new Visitor subclass
class ScoresReportVisitor  : public Visitor { /* ... */ };
class WinningsReportVisitor: public Visitor { /* ... */ };
```

**When to use:** Object structure is stable; operations on it change frequently.
**vs. Iterator:** Iterator traverses; Visitor operates on each element with type-specific behavior.

---

## 20. Observer Pattern

**Concept:** Defines a one-to-many dependency: when one object (Subject) changes state, all its dependents (Observers) are notified automatically. Decouples the subject from who cares about its state.

**Bad — [labs/Program12.1-Stats/](labs/Program12.1-Stats/):** Multiple reporters independently poll the data source.

**Good — [labs/Program12.2-Stats-ObserverDP/](labs/Program12.2-Stats-ObserverDP/):**
```cpp
class Observer {
public:
    virtual void update(const string name, const int outs) = 0;
};
class Subject {
public:
    void attach(Observer *o) { observers.push_back(o); }
    void detach(Observer *o);
    void notify(const string name, const int outs) const {
        for (Observer *o : observers) o->update(name, outs);  // Push to all
    }
private:
    vector<Observer*> observers;
};
// GraphReport, LogReport, FanClubReport each implement Observer
```

**Push vs Pull:** Subject can push data in `update()` args (shown above) or observers can pull from subject after notification.

---

## 21. State Pattern

**Concept:** Allows an object to alter its behavior when its internal state changes. The object will appear to change its class. Replace state-based `switch` statements with polymorphic state objects.

**Bad — [labs/Program13.1-TicketMachine/](labs/Program13.1-TicketMachine/):** One class with `State` enum and big switch in every method.
```cpp
void TicketMachine::insert_card() {
    switch (state) {
        case READY: state = VALIDATING; break;
        case SOLD_OUT: cout << "Machine empty"; break;
        // ...
    }
}
```

**Good — [labs/Program13.2-TicketMachnine-StateDP/](labs/Program13.2-TicketMachnine-StateDP/):**
```cpp
class State {                              // Abstract state
public:
    virtual State *insert_credit_card()  = 0;
    virtual State *check_validity()      = 0;
    virtual State *take_ticket()         = 0;
    virtual State *remove_credit_card()  = 0;
};
class READY : public State {              // Each state knows its own transitions
    State *insert_credit_card() override { return new VALIDATING(...); }
    State *take_ticket()        override { cout << "Insert card first"; return this; }
};
```

Machine stores `State *current` and delegates: `current = current->insert_credit_card();`

---

## 22. Singleton Pattern

**Concept:** Ensures a class has only one instance and provides a global access point to it. Uses private constructor + static `get_instance()` method.

**Lab:** [labs/Program14.1-ExecPass/](labs/Program14.1-ExecPass/) — controlled instantiation with private copy constructor.

**Standard Singleton:**
```cpp
class Singleton {
public:
    static Singleton& get_instance() {
        static Singleton instance;  // Created once, destroyed at program exit
        return instance;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
private:
    Singleton() {}
};
```

**Lab:** [labs/Program14.2-ExecPass-SingletonDP/](labs/Program14.2-ExecPass-SingletonDP/) *(note: zip was corrupt on server — see lecture slides for code)*.

---

## 23. Composite Pattern

**Concept:** Compose objects into **tree structures** to represent part-whole hierarchies. Clients treat individual objects and compositions uniformly through a common interface.

**Bad — [labs/Program14.3-CostReport/](labs/Program14.3-CostReport/):** Flat list of items; no nesting.

**Good — [labs/Program14.4-CostReport-CompositeDP/](labs/Program14.4-CostReport-CompositeDP/):**
```cpp
class ProvisionItem {                        // Component (leaf OR composite)
public:
    virtual double get_cost() const = 0;
    virtual void add(ProvisionItem *item) {
        throw logic_error("not a group");
    }
};
class ProvisionGroup : public ProvisionItem { // Composite
public:
    void add(ProvisionItem *item) override { provisions.push_back(item); }
    double get_cost() const override {        // Recursively sums children
        double total = 0;
        for (auto *item : provisions) total += item->get_cost();
        return total;
    }
private:
    vector<ProvisionItem*> provisions;
};
```

Client calls `root->get_cost()` — doesn't know or care if root is a leaf or a tree.

---

## 24. Decorator Pattern

**Concept:** Attaches additional responsibilities to an object **dynamically**. Decorators provide a flexible alternative to subclassing for extending functionality.

**Bad — [labs/Program14.5-Enhanced/](labs/Program14.5-Enhanced/):** Boolean flags + conditional pricing in constructor.
```cpp
class Ticket {
    double get_cost() const {
        double total = BASE_PRICE;
        if (pregame_party) total += PARTY_PRICE;
        if (vip_seating)   total += VIP_PRICE;
        return total + drink_coupons * COUPON_PRICE;
    }
};
```

**Good — [labs/Program14.6-Enhanced-DecoratorDP/](labs/Program14.6-Enhanced-DecoratorDP/):**
```cpp
class Ticket { public: virtual double get_cost() const = 0; };

class Decorator : public Ticket {           // Wraps another ticket
public:
    Decorator(string desc, double price, Ticket *t)
        : description(desc), price(price), ticket(t) {}
    double get_cost() const override {
        return price + ticket->get_cost();  // Add own price + delegate
    }
private:
    Ticket *ticket;
};
// Usage: wrap dynamically
Ticket *t = new BaseTicket();
t = new Party(t);       // Add party
t = new VIP(t);         // Add VIP
t = new Coupon(t, 3);   // Add 3 coupons
cout << t->get_cost();  // Computes total recursively
```

---

## 25. Lambda Expressions

**Concept:** Anonymous inline functions. Capture local variables from the enclosing scope. Syntax: `[capture](params) -> return_type { body }`.

**Lab:** [labs/Lambda-1/](labs/Lambda-1/) — using function pointers (old way).
```cpp
bool is_male(const Person& p) { return p.gender == Gender::M; }
vector<Person> males = select(people, is_male);
```

**Lab:** [labs/Lambda-2/](labs/Lambda-2/) — lambda expressions.
```cpp
vector<Person> males = select(people,
    [](const Person& p) -> bool { return p.gender == Gender::M; });

// Capture local variable by value:
string target = "Smith";
auto smiths = select(people,
    [target](const Person& p) { return p.last == target; });
```

**Lab:** [labs/Lambda-3/](labs/Lambda-3/) — lambdas with `std::sort`, `std::find_if`, `std::for_each`.

**Capture modes:**
- `[]` — capture nothing
- `[=]` — capture all by value
- `[&]` — capture all by reference
- `[x, &y]` — x by value, y by reference

---

## 26. Functors (Function Objects)

**Concept:** A class that overloads `operator()`, making its instances callable like functions. Unlike plain functions, functors can carry **state** between calls.

**Lab:** [labs/Functor-Randomint/](labs/Functor-Randomint/)
```cpp
class RandomInt {
public:
    RandomInt(int min, int max) : min(min), max(max) { srand(time(NULL)); }
    int operator()() {                              // Makes instance callable
        return min + rand() % (max - min + 1);
    }
private:
    int min, max;   // State persists between calls
};

RandomInt roll(1, 6);
cout << roll() << roll() << roll();   // Call like a function
```

**Lab:** [labs/Functor-Summation/](labs/Functor-Summation/) — accumulating functor that keeps a running sum.

---

## 27. Smart Pointers — unique_ptr

**Concept:** `unique_ptr<T>` manages a heap object with **exclusive ownership**. The object is automatically deleted when the `unique_ptr` is destroyed (goes out of scope). Ownership can be **transferred** with `std::move()` but not copied.

**Lab:** [labs/SmartUniquePointer/](labs/SmartUniquePointer/)
```cpp
{
    unique_ptr<Date> p1(new Date(2001, 1, 1));
    unique_ptr<Date> p2 = std::move(p1);    // Transfer: p1 is now null
    if (p1 == nullptr) cout << "p1 is null\n";
    cout << *p2 << endl;
}   // p2 goes out of scope → Date is deleted automatically (no memory leak)

// Custom deleter
unique_ptr<Date, function<void(Date*)>> p3(new Date(2020,1,1),
    [](Date *d) { cout << "Deleting\n"; delete d; });
```

**Use when:** Object has one owner. Eliminates `delete`.

---

## 28. Smart Pointers — shared_ptr

**Concept:** `shared_ptr<T>` allows **shared ownership** via reference counting. The object is deleted when the last `shared_ptr` pointing to it is destroyed or reset.

**Lab:** [labs/SmartSharedPointer/](labs/SmartSharedPointer/)
```cpp
shared_ptr<Date> p1(new Date(2001, 1, 1));
shared_ptr<Date> p2(p1);               // Both point to same object; ref count = 2

p1.reset(new Date(2011, 11, 11));      // p1 now points to new object; old object ref count → 1
// p2 still holds (2001, 1, 1)
p2.reset();                            // ref count → 0 → Date(2001) is deleted

// Make from scratch (preferred):
auto p3 = make_shared<Date>(2022, 6, 1);
```

**unique_ptr vs shared_ptr:**
| | `unique_ptr` | `shared_ptr` |
|---|---|---|
| Owners | 1 | Many |
| Overhead | Zero | Ref count |
| Copyable | No (move only) | Yes |

---

## 29. Move Semantics

**Concept:** Moving transfers ownership of resources (heap memory, file handles) from one object to another **without copying**. Much cheaper than deep copy for large objects. After a move, the source is in a valid but unspecified ("moved-from") state.

**Lab:** [labs/MoveSemantics-1/](labs/MoveSemantics-1/)
```cpp
Message msg1("Hello");
Message msg2("World");

msg2 = msg1;             // COPY: msg1 and msg2 each have their own data
msg2 = std::move(msg1);  // MOVE: msg2 takes msg1's data; msg1 is now empty

vector<Message> v;
v.push_back(std::move(msg2));  // Move msg2 into vector (avoids copy)
```

**Lab:** [labs/MoveSemantics-2/](labs/MoveSemantics-2/) — move semantics with `shared_ptr`.

**Rule of Five:** If you define any of destructor / copy constructor / copy assignment / move constructor / move assignment, you should define all five.

---

## QUICK REFERENCE — Design Patterns

| Pattern | Category | Key idea | Lab |
|---------|----------|----------|-----|
| Template Method | Behavioral | Fixed algorithm skeleton; subclasses fill steps | Program8.2 |
| Strategy | Behavioral | Swap algorithms at runtime via composition | Program8.4 |
| Factory Method | Creational | Subclass decides which class to instantiate | Program9.2 |
| Abstract Factory | Creational | Creates families of related objects | Program9.3 |
| Adapter | Structural | Converts incompatible interface | Program10.2 |
| Facade | Structural | Simplifies complex subsystem | Program10.5 |
| Iterator | Behavioral | Uniform traversal of any collection | Program11.2 |
| Visitor | Behavioral | Add operations without modifying classes | Program11.4 |
| Observer | Behavioral | Notify dependents on state change | Program12.2 |
| State | Behavioral | Object changes behavior based on state | Program13.2 |
| Singleton | Creational | One instance, global access | Program14.1 |
| Composite | Structural | Tree of uniform leaf/group objects | Program14.4 |
| Decorator | Structural | Add responsibilities dynamically by wrapping | Program14.6 |

---

## QUICK REFERENCE — OOP Principles

| Principle | Violation Sign | Fix |
|-----------|---------------|-----|
| SRP | Class has >1 reason to change | Extract class |
| OCP | Adding feature requires editing existing class | Use abstract interface; add subclass |
| Law of Demeter | `a.getB().getC().doThing()` chains | Delegate: `a.doThing()` |

---

## QUICK REFERENCE — Threading

| Scenario | Tool |
|----------|------|
| Protect critical section | `mutex` + `lock_guard` |
| RAII unlock | `lock_guard<mutex>` |
| Multiple concurrent readers | `shared_mutex` + `shared_lock` |
| Exclusive write | `shared_mutex` + `unique_lock` |
| Voluntary CPU release | `this_thread::yield()` |
| Shared ownership + thread-safe | `atomic<T>` |
| Notify waiting thread | `condition_variable` |

---

*Good luck Wednesday!*
