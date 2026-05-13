#ifndef METER_H_
#define METER_H_

#include <thread>
#include <shared_mutex>
#include <time.h>

using namespace std;
using namespace std::chrono;

/**
 * The shared resource.
 */
class Meter
{
public:
    Meter();
    ~Meter();

private:
    static constexpr int MAX_SETTING_LEVEL         =  4;
    static constexpr int TECHNICIANS_COUNT         =  3;
    static constexpr int TECHNICIAN_TURNS          =  3;
    static constexpr int TECHNICIAN_SET_TIME       =  1;
    static constexpr int MIN_TECHNICIAN_SLEEP_TIME =  3;
    static constexpr int MAX_TECHNICIAN_SLEEP_TIME =  5;
    static constexpr int MAX_LOGGER_SLEEP_TIME     =  3;
    static constexpr int LOGGERS_COUNT             =  3;
    static constexpr int LOGGER_PRINT_MARGIN       = 25;

    int setting;
    int active_technicians_count;
    bool ok_to_log;

    thread technicians[TECHNICIANS_COUNT];
    thread loggers[LOGGERS_COUNT];

    void set_meter(const int thread_id);
    void log_meter(const int thread_id);

    steady_clock::time_point start_time;

    // For multithreading
    shared_mutex meter_mutex;
    mutex print_mutex;

    int elapsed_seconds() const
    {
        return duration_cast<seconds>(
                        steady_clock::now() - start_time).count();
    }
};

#endif /* METER_H_ */
