#include <iostream>
#include <string>
#include <thread>
#include <mutex>

using namespace std;

const int COUNT = 5;

mutex print_mutex;

void print(string text);

int main(void)
{
    thread hello_thread(print, "Hello, world!\n");
    thread use_thread(print, "Use good design!\n");
    thread go_thread(print, "Go multithreaded!\n");

    hello_thread.join();
    use_thread.join();
    go_thread.join();

    cout << endl << "Program done." << endl;
    return 0;
}

void print(string text)
{
    for (int i = 0; i < COUNT; i++)
    {
        print_mutex.lock();
        {
            for (const char &ch : text) cout << ch;
        }
        print_mutex.unlock();
    }
}
