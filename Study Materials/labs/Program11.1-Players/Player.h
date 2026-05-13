#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

using namespace std;

class Player
{
public:
    Player(const long id, const string last, const string first)
        : student_id(id), last_name(last), first_name(first) {}

    long   get_student_id() const { return student_id; }
    string get_last_name()  const { return last_name; }
    string get_first_name() const { return first_name; }

private:
    long   student_id;
    string last_name;
    string first_name;
};

#endif /* PLAYER_H_ */
