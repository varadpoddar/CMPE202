# CMPE 202 — Practice Exam 2
## Coding Short Answers + Extended MCQ Bank
**Exam: Wednesday May 13, 2026 at 5:30 PM**
**Short answers are on an online C++ compiler — your code must compile and run correctly.**

---

## PART A — Coding Short Answer (15 Questions)

Each question gives you a problem. Write complete, compilable C++ code in the online editor.
Starter `#include` headers are listed where needed.

---

### SA-C1. Recursive Reverse String

Write a recursive function `string reverse_str(string s)` that returns the string reversed.
- Do **not** use any loop.
- Must work for empty string.

**Expected output for `reverse_str("hello")`:** `"olleh"`

**Solution:**
```cpp
#include <iostream>
#include <string>
using namespace std;

string reverse_str(string s) {
    if (s.empty()) return "";                          // base case
    return reverse_str(s.substr(1)) + s[0];           // recursive case
}

int main() {
    cout << reverse_str("hello") << endl;   // olleh
    cout << reverse_str("CMPE202") << endl; // 202EPMC
    cout << reverse_str("") << endl;        // (empty)
}
```

---

### SA-C2. Recursive Power

Write `double power(double base, int exp)` recursively.
- Handle `exp == 0` (base case).
- Handle negative exponents: `power(2, -3)` = `1/8`.
- Do **not** use `<cmath>`.

**Expected:** `power(2, 10)` = `1024`, `power(2, -2)` = `0.25`

**Solution:**
```cpp
#include <iostream>
using namespace std;

double power(double base, int exp) {
    if (exp == 0)  return 1.0;
    if (exp < 0)   return 1.0 / power(base, -exp);
    return base * power(base, exp - 1);
}

int main() {
    cout << power(2, 10)  << endl;   // 1024
    cout << power(2, -2)  << endl;   // 0.25
    cout << power(3, 4)   << endl;   // 81
}
```

---

### SA-C3. Backtracking — Subset Sum

Write a recursive function that prints **all subsets** of a `vector<int>` that sum to a given target.

```cpp
// starter:
#include <iostream>
#include <vector>
using namespace std;
void find_subsets(vector<int>& nums, int target, vector<int>& current, int index);
```

**Example:** `nums = {1, 2, 3, 4}`, `target = 5` → prints `{1, 4}` and `{2, 3}`

**Solution:**
```cpp
#include <iostream>
#include <vector>
using namespace std;

void print_subset(const vector<int>& v) {
    cout << "{ ";
    for (int x : v) cout << x << " ";
    cout << "}" << endl;
}

void find_subsets(vector<int>& nums, int target,
                  vector<int>& current, int index) {
    int sum = 0;
    for (int x : current) sum += x;

    if (sum == target) { print_subset(current); return; }
    if (index >= (int)nums.size() || sum > target) return;

    // Include nums[index]
    current.push_back(nums[index]);
    find_subsets(nums, target, current, index + 1);

    // Exclude nums[index] (backtrack)
    current.pop_back();
    find_subsets(nums, target, current, index + 1);
}

int main() {
    vector<int> nums = {1, 2, 3, 4};
    vector<int> current;
    find_subsets(nums, 5, current, 0);
}
```

---

### SA-C4. Thread-Safe Counter

Two threads each increment a shared counter 100,000 times. Without synchronization the final count is wrong. Write the complete program using `mutex` and `lock_guard` so the final count is always exactly 200,000.

**Solution:**
```cpp
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int counter = 0;
mutex counter_mutex;

void increment(int times) {
    for (int i = 0; i < times; i++) {
        lock_guard<mutex> guard(counter_mutex);
        counter++;
    }
}

int main() {
    thread t1(increment, 100000);
    thread t2(increment, 100000);
    t1.join();
    t2.join();
    cout << "Final count: " << counter << endl;  // Always 200000
}
```

---

### SA-C5. Producer-Consumer (simplified)

Write a program with:
- One producer thread that pushes integers 1–10 into a `queue<int>`.
- One consumer thread that pops and prints each value.
- Use a `mutex` to protect the queue.
- Use `this_thread::yield()` when the queue is empty/full.

**Solution:**
```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
using namespace std;

queue<int> q;
mutex q_mutex;
bool done = false;

void producer() {
    for (int i = 1; i <= 10; i++) {
        while (true) {
            lock_guard<mutex> lk(q_mutex);
            if (q.size() < 5) { q.push(i); break; }
            this_thread::yield();
        }
    }
    lock_guard<mutex> lk(q_mutex);
    done = true;
}

void consumer() {
    while (true) {
        lock_guard<mutex> lk(q_mutex);
        if (!q.empty()) {
            cout << "Consumed: " << q.front() << endl;
            q.pop();
        } else if (done) {
            break;
        } else {
            this_thread::yield();
        }
    }
}

int main() {
    thread prod(producer);
    thread cons(consumer);
    prod.join();
    cons.join();
}
```

---

### SA-C6. Strategy Pattern

Implement the Strategy pattern for a `Sorter` class that can sort a `vector<int>` using either **bubble sort** or **selection sort** as interchangeable strategies.

Requirements:
- `SortStrategy` abstract base class with `virtual void sort(vector<int>&) = 0`
- `BubbleSort` and `SelectionSort` concrete strategies
- `Sorter` class that holds a `SortStrategy*` and has `set_strategy()` and `sort()` methods

**Solution:**
```cpp
#include <iostream>
#include <vector>
using namespace std;

class SortStrategy {
public:
    virtual void sort(vector<int>& v) = 0;
    virtual ~SortStrategy() = default;
};

class BubbleSort : public SortStrategy {
public:
    void sort(vector<int>& v) override {
        for (int i = 0; i < (int)v.size()-1; i++)
            for (int j = 0; j < (int)v.size()-1-i; j++)
                if (v[j] > v[j+1]) swap(v[j], v[j+1]);
    }
};

class SelectionSort : public SortStrategy {
public:
    void sort(vector<int>& v) override {
        for (int i = 0; i < (int)v.size()-1; i++) {
            int min_idx = i;
            for (int j = i+1; j < (int)v.size(); j++)
                if (v[j] < v[min_idx]) min_idx = j;
            swap(v[i], v[min_idx]);
        }
    }
};

class Sorter {
public:
    Sorter(SortStrategy* s) : strategy(s) {}
    void set_strategy(SortStrategy* s) { strategy = s; }
    void sort(vector<int>& v) { strategy->sort(v); }
private:
    SortStrategy* strategy;
};

int main() {
    vector<int> v = {5, 3, 8, 1, 9, 2};

    Sorter sorter(new BubbleSort());
    sorter.sort(v);
    for (int x : v) cout << x << " ";
    cout << endl;  // 1 2 3 5 8 9

    v = {5, 3, 8, 1, 9, 2};
    sorter.set_strategy(new SelectionSort());
    sorter.sort(v);
    for (int x : v) cout << x << " ";
    cout << endl;  // 1 2 3 5 8 9
}
```

---

### SA-C7. Observer Pattern

Implement a simple Observer pattern where a `Temperature` subject notifies registered observers whenever the temperature changes. Implement two observers: `Display` (prints current temp) and `Alarm` (prints warning if temp > 100).

**Solution:**
```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Observer {
public:
    virtual void update(double temp) = 0;
    virtual ~Observer() = default;
};

class Subject {
public:
    void attach(Observer* o) { observers.push_back(o); }
    void notify(double temp) {
        for (Observer* o : observers) o->update(temp);
    }
private:
    vector<Observer*> observers;
};

class Temperature : public Subject {
public:
    void set_temperature(double t) {
        temp = t;
        notify(temp);
    }
    double get_temperature() const { return temp; }
private:
    double temp = 0;
};

class Display : public Observer {
public:
    void update(double temp) override {
        cout << "Display: Current temp = " << temp << "°C" << endl;
    }
};

class Alarm : public Observer {
public:
    void update(double temp) override {
        if (temp > 100)
            cout << "ALARM: Temperature exceeded 100°C! (" << temp << ")" << endl;
    }
};

int main() {
    Temperature t;
    Display d;
    Alarm a;
    t.attach(&d);
    t.attach(&a);

    t.set_temperature(25.0);
    t.set_temperature(105.0);
    t.set_temperature(98.6);
}
```

**Expected output:**
```
Display: Current temp = 25°C
Display: Current temp = 105°C
ALARM: Temperature exceeded 100°C! (105)
Display: Current temp = 98.6°C
```

---

### SA-C8. Decorator Pattern

Implement a `TextFormatter` decorator chain:
- `TextComponent` base class with `virtual string get_text() const = 0`
- `PlainText` concrete base that holds a `string`
- `BoldDecorator` — wraps text in `**...**`
- `UpperCaseDecorator` — converts text to uppercase
- Decorators can be chained in any order

**Solution:**
```cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class TextComponent {
public:
    virtual string get_text() const = 0;
    virtual ~TextComponent() = default;
};

class PlainText : public TextComponent {
public:
    PlainText(const string& s) : text(s) {}
    string get_text() const override { return text; }
private:
    string text;
};

class Decorator : public TextComponent {
public:
    Decorator(TextComponent* c) : component(c) {}
protected:
    TextComponent* component;
};

class BoldDecorator : public Decorator {
public:
    BoldDecorator(TextComponent* c) : Decorator(c) {}
    string get_text() const override {
        return "**" + component->get_text() + "**";
    }
};

class UpperCaseDecorator : public Decorator {
public:
    UpperCaseDecorator(TextComponent* c) : Decorator(c) {}
    string get_text() const override {
        string s = component->get_text();
        transform(s.begin(), s.end(), s.begin(), ::toupper);
        return s;
    }
};

int main() {
    TextComponent* t = new PlainText("hello cmpe202");
    t = new BoldDecorator(t);
    t = new UpperCaseDecorator(t);
    cout << t->get_text() << endl;   // **HELLO CMPE202**

    TextComponent* t2 = new PlainText("design patterns");
    t2 = new UpperCaseDecorator(t2);
    t2 = new BoldDecorator(t2);
    cout << t2->get_text() << endl;  // **DESIGN PATTERNS**
}
```

---

### SA-C9. Factory Method Pattern

Implement a `ShapeFactory` with a static `make(string type)` method that creates:
- `Circle` — `area()` returns `π * r²` (use `r = 5`)
- `Rectangle` — `area()` returns `w * h` (use `w=4, h=6`)
- `Triangle` — `area()` returns `0.5 * b * h` (use `b=3, h=8`)

All shapes inherit from abstract `Shape` with `virtual double area() const = 0` and `virtual string name() const = 0`.

**Solution:**
```cpp
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Shape {
public:
    virtual double area()   const = 0;
    virtual string name()   const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
    double area()   const override { return M_PI * 5 * 5; }
    string name()   const override { return "Circle"; }
};
class Rectangle : public Shape {
    double area()   const override { return 4 * 6; }
    string name()   const override { return "Rectangle"; }
};
class Triangle : public Shape {
    double area()   const override { return 0.5 * 3 * 8; }
    string name()   const override { return "Triangle"; }
};

class ShapeFactory {
public:
    static Shape* make(const string& type) {
        if (type == "circle")    return new Circle();
        if (type == "rectangle") return new Rectangle();
        if (type == "triangle")  return new Triangle();
        return nullptr;
    }
};

int main() {
    for (const string& type : {"circle", "rectangle", "triangle"}) {
        Shape* s = ShapeFactory::make(type);
        cout << s->name() << " area = " << s->area() << endl;
        delete s;
    }
}
```

---

### SA-C10. Composite Pattern — File System

Implement a simple file system using the Composite pattern:
- `FileSystemNode` base class with `virtual long size() const = 0` and `virtual void print(int indent) const = 0`
- `File` — leaf node, holds a name and size
- `Directory` — composite, holds `vector<FileSystemNode*>`, `size()` returns sum of children

**Solution:**
```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class FileSystemNode {
public:
    virtual long size()               const = 0;
    virtual void print(int indent = 0) const = 0;
    virtual ~FileSystemNode() = default;
};

class File : public FileSystemNode {
public:
    File(const string& n, long s) : name(n), bytes(s) {}
    long size()                const override { return bytes; }
    void print(int indent = 0) const override {
        cout << string(indent, ' ') << name << " (" << bytes << " bytes)" << endl;
    }
private:
    string name;
    long bytes;
};

class Directory : public FileSystemNode {
public:
    Directory(const string& n) : name(n) {}
    void add(FileSystemNode* node) { children.push_back(node); }
    long size() const override {
        long total = 0;
        for (auto* c : children) total += c->size();
        return total;
    }
    void print(int indent = 0) const override {
        cout << string(indent, ' ') << "[" << name << "] (" << size() << " bytes)" << endl;
        for (auto* c : children) c->print(indent + 2);
    }
private:
    string name;
    vector<FileSystemNode*> children;
};

int main() {
    Directory* root = new Directory("root");
    root->add(new File("readme.txt", 1024));

    Directory* src = new Directory("src");
    src->add(new File("main.cpp", 2048));
    src->add(new File("helper.cpp", 512));
    root->add(src);

    root->print();
    cout << "Total: " << root->size() << " bytes" << endl;
}
```

**Expected output:**
```
[root] (3584 bytes)
  readme.txt (1024 bytes)
  [src] (2560 bytes)
    main.cpp (2048 bytes)
    helper.cpp (512 bytes)
Total: 3584 bytes
```

---

### SA-C11. State Pattern — Traffic Light

Implement a traffic light state machine using the State pattern:
- States: `Red`, `Green`, `Yellow`
- `Red::next()` → `Green`
- `Green::next()` → `Yellow`
- `Yellow::next()` → `Red`
- `TrafficLight` holds current state and calls `next()` to advance

**Solution:**
```cpp
#include <iostream>
#include <string>
using namespace std;

class TrafficLight;  // forward declaration

class LightState {
public:
    virtual string color()            const = 0;
    virtual LightState* next()              = 0;
    virtual ~LightState() = default;
};

class Red;
class Green;
class Yellow;

class Red : public LightState {
public:
    string color() const override { return "RED — Stop"; }
    LightState* next() override;   // defined after Green
};
class Green : public LightState {
public:
    string color() const override { return "GREEN — Go"; }
    LightState* next() override { return new Yellow(); }
};
class Yellow : public LightState {
public:
    string color() const override { return "YELLOW — Caution"; }
    LightState* next() override { return new Red(); }
};

LightState* Red::next() { return new Green(); }

class TrafficLight {
public:
    TrafficLight() : state(new Red()) {}
    void advance() {
        LightState* next = state->next();
        delete state;
        state = next;
    }
    void show() const { cout << state->color() << endl; }
private:
    LightState* state;
};

int main() {
    TrafficLight light;
    for (int i = 0; i < 6; i++) {
        light.show();
        light.advance();
    }
}
```

---

### SA-C12. Lambda + STL

Given a `vector<string> words`, use lambdas with `std::sort`, `std::remove_if`, and `std::for_each` to:
1. Remove all words shorter than 4 characters.
2. Sort the remaining words alphabetically.
3. Print each word with its length.

**Solution:**
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    vector<string> words = {"hi", "design", "OOP", "pattern", "go", "lambda", "law"};

    // Remove words shorter than 4 chars
    words.erase(
        remove_if(words.begin(), words.end(),
            [](const string& s) { return s.size() < 4; }),
        words.end()
    );

    // Sort alphabetically
    sort(words.begin(), words.end(),
        [](const string& a, const string& b) { return a < b; });

    // Print each with its length
    for_each(words.begin(), words.end(),
        [](const string& s) {
            cout << s << " (length=" << s.size() << ")" << endl;
        });
}
```

**Expected output:**
```
design (length=6)
lambda (length=6)
pattern (length=7)
```

---

### SA-C13. unique_ptr Chain

Write a program that:
1. Creates a `unique_ptr<string>` with value `"original"`.
2. Transfers ownership to a second `unique_ptr` using `std::move`.
3. Verifies the first pointer is now `nullptr`.
4. Creates a `unique_ptr` with a custom deleter that prints `"Deleting: "` + the string value before deletion.

**Solution:**
```cpp
#include <iostream>
#include <memory>
#include <string>
#include <functional>
using namespace std;

int main() {
    // Step 1: create
    unique_ptr<string> p1 = make_unique<string>("original");
    cout << "p1: " << *p1 << endl;

    // Step 2: transfer ownership
    unique_ptr<string> p2 = move(p1);
    cout << "p2: " << *p2 << endl;

    // Step 3: verify p1 is null
    if (p1 == nullptr)
        cout << "p1 is now nullptr" << endl;

    // Step 4: custom deleter
    auto deleter = [](string* s) {
        cout << "Deleting: " << *s << endl;
        delete s;
    };
    unique_ptr<string, function<void(string*)>> p3(new string("custom"), deleter);
    cout << "p3: " << *p3 << endl;
    // p3 goes out of scope here → custom deleter fires
}
```

**Expected output:**
```
p1: original
p2: original
p1 is now nullptr
p3: custom
Deleting: custom
```

---

### SA-C14. Template Method — Report Generator

Implement the Template Method pattern for two report types: `SalesReport` and `InventoryReport`.
- Base class `Report` defines the template method `generate()` that calls: `header()` → `body()` → `footer()`.
- `header()` and `footer()` are concrete in the base class.
- `body()` is pure virtual.

**Solution:**
```cpp
#include <iostream>
#include <string>
using namespace std;

class Report {
public:
    void generate() {       // Template method — fixed sequence
        header();
        body();             // Subclass fills this in
        footer();
    }
protected:
    void header() const { cout << "=== " << title() << " ===" << endl; }
    void footer() const { cout << "=== End of Report ===" << endl << endl; }
    virtual void body()         const = 0;
    virtual string title()      const = 0;
};

class SalesReport : public Report {
    string title() const override { return "Sales Report"; }
    void body()    const override {
        cout << "Q1: $120,000" << endl;
        cout << "Q2: $145,000" << endl;
        cout << "Q3: $132,000" << endl;
    }
};

class InventoryReport : public Report {
    string title() const override { return "Inventory Report"; }
    void body()    const override {
        cout << "Widgets in stock: 4,200" << endl;
        cout << "Gadgets in stock: 1,850" << endl;
    }
};

int main() {
    SalesReport    sr;
    InventoryReport ir;
    sr.generate();
    ir.generate();
}
```

---

### SA-C15. Adapter Pattern

You have a legacy `CelsiusThermometer` class that only returns temperature in Celsius. Write an `Adapter` so it can be used through a `Thermometer` interface that requires `get_fahrenheit()`.

**Solution:**
```cpp
#include <iostream>
using namespace std;

// Existing interface expected by client
class Thermometer {
public:
    virtual double get_fahrenheit() const = 0;
    virtual ~Thermometer() = default;
};

// Legacy class — cannot be modified
class CelsiusThermometer {
public:
    CelsiusThermometer(double c) : celsius(c) {}
    double get_celsius() const { return celsius; }
private:
    double celsius;
};

// Adapter: makes CelsiusThermometer look like Thermometer
class CelsiusAdapter : public Thermometer {
public:
    CelsiusAdapter(CelsiusThermometer* t) : thermometer(t) {}
    double get_fahrenheit() const override {
        return thermometer->get_celsius() * 9.0 / 5.0 + 32.0;
    }
private:
    CelsiusThermometer* thermometer;
};

void print_temperature(const Thermometer& t) {
    cout << "Temperature: " << t.get_fahrenheit() << "°F" << endl;
}

int main() {
    CelsiusThermometer legacy(100.0);   // boiling point
    CelsiusAdapter adapter(&legacy);
    print_temperature(adapter);         // 212°F

    CelsiusThermometer body_temp(37.0);
    CelsiusAdapter adapter2(&body_temp);
    print_temperature(adapter2);        // 98.6°F
}
```

---

## PART B — Additional MCQ (50 Questions)

---

**MCQ-1.** What is printed by this code?
```cpp
int f(int n) {
    if (n == 0) return 1;
    return n * f(n - 1);
}
cout << f(5);
```
- A) 25
- B) 60
- C) 120 ✓
- D) Stack overflow

---

**MCQ-2.** Which line causes undefined behavior in this recursive function?
```cpp
int sum(int* arr, int n) {
    if (n == 0) return arr[0];   // ← Line A
    return arr[0] + sum(arr + 1, n - 1);
}
```
- A) The base case is wrong — `n == 0` should be `n < 0`
- B) Line A accesses `arr[0]` when `n == 0`, which is after the last element ✓
- C) The recursion never terminates
- D) `arr + 1` does not advance the pointer correctly

---

**MCQ-3.** The correct base case for a recursive function that counts nodes in a linked list is:
- A) `if (node == nullptr) return -1;`
- B) `if (node->next == nullptr) return 1;`
- C) `if (node == nullptr) return 0;` ✓
- D) `if (node != nullptr) return 1;`

---

**MCQ-4.** Tower of Hanoi with 4 disks requires how many moves?
- A) 8
- B) 12
- C) 15 ✓
- D) 16

---

**MCQ-5.** In the Quicksort recursion `sort(left, pivot-1)` and `sort(pivot+1, right)`, the base case triggers when:
- A) `left == 0 && right == 0`
- B) The partition size is less than 2 (0 or 1 element) ✓
- C) `pivot == left`
- D) The array is already sorted

---

**MCQ-6.** In the Sudoku backtracking solver, when `is_number_ok()` returns `false` for all numbers 1–9 in a cell, the function:
- A) Skips the cell and moves to the next
- B) Sets the cell to 0 and returns `false` to trigger backtracking ✓
- C) Throws an exception
- D) Resets the entire grid

---

**MCQ-7.** What does `t1.join()` do?
- A) Creates thread `t1`
- B) Sends data to thread `t1`
- C) Blocks the calling thread until `t1` finishes ✓
- D) Terminates thread `t1` immediately

---

**MCQ-8.** If you forget to call `join()` on a thread and it goes out of scope, the program:
- A) Silently continues without the thread
- B) Calls `terminate()` and crashes ✓
- C) Automatically detaches the thread
- D) Waits indefinitely for the thread

---

**MCQ-9.** Which of the following correctly creates a thread that calls `void foo(int x)` with argument `42`?
- A) `thread t = foo(42);`
- B) `thread t(foo, 42);` ✓
- C) `thread t(&foo(42));`
- D) `thread t = thread::create(foo, 42);`

---

**MCQ-10.** `lock_guard` provides exception safety because:
- A) It catches exceptions and retries the lock
- B) Its destructor always releases the mutex, even if an exception is thrown ✓
- C) It prevents exceptions from being thrown in the critical section
- D) It uses `try`/`catch` internally

---

**MCQ-11.** Given `shared_mutex m`, which lock combination allows two reader threads to proceed simultaneously?
- A) Both use `unique_lock<shared_mutex>`
- B) Both use `shared_lock<shared_mutex>` ✓
- C) One uses `shared_lock`, the other uses `unique_lock`
- D) Both use `lock_guard<mutex>`

---

**MCQ-12.** A `condition_variable` is used to:
- A) Prevent two threads from entering a critical section simultaneously
- B) Allow a thread to sleep until another thread signals that a condition is met ✓
- C) Count the number of active threads
- D) Transfer data between threads without a mutex

---

**MCQ-13.** In the Dining Philosophers problem, if all five philosophers simultaneously pick up their left chopstick and wait for their right, this is called:
- A) Livelock
- B) Starvation
- C) Deadlock ✓
- D) Race condition

---

**MCQ-14.** Which class in Program16.3 uses `shared_lock<shared_mutex>`?
- A) The writer (set_meter) — needs exclusive access
- B) The reader (log_meter) — allows concurrent reads ✓
- C) Both reader and writer
- D) Neither — they use plain `mutex`

---

**MCQ-15.** Which OOP principle does this violate?
```cpp
class OrderProcessor {
    void process_order() { ... }
    void send_email_confirmation() { ... }
    void generate_invoice_pdf() { ... }
    void update_database() { ... }
};
```
- A) Open-Closed Principle
- B) Law of Demeter
- C) Single Responsibility Principle ✓
- D) Interface Segregation Principle

---

**MCQ-16.** After applying SRP to the class above, how many classes would you likely have?
- A) 1 — SRP only requires one public interface
- B) 2 — one for processing, one for everything else
- C) 4 — one per responsibility ✓
- D) As many as there are methods

---

**MCQ-17.** Which code correctly demonstrates the Open-Closed Principle?
- A) Adding an `if/else` inside `calculate_tax()` for each new country
- B) Each country implements a `TaxCalculator` interface with `calculate()` ✓
- C) Modifying the base class whenever a new country is added
- D) Using a global variable to select which tax calculation to run

---

**MCQ-18.** The Law of Demeter is also known as:
- A) The Principle of Single Responsibility
- B) The Principle of Least Knowledge ✓
- C) The Principle of Interface Segregation
- D) The Principle of Dependency Inversion

---

**MCQ-19.** Which of the following is a Law of Demeter **compliant** replacement for `car.get_engine().get_rpm()`?
- A) `car.get_engine_rpm()` ✓
- B) `Engine& e = car.get_engine(); e.get_rpm();`
- C) Both A and B are compliant
- D) Neither — you must directly access the engine

---

**MCQ-20.** Which design pattern is being used here?
```cpp
void process() {
    open_connection();
    authenticate();      // ← subclass overrides
    fetch_data();        // ← subclass overrides
    close_connection();
}
```
- A) Strategy
- B) Observer
- C) Template Method ✓
- D) Factory Method

---

**MCQ-21.** In the Template Method pattern, the invariant steps in the base class are typically:
- A) Pure virtual
- B) Private and non-virtual
- C) Concrete (non-virtual) implementations ✓
- D) Static methods

---

**MCQ-22.** What is the **primary benefit** of the Strategy pattern?
- A) Reduces the number of classes
- B) Allows algorithms to be selected and swapped at runtime without modifying the host class ✓
- C) Guarantees the same algorithm is always used
- D) Eliminates the need for inheritance

---

**MCQ-23.** In `Sport::set_player_strategy(PlayerStrategy* ps)`, what pattern enables this?
- A) Observer — observers can be swapped
- B) Template Method — the template can be changed
- C) Strategy — strategies can be replaced at runtime ✓
- D) Decorator — behavior is wrapped dynamically

---

**MCQ-24.** A `ToyFactory::make(Kind::CAR)` hides which class name from the caller?
- A) `Kind`
- B) `Toy`
- C) `ToyCar` ✓
- D) `ToyFactory`

---

**MCQ-25.** Which statement correctly describes the Factory Method pattern's structure?
- A) A static method returns one of many concrete product types based on input ✓
- B) A base class defines factory methods; each subclass creates a full product family
- C) A single class creates all products with `new`
- D) Products are created by visitors

---

**MCQ-26.** In `Program9.3`, `VarsityFactory::make_venue()` returns `new Stadium()`. If you swap the factory to `IntramuralFactory`, `make_venue()` returns `new Gym()`. This demonstrates:
- A) The products can be swapped independently
- B) The entire product family is replaced as a unit ✓
- C) The factory method delegates to a strategy
- D) The Decorator pattern wrapping the venue

---

**MCQ-27.** The Adapter pattern is **structurally similar** to which other pattern?
- A) Observer
- B) Decorator ✓ (both wrap an object; Adapter changes interface, Decorator adds behavior)
- C) Singleton
- D) Composite

---

**MCQ-28.** In `Program10.2`, `ConvertedData` inherits from `AttendanceData`. This is an example of:
- A) Multiple inheritance to combine two unrelated classes
- B) The Adapter using inheritance to satisfy the expected interface ✓
- C) The Decorator adding cost behavior
- D) The Composite aggregating child nodes

---

**MCQ-29.** The Facade pattern differs from the Adapter pattern in that:
- A) Facade wraps a single object; Adapter wraps multiple objects
- B) Facade simplifies a subsystem interface; Adapter converts one interface to another ✓
- C) Facade is behavioral; Adapter is creational
- D) They are the same pattern with different names

---

**MCQ-30.** Which pattern is most appropriate when you need uniform traversal over an array, a linked list, and a hash map?
- A) Visitor
- B) Strategy
- C) Iterator ✓
- D) Composite

---

**MCQ-31.** In the Iterator pattern, `has_next()` and `next()` are defined in:
- A) The concrete collection class
- B) The abstract `Iterator` base class ✓
- C) The client that uses the iterator
- D) The factory that creates iterators

---

**MCQ-32.** In the Visitor pattern, `Node::accept(Visitor& v)` calls `v.visit_X(this)`. This technique is called:
- A) Single dispatch
- B) Double dispatch ✓ (first dispatch on node type, second on visitor type)
- C) Template method dispatch
- D) Strategy dispatch

---

**MCQ-33.** Which pattern is best for adding a new report type (e.g., `WinningsReport`) to an existing class hierarchy without modifying any node classes?
- A) Observer — attach a new observer
- B) Decorator — wrap nodes with new behavior
- C) Visitor — add a new Visitor subclass ✓
- D) Strategy — swap the reporting algorithm

---

**MCQ-34.** In the Observer pattern, `detach(Observer* o)` is used to:
- A) Delete the observer object
- B) Remove the observer so it no longer receives notifications ✓
- C) Pause notifications to the observer temporarily
- D) Transfer the observer to a different subject

---

**MCQ-35.** The difference between **push** and **pull** Observer models is:
- A) Push: observer calls subject to get data. Pull: subject sends data in `update()`.
- B) Push: subject sends data in `update()`. Pull: observer queries subject after notification. ✓
- C) Push uses `condition_variable`; Pull uses polling
- D) There is no meaningful difference

---

**MCQ-36.** In the State pattern, what handles state transitions?
- A) A central `switch` statement in the context class
- B) Each concrete state returns the next state from its action methods ✓
- C) A factory that creates the next state
- D) An observer that monitors state changes

---

**MCQ-37.** The Singleton's copy constructor and assignment operator should be:
- A) Public to allow copying to other pointers
- B) Protected to allow subclassing
- C) Deleted (or made private) to prevent multiple instances ✓
- D) Virtual to support polymorphism

---

**MCQ-38.** In the Composite pattern, the `add()` method is defined in the base `Component` class and throws by default. Why?
- A) To force subclasses to implement it
- B) So that clients can call `add()` uniformly; leaves throw to indicate they cannot have children ✓
- C) Because C++ requires all virtual methods to have a base implementation
- D) To prevent memory leaks when adding children

---

**MCQ-39.** What is the key structural identifier of the Decorator pattern?
- A) The decorator inherits from AND holds a reference to the same base class ✓
- B) The decorator only inherits from the base class
- C) The decorator only holds a reference without inheritance
- D) The decorator uses a factory to create new behavior

---

**MCQ-40.** What does `[&]` mean in a lambda capture clause?
- A) Capture all variables by value (copy)
- B) Capture all variables by reference ✓
- C) Capture nothing
- D) Capture only `this`

---

**MCQ-41.** Which lambda correctly filters a `vector<int>` to keep only even numbers using `std::remove_if`?
- A) `remove_if(v.begin(), v.end(), [](int x){ return x % 2 == 0; })` removes evens; to *keep* evens, remove odds:
- B) `remove_if(v.begin(), v.end(), [](int x){ return x % 2 != 0; })` ✓
- C) `remove_if(v.begin(), v.end(), [](int x){ return x > 0; })`
- D) `remove_if(v.begin(), v.end(), [](int x){ return x % 2; })` — same as B ✓

*(Best answer: B — removes odd numbers, keeping even ones)*

---

**MCQ-42.** A functor differs from a plain function because:
- A) A functor can take arguments; a function cannot
- B) A functor can maintain state between calls ✓
- C) A functor is faster than a plain function
- D) A functor cannot be passed as an argument to STL algorithms

---

**MCQ-43.** Which operator does a functor class override to make instances callable?
- A) `operator->`
- B) `operator()`  ✓
- C) `operator[]`
- D) `operator*`

---

**MCQ-44.** What is the output?
```cpp
auto add = [](int a, int b) { return a + b; };
cout << add(3, 4);
```
- A) Compile error — lambdas cannot return values
- B) 34
- C) 7 ✓
- D) Undefined behavior

---

**MCQ-45.** `unique_ptr` cannot be copied because:
- A) C++ does not allow overloading the copy constructor for templates
- B) Two `unique_ptr`s pointing to the same object would both try to `delete` it ✓
- C) `unique_ptr` is a primitive type with no copy semantics
- D) Only `shared_ptr` supports the copy constructor

---

**MCQ-46.** After `shared_ptr<T> p2 = p1;`, the reference count is:
- A) 1 — only one pointer counts
- B) 2 ✓ (both p1 and p2 own the object)
- C) 0 — the object is not yet fully constructed
- D) Undefined

---

**MCQ-47.** After `p1.reset(new T())` where `p1` was the last `shared_ptr` to object A:
- A) Object A's reference count drops to 0 and it is deleted ✓
- B) Object A is moved into the new T
- C) A memory leak occurs
- D) p1 is set to `nullptr`

---

**MCQ-48.** Move semantics are important for performance because:
- A) Moving increments the reference count
- B) Moving avoids a deep copy by transferring ownership of heap resources ✓
- C) Moving uses the copy constructor internally
- D) Moving always results in both objects sharing the resource

---

**MCQ-49.** After `vector<string> v; v.push_back(std::move(s));` where `s = "hello"`:
- A) `s` still contains `"hello"` and a copy is in the vector
- B) `s` is in a moved-from (empty/valid but unspecified) state; vector owns `"hello"` ✓
- C) Both `s` and the vector's element share `"hello"`
- D) `s` is deleted from memory

---

**MCQ-50.** Which design pattern is illustrated here?
```cpp
Logger& log = Logger::get_instance();
log.write("Application started");
```
- A) Facade
- B) Factory Method
- C) Singleton ✓
- D) Observer

---

## ANSWER KEY — MCQ

| # | ✓ | # | ✓ | # | ✓ | # | ✓ | # | ✓ |
|---|---|---|---|---|---|---|---|---|---|
| 1 | C | 11 | B | 21 | C | 31 | B | 41 | B |
| 2 | B | 12 | B | 22 | B | 32 | B | 42 | B |
| 3 | C | 13 | C | 23 | C | 33 | C | 43 | B |
| 4 | C | 14 | B | 24 | C | 34 | B | 44 | C |
| 5 | B | 15 | C | 25 | A | 35 | B | 45 | B |
| 6 | B | 16 | C | 26 | B | 36 | B | 46 | B |
| 7 | C | 17 | B | 27 | B | 37 | C | 47 | A |
| 8 | B | 18 | B | 28 | B | 38 | B | 48 | B |
| 9 | B | 19 | A | 29 | B | 39 | A | 49 | B |
| 10 | B | 20 | C | 30 | C | 40 | B | 50 | C |

---

## CODING EXAM TIPS

1. **Always include required headers** — `<thread>`, `<mutex>`, `<memory>`, `<algorithm>`, etc.
2. **Compile command for threading:** `g++ -std=c++17 -pthread file.cpp`
3. **Pure virtual syntax:** `virtual void foo() = 0;` — don't forget `= 0`
4. **Virtual destructor:** Any base class with virtual methods needs `virtual ~Base() = default;`
5. **`override` keyword:** Always use on overridden methods — the compiler catches typos.
6. **`std::move` does NOT move** — it casts to rvalue reference. The actual move happens in the move constructor/assignment.
7. **lock_guard scope:** Use `{ lock_guard<mutex> g(m); /* critical section */ }` — braces limit the lock duration.
8. **Backtracking template:** Place → Recurse → **Undo** (in that exact order).
9. **Factory return type:** Usually returns base class pointer (`Shape*`, `Toy*`) — not the concrete type.
10. **Decorator must inherit AND hold** the same base type — this is what makes chaining work.

---

*See [STUDY_GUIDE.md](STUDY_GUIDE.md) for concept explanations and [PRACTICE_EXAM.md](PRACTICE_EXAM.md) for the first exam set.*
