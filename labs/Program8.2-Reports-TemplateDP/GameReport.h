#ifndef GAMEREPORT_H
#define GAMEREPORT_H

#include <iostream>
#include <string>

using namespace std;

class GameReport
{
public:
    GameReport(const string t) : title(t) {}
    virtual ~GameReport() {}

    void generate_report()
    {
        print_header();
        acquire_data();
        analyze_data();
        print_report();
        print_footer();
    }

protected:
    void print_header() const
    {
        cout << title << endl;
        cout << endl;
    }

    virtual void acquire_data() = 0;
    virtual void analyze_data() = 0;
    virtual void print_report() const = 0;

    void print_footer() const
    {
        cout << endl;
        cout << "End of report" << endl;
    }

private:
    string title;
};

#endif /* GAMEREPORT_H */
