#ifndef FANCLUBREPORT_H_
#define FANCLUBREPORT_H_

#include <string>
#include "Observer.h"
#include "BaseballReporter.h"

using namespace std;

class FanClubReport : public Observer
{
public:
    FanClubReport(BaseballReporter * const r, const string name)
        : reporter(r), idol(name), what("")
    {
        r->attach(this);
    }

    void update(const string name, const int outs) override;

    void print_report() const;

private:
    BaseballReporter *reporter;
    string idol;
    string what;
};

#endif /* FANCLUBREPORT_H_ */
