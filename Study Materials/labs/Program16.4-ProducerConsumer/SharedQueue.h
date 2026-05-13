#ifndef SHAREDQUEUE_H_
#define SHAREDQUEUE_H_

#include <queue>
#include <mutex>

using namespace std;

class SharedQueue
{
public:
    SharedQueue(const int cap) : capacity(cap) {}

    mutex& get_mutex() { return queue_mutex; }

    void print()
    {
        queue<int> copy(data);
        int size = copy.size();

        cout << " [";
        for (int i = 0; i < size; i++)
        {
            int value = copy.front();

            if (i == 0) cout << value;
            else        cout << " " << value;

            copy.pop();
        }
        cout << "]" << endl;
    }

    void enter(const int value) { data.push(value); }

    int remove()
    {
        int value = data.front();
        data.pop();
        return value;
    }

    int size() const { return data.size(); }

    bool is_empty() const { return data.size() == 0; }
    bool is_full()  const { return data.size() == capacity; }

    bool just_became_not_empty() const
    {
        return data.size() == 1;
    }

    bool just_became_not_full() const
    {
        return data.size() == capacity - 1;
    }

private:
    size_t capacity;
    queue<int> data;

    mutex queue_mutex;
};

#endif /* SHAREDQUEUE_H_ */
