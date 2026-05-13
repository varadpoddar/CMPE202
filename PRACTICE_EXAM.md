# CMPE 202 — Practice Exam
**Exam: Wednesday May 13, 2026 at 5:30 PM**
**Format: 5 Short Answer + 35 Multiple Choice**

---

## PART A — Short Answer (5 Questions)

---

**SA-1.** The following code has a threading problem. Identify the problem, explain why it occurs, and rewrite the `print()` function to fix it using best practices.

```cpp
#include <iostream>
#include <thread>
using namespace std;

void print(string text) {
    for (const char& ch : text)
        cout << ch;
}

int main() {
    thread t1(print, "Hello, world!\n");
    thread t2(print, "Use good design!\n");
    thread t3(print, "Go multithreaded!\n");
    t1.join(); t2.join(); t3.join();
}
```

**Answer:**
> **Problem:** Race condition on `cout`. Three threads write to shared standard output simultaneously with no synchronization. The CPU scheduler can interrupt any thread mid-character, causing garbled interleaved output (e.g., `HGelUlo,se  gwoorld!od`).
>
> **Fixed version using `lock_guard` (RAII — preferred):**
> ```cpp
> #include <mutex>
> mutex print_mutex;
>
> void print(string text) {
>     lock_guard<mutex> guard(print_mutex);  // Acquired here
>     for (const char& ch : text)
>         cout << ch;
> }   // Automatically released when guard goes out of scope
> ```
> `lock_guard` is preferred over manual `lock()`/`unlock()` because it is exception-safe — the mutex is always released even if an exception is thrown inside the critical section.

---

**SA-2.** Explain the difference between the **Factory Method** pattern and the **Abstract Factory** pattern. Give a one-sentence real-world analogy for each and describe when you would choose one over the other.

**Answer:**
> **Factory Method** defines a single virtual method in a base class that subclasses override to create one type of product. The *creator* class defers instantiation to its subclass.
> *Analogy:* A generic `AthleticsDept` that declares `create_sport()` — `VarsityDept` overrides it to create varsity sports, `IntramuralDept` overrides it to create intramural sports. (Program9.2)
>
> **Abstract Factory** provides an interface with *multiple* factory methods — one per product in a related family. The whole factory is swapped as a unit.
> *Analogy:* A `ProvisionsFactory` that creates both `PlayerStrategy` and `VenueStrategy` together — `VarsityFactory` creates varsity players + stadium, `IntramuralFactory` creates intramural players + gym. Swapping the factory changes the entire product family. (Program9.3)
>
> **Choose Factory Method** when you have one product that varies by subclass.
> **Choose Abstract Factory** when you have a *family* of related products that must be used together and you need to swap the whole family at once.

---

**SA-3.** Consider the following two implementations. Identify which design principle is violated in version A, explain why it is a violation, and explain how version B fixes it.

**Version A:**
```cpp
class Employee {
public:
    Date *get_birthdate() const { return birthdate; }
private:
    Date *birthdate;
};

// Elsewhere in the code:
employee.get_birthdate()->set_year(1990);
```

**Version B:**
```cpp
class Employee {
public:
    Date *get_birthdate() const { return new Date(*birthdate); }
private:
    Date *birthdate;
};
```

**Answer:**
> **Violation:** Law of Demeter (also called "Principle of Least Knowledge").
>
> **Why Version A violates it:** `get_birthdate()` returns a raw pointer to the internal `Date` object. External code can then call `->set_year()` on that pointer, effectively **reaching inside** `Employee`'s private data and mutating it from outside. The caller is "talking to a stranger" — `Date` — rather than talking only to `Employee`. This tightly couples the caller to `Employee`'s internal representation. If `Employee` ever changes how it stores birthdate (e.g., as a different type), all external callers break.
>
> **How Version B fixes it:** Returns `new Date(*birthdate)` — a **deep copy**. External code gets a copy it can inspect or modify freely, but changes to the copy do not affect the original `Employee` object. `Employee`'s internal state is fully encapsulated.

---

**SA-4.** Explain the Decorator pattern. Using the ticket example from the labs (Program14.6), show how you would create a ticket with base price, VIP seating, and 2 drink coupons using the Decorator pattern. Compare this to the boolean-flag approach (Program14.5) and state one advantage of each.

**Answer:**
> **Decorator pattern:** Wraps an existing object with another object that adds behavior. Each decorator implements the same interface as the wrapped object, delegates to it, and adds its own cost/behavior. Decorators are chained at runtime.
>
> **Creating the ticket:**
> ```cpp
> Ticket *t = new BaseTicket();    // $50 base
> t = new VIP(t);                  // Wraps base, adds $30
> t = new Coupon(t, 2);            // Wraps VIP+base, adds 2×$5
> cout << t->get_cost();           // $50 + $30 + $10 = $90
> ```
>
> Each `get_cost()` call delegates: `Coupon::get_cost()` → calls `VIP::get_cost()` → calls `BaseTicket::get_cost()`.
>
> **Advantage of Decorator:** Open-Closed — adding a new enhancement (e.g., `ParkingPass`) requires zero changes to existing classes. Combinations are unlimited without combinatorial subclass explosion.
>
> **Advantage of boolean-flag approach:** Simpler to understand at a glance; no object chain to trace; adequate when the set of enhancements is fixed and small.

---

**SA-5.** Write a recursive function `int sum(vector<int> v)` that returns the sum of all elements. Clearly label the base case and recursive case. Then write the equivalent iterative version and explain one trade-off between the two approaches.

**Answer:**
> ```cpp
> // Recursive
> int sum(vector<int> v) {
>     if (v.empty()) return 0;                 // Base case
>     int first = v[0];
>     v.erase(v.begin());
>     return first + sum(v);                   // Recursive case
> }
>
> // Iterative
> int sum(vector<int> v) {
>     int total = 0;
>     for (int x : v) total += x;
>     return total;
> }
> ```
>
> **Trade-off:** The recursive version is elegant and maps directly to the mathematical definition, but each call adds a stack frame — O(n) stack space. For a 10,000-element vector it risks stack overflow. The iterative version uses O(1) space and is faster in practice. However, for inherently recursive problems like tree traversal or backtracking, recursion is clearer and the iterative equivalent becomes complex and error-prone.

---

## PART B — Multiple Choice (35 Questions)

*Circle the single best answer.*

---

**1.** What is the **base case** in a recursive algorithm?

- A) The step where the function calls itself  
- B) The simplest input that can be solved without further recursion ✓  
- C) The step that divides the problem in half  
- D) The first call to the function  

---

**2.** In the Tower of Hanoi solution with N disks, how many total moves are required?

- A) N²  
- B) N log N  
- C) 2ᴺ − 1 ✓  
- D) N!  

---

**3.** What distinguishes **backtracking** from ordinary recursion?

- A) Backtracking always finds the optimal solution  
- B) Backtracking uses iteration instead of recursion  
- C) Backtracking undoes a choice when it leads to a dead end ✓  
- D) Backtracking avoids a base case  

---

**4.** In the N-Queens backtracking solution, after placing a queen and recursing deeper, what happens if no valid placement exists in the next column?

- A) The program terminates with an error  
- B) The queen is left in place and a new row is tried in the next column  
- C) `occupied[row][col]` is set to `false` and the next row is tried in the same column ✓  
- D) The board is reset to its initial state  

---

**5.** What output problem does `Program16.1-Printing-unprotected` demonstrate?

- A) Deadlock between threads  
- B) A race condition causing garbled interleaved output ✓  
- C) Stack overflow from too many threads  
- D) Incorrect join order  

---

**6.** Which synchronization object should you prefer over `mutex::lock()` / `mutex::unlock()` and why?

- A) `atomic<bool>`, because it avoids locking entirely  
- B) `lock_guard<mutex>`, because it is exception-safe via RAII ✓  
- C) `shared_mutex`, because it allows multiple writers  
- D) `condition_variable`, because it is faster  

---

**7.** After the following code executes, what is the state of `p1`?

```cpp
unique_ptr<Date> p1(new Date(2001, 1, 1));
unique_ptr<Date> p2 = std::move(p1);
```

- A) `p1` and `p2` both point to the same `Date` object  
- B) `p1` is unchanged; `p2` is a deep copy  
- C) `p1` is `nullptr`; `p2` owns the `Date` object ✓  
- D) Both pointers are `nullptr`  

---

**8.** What is `this_thread::yield()` used for?

- A) Terminates the current thread  
- B) Locks a mutex for the current thread  
- C) Voluntarily releases the CPU so other threads can run ✓  
- D) Waits for a condition variable to be signaled  

---

**9.** In the Reader-Writer pattern using `shared_mutex`, which lock type should a **writer** use?

- A) `shared_lock<shared_mutex>` — allows concurrent access  
- B) `lock_guard<mutex>` — plain mutex  
- C) `unique_lock<shared_mutex>` — exclusive access ✓  
- D) `atomic<int>` — no lock needed  

---

**10.** Which of the following is NOT one of the four conditions required for deadlock?

- A) Mutual exclusion  
- B) Hold and wait  
- C) Circular wait  
- D) Thread yielding ✓  

---

**11.** The **Single Responsibility Principle** states that:

- A) A class should have only one public method  
- B) A class should have only one reason to change ✓  
- C) A class should inherit from only one base class  
- D) A class should use only one design pattern  

---

**12.** In the Books example (Programs 2.1–2.5), which responsibility was incorrectly placed inside `Catalogue` in version 2.1?

- A) Storing books in a list  
- B) Adding books to the collection  
- C) Case-insensitive string comparison logic ✓  
- D) Printing the catalogue  

---

**13.** The **Open-Closed Principle** means software entities should be:

- A) Open to modification, closed to extension  
- B) Open to extension, closed to modification ✓  
- C) Open to inheritance, closed to composition  
- D) Open to refactoring, closed to new features  

---

**14.** In Program4.4, `MotorVehicleInterface` uses pure virtual methods. Adding a new vehicle type `Motorcycle` requires:

- A) Modifying `MotorVehicleInterface`  
- B) Modifying existing `Car` and `Truck` classes  
- C) Creating a new class `Motorcycle` that implements the interface ✓  
- D) Adding a new `switch` case to all existing methods  

---

**15.** Which of the following violates the **Law of Demeter**?

- A) `engine.replace_sparkplug();`  
- B) `employee.get_salary();`  
- C) `car.get_engine().get_sparkplug()->replace();` ✓  
- D) `report.print();`  

---

**16.** Returning `new Date(*birthdate)` instead of `birthdate` from a getter fixes the Law of Demeter violation because:

- A) It prevents the object from being garbage collected  
- B) It returns a copy, so external code cannot mutate the internal state ✓  
- C) It makes the method faster  
- D) It prevents memory leaks  

---

**17.** The **Template Method** pattern uses:

- A) Composition — a base class holds a reference to a strategy object  
- B) Inheritance — a base class defines the algorithm skeleton; subclasses fill in abstract steps ✓  
- C) A static factory method to create algorithm objects  
- D) A visitor to perform operations on nodes  

---

**18.** In `GameReport::generate_report()`, the methods `print_header()` and `print_footer()` are **concrete** (not abstract) because:

- A) They are too complex to override  
- B) Subclasses are not allowed to override them  
- C) They are the same for all report types — only the data steps vary ✓  
- D) They must be called before and after every abstract method  

---

**19.** The key difference between the **Strategy** and **Template Method** patterns is:

- A) Template Method uses interfaces; Strategy uses abstract classes  
- B) Strategy changes behavior via composition at runtime; Template Method fixes the skeleton via inheritance ✓  
- C) Strategy cannot be changed at runtime; Template Method can  
- D) There is no meaningful difference  

---

**20.** In `Sport` (Program8.4), calling `set_player_strategy(new DraftStrategy())` at runtime is an example of:

- A) The Observer pattern — notifying observers  
- B) The Decorator pattern — adding responsibility dynamically  
- C) The Strategy pattern — swapping algorithms at runtime ✓  
- D) The State pattern — transitioning to a new state  

---

**21.** What is the role of `create_sport()` in `AthleticsDept` (Program9.2)?

- A) It is a concrete method that creates all sport types  
- B) It is a pure virtual factory method that subclasses override to create the appropriate sport ✓  
- C) It is a static factory that uses a switch statement  
- D) It is an observer that is notified when a sport is created  

---

**22.** An **Abstract Factory** differs from a **Factory Method** primarily because:

- A) Abstract Factory creates only one product type  
- B) Abstract Factory creates a *family* of related products through multiple factory methods ✓  
- C) Factory Method uses composition; Abstract Factory uses inheritance  
- D) Abstract Factory always returns the same object (Singleton)  

---

**23.** The **Adapter** pattern is best described as:

- A) Simplifying a complex subsystem behind a single interface  
- B) Wrapping an incompatible interface so it matches the expected interface ✓  
- C) Defining a skeleton algorithm in a base class  
- D) Observing state changes in a subject  

---

**24.** In Program10.2, `ConvertedData` is an inner class that inherits from `AttendanceData`. What role does it play?

- A) Subject — it notifies observers when attendance changes  
- B) Composite — it groups multiple attendance records  
- C) Adapter — it converts `FootballInfo`/`VolleyballStats` to the `AttendanceData` interface ✓  
- D) Decorator — it adds new attendance fields dynamically  

---

**25.** The **Facade** pattern is most appropriate when:

- A) You need a single instance of a class  
- B) You want to add behavior to an object at runtime  
- C) You want to provide a simple interface to a complex set of subsystem classes ✓  
- D) You need to traverse elements of a collection uniformly  

---

**26.** The **Iterator** pattern allows clients to traverse different collection types (array, vector, map) without knowing the underlying type because:

- A) All collections inherit from a common base class  
- B) All iterators implement the same `has_next()` / `next()` interface ✓  
- C) The factory method creates the correct iterator automatically  
- D) The observer pattern notifies the client of each element  

---

**27.** In the **Visitor** pattern, `Node::accept(Visitor& v)` typically calls:

- A) `v.visit_all()`  
- B) `v.notify(this)`  
- C) The appropriate `v.visit_X(this)` method for the node's concrete type ✓  
- D) `v.update(this)`  

---

**28.** When would you use the **Visitor** pattern over just adding a new method to each class?

- A) When the object hierarchy changes frequently but operations are stable  
- B) When the object hierarchy is stable but new operations are added frequently ✓  
- C) When you need to create objects from a factory  
- D) When you need to observe state changes  

---

**29.** In the **Observer** pattern, what does `Subject::notify()` do?

- A) Registers a new observer  
- B) Removes an observer from the list  
- C) Calls `update()` on every registered observer ✓  
- D) Updates its own internal state  

---

**30.** The **State** pattern replaces `switch (state) { ... }` in every method with:

- A) A map from state enum to function pointer  
- B) A visitor that handles each state  
- C) Concrete state objects, each implementing the correct behavior for that state ✓  
- D) A singleton that manages state transitions  

---

**31.** In Program13.2, calling `current = current->insert_credit_card()` returns a new `State*`. What does this represent?

- A) A new `TicketMachine` object  
- B) A transition to the next state ✓  
- C) A copy of the current state  
- D) The result of the transaction  

---

**32.** The **Singleton** pattern ensures:

- A) An object is created exactly once and has no public methods  
- B) A class has exactly one instance and provides a global access point to it ✓  
- C) All instances of a class share the same state  
- D) A class cannot be instantiated at all  

---

**33.** In the **Composite** pattern, calling `get_cost()` on a `ProvisionGroup` works because:

- A) It returns a hardcoded sum of all known item types  
- B) It iterates over its children and recursively calls `get_cost()` on each ✓  
- C) It uses a visitor to accumulate costs  
- D) It uses a template method defined in the base class  

---

**34.** What is the key structural difference between the **Decorator** and **Composite** patterns?

- A) Decorator is behavioral; Composite is creational  
- B) Composite assembles a tree for part-whole hierarchy; Decorator wraps a single object to add behavior ✓  
- C) Decorator creates families of objects; Composite creates one  
- D) There is no structural difference  

---

**35.** What does the following lambda expression do?

```cpp
auto result = select(people,
    [](const Person& p) -> bool { return p.last[0] == 'S'; });
```

- A) Selects all people whose first name starts with 'S'  
- B) Selects all people whose last name starts with 'S' ✓  
- C) Sorts people alphabetically by last name  
- D) Counts the number of people with last name starting with 'S'  

---

## ANSWER KEY

### Short Answer — Key Points Checklist

| Q | Must Include |
|---|---|
| SA-1 | "race condition" + "mutex" or "lock_guard" + exception-safety explanation |
| SA-2 | Factory Method = one product + subclass overrides; Abstract Factory = family of products; when to use each |
| SA-3 | "Law of Demeter" + "returns pointer to internal state" + "returns copy" fixes it |
| SA-4 | Chain of wrappers each calling `get_cost()` on wrapped object + comparison to flag approach |
| SA-5 | Base case (empty vector) + recursive case + stack space trade-off |

### MCQ Answer Key

| # | Answer | # | Answer | # | Answer | # | Answer | # | Answer |
|---|--------|---|--------|---|--------|---|--------|---|--------|
| 1 | B | 8 | C | 15 | C | 22 | B | 29 | C |
| 2 | C | 9 | C | 16 | B | 23 | B | 30 | C |
| 3 | C | 10 | D | 17 | B | 24 | C | 31 | B |
| 4 | C | 11 | B | 18 | C | 25 | C | 32 | B |
| 5 | B | 12 | C | 19 | B | 26 | B | 33 | B |
| 6 | B | 13 | B | 20 | C | 27 | C | 34 | B |
| 7 | C | 14 | C | 21 | B | 28 | B | 35 | B |

---

*Cross-reference each question with [STUDY_GUIDE.md](STUDY_GUIDE.md) for full concept review.*
