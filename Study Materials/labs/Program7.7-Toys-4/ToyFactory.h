#ifndef TOYFACTORY_H_
#define TOYFACTORY_H_

#include "Toy.h"

enum class Kind { CAR, AIRPLANE, TRAIN };

class ToyFactory
{
public:
    static Toy *make(const Kind kind)
    {
        switch (kind)
        {
            case Kind::CAR:
                return new ToyCar(new Roll(), new Engine());

            case Kind::AIRPLANE:
                return new ModelAirplane(new Fly(), new Engine());

            case Kind::TRAIN:
                return new TrainSet(new Roll(), new ChooChoo());

            default: return nullptr;
        }
    }
};

#endif /* TOYFACTORY_H_ */
