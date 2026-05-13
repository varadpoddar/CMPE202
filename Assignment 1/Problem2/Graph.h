#ifndef GRAPH_H_
#define GRAPH_H_

#include "Island.h"
#include "Bridge.h"

class Graph
{
private:
    Island is1, is2, is3, is4, is5, is6, is7, is8;

    Bridge br12, br13, br14;
    Bridge br24, br25;
    Bridge br36;
    Bridge br43, br45, br46, br47;
    Bridge br68;
    Bridge br75, br76, br78;

public:
    /**
     * Constructor: Build the graph of islands and bridges.
     */
    Graph() : is1(Island("Island 1")),
              is2(Island("Island 2")),
              is3(Island("Island 3")),
              is4(Island("Island 4")),
              is5(Island("Island 5")),
              is6(Island("Island 6")),
              is7(Island("Island 7")),
              is8(Island("Island 8")),

              br12(Bridge(&is2, 2)),
              br13(Bridge(&is3, 3)),
              br14(Bridge(&is4, 2)),

              br24(Bridge(&is4, 3)),
              br25(Bridge(&is5, 1)),

              br36(Bridge(&is6, 3)),

              br43(Bridge(&is3, 3)),
              br45(Bridge(&is5, 2)),
              br46(Bridge(&is6, 4)),
              br47(Bridge(&is7, 3)),

              br68(Bridge(&is8, 2)),

              br75(Bridge(&is5, 3)),
              br76(Bridge(&is6, 1)),
              br78(Bridge(&is8, 4))
    {
        is1.set_bridges(vector<const Bridge *> { &br12, &br13, &br14 });
        is2.set_bridges(vector<const Bridge *> { &br24, &br25 });
        is3.set_bridges(vector<const Bridge *> { &br36 });
        is4.set_bridges(vector<const Bridge *> { &br43, &br45, &br46, &br47 });
        is6.set_bridges(vector<const Bridge *> { &br68 });
        is7.set_bridges(vector<const Bridge *> { &br75, &br76, &br78 });
    }

    Island const *get_start() const { return &is1; }
    Island const *get_destination() const { return &is6; }
};



#endif /* GRAPH_H_ */
