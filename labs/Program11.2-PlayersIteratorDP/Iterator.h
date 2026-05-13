#ifndef ITERATOR_H_
#define ITERATOR_H_

#include "Player.h"

class Iterator
{
public:
    virtual Player *next() = 0;
    virtual bool has_next() const = 0;
};

class ArrayIterator : public Iterator
{
public:
    ArrayIterator(Player *ps[]) : players(ps), cursor(0) {}

    Player *next() override { return players[cursor++]; }

    bool has_next() const override
    {
        return cursor < 9;
    }

private:
    Player **players;
    int cursor;
};

class VectorIterator : public Iterator
{
public:
    VectorIterator(const vector<Player *> ps)
        : players(ps), cursor(players.begin()) {}

    Player *next() override { return *(cursor++); }

    bool has_next() const override
    {
        return cursor != players.end();
    }

private:
    vector<Player *> players;
    vector<Player *>::iterator cursor;
};

class MapIterator : public Iterator
{
public:
    MapIterator(const map<long, Player *> ps)
        : players(ps), cursor(players.begin()) {}

    Player *next() override { return (cursor++)->second; }

    bool has_next() const override
    {
        return cursor != players.end();
    }

private:
    map<long, Player *> players;
    map<long, Player *>::iterator cursor;
};

#endif /* ITERATOR_H_ */
