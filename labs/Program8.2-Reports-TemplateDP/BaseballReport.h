#ifndef BASEBALLREPORT_H_
#define BASEBALLREPORT_H_

#include <vector>
#include "BaseballData.h"
#include "GameReport.h"

using namespace std;

class BaseballReport : public GameReport
{
public:
    BaseballReport() : GameReport("BASEBALL GAME REPORT")
    {
        singles = doubles = triples = homers = 0;
    }

private:
    vector<int> hits;
    int singles, doubles, triples, homers;

    void acquire_data() override;
    void analyze_data() override;
    void print_report() const override;

    void print_bar(const char ch, const int count) const;
};

#endif /* BASEBALLREPORT_H_ */
