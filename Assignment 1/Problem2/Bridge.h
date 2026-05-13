#ifndef BRIDGE_H_
#define BRIDGE_H_

class Island;

class Bridge
{
public:
    Bridge(const Island * const ep, const int t)
        : endpoint(ep), toll(t) {}

    const Island * const get_endpoint() const { return endpoint; }
    int get_toll() const { return toll; }

private:
    const Island * const endpoint;  // island where the bridge ends
    const int toll;                 // toll to cross the bridge
};

#endif /* BRIDGE_H_ */
