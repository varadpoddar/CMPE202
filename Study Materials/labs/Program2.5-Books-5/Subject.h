#ifndef SUBJECT_H_
#define SUBJECT_H_

#include <iostream>

using namespace std;

enum class Subject
{
    DRAWING, PAINTING, WRITING
};

inline ostream& operator <<(ostream& ostr, const Subject& subject)
{
    switch (subject)
    {
        case Subject::DRAWING:  ostr << "drawing";  break;
        case Subject::PAINTING: ostr << "painting"; break;
        case Subject::WRITING:  ostr << "writing";  break;
    }

    return ostr;
}

#endif /* SUBJECT_H_ */
