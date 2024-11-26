#ifndef DYNAMIC_ARRAY_NODE_H
#define DYNAMIC_ARRAY_NODE_H

struct DynamicArrayNode {
    int key;
    int value;
    bool isOccupied;

    DynamicArrayNode() : key(0), value(0), isOccupied(false) {}
    DynamicArrayNode(int k, int v, bool occupied) : key(k), value(v), isOccupied(occupied) {}
};

#endif
