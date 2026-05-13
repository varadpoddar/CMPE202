#ifndef BASEBALLREPORT_H_
#define BASEBALLREPORT_H_

#include <string>
#include <vector>
#include "BaseballData.h"

using namespace std;

class BaseballReport
{
public:
    BaseballReport() : title("BASEBALL GAME REPORT")
    {
        singles = doubles = triples = homers = 0;
    }

    void generate_report()
    {
        print_header();
        acquire_data();
        analyze_data();
        print_report();
        print_footer();
    }

private:
    string title;
    vector<int> hits;
    int singles, doubles, triples, homers;

    void print_bar(const char ch, const int count) const;

    void print_header() const;
    void acquire_data();
    void analyze_data();
    void print_report() const;
    void print_footer() const;
};

#endif /* BASEBALLREPORT_H_ */
