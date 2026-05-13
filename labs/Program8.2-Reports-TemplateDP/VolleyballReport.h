#ifndef VOLLEYBALLREPORT_H_
#define VOLLEYBALLREPORT_H_

#include <vector>

#include "GameReport.h"
#include "VolleyballData.h"

using namespace std;

class VolleyballReport : public GameReport
{
public:
    VolleyballReport()
        : GameReport("VOLLEYBALL GAME REPORT"),
          team1_is_winner(false), losers_score(0) {}

private:
    vector<int> points;
    bool team1_is_winner;
    int  losers_score;

    void acquire_data() override;
    void analyze_data() override;
    void print_report() const override;
};

#endif /* VOLLEYBALLREPORT_H_ */
