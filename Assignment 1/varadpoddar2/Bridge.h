#ifndef BRIDGE_H_
#define BRIDGE_H_

class Island;

class Bridge
{
public:
    Bridge(const Island * ep, int t) : endpoint(ep), toll(t) {}

    const Island * get_endpoint() const { return endpoint; }
    int get_toll() const { return toll; }

private:
    const Island * endpoint;  // island where the bridge ends
    int toll;                 // toll to cross the bridge
};

#endif /* BRIDGE_H_ */
