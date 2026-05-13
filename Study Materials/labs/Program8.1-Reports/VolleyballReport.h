#ifndef VOLLEYBALLREPORT_H_
#define VOLLEYBALLREPORT_H_

#include <string>
#include <vector>
#include "VolleyballData.h"

using namespace std;

class VolleyballReport
{
public:
    VolleyballReport()
        : title("VOLLEYBALL GAME REPORT"),
          team1_is_winner(false), losers_score(0) {}

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
    vector<int> points;
    bool team1_is_winner;
    int  losers_score;

    void print_header() const;
    void acquire_data();
    void analyze_data();
    void print_report() const;
    void print_footer() const;
};

#endif /* VOLLEYBALLREPORT_H_ */
