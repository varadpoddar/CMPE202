#include <iostream>
#include <vector>
#include "Person.h"

void init(vector<Person>& v)
{
    v.push_back(Person("Marie",  "Curie",   Gender::F));
    v.push_back(Person("Agatha", "Cristie", Gender::F));
    v.push_back(Person("Biden",  "Joe",     Gender::M));
    v.push_back(Person("Tom",    "Cruise",  Gender::M));
    v.push_back(Person("Julia",  "Child",   Gender::F));
    v.push_back(Person("Ron",    "Mak",     Gender::M));
}

vector<Person> select(const vector<Person> people,
                      bool matches(const Person &p))
{
    vector<Person> selected;
    for (const Person& p : people) if (matches(p)) selected.push_back(p);
    return selected;
}

int main()
{
    vector<Person> people;
    init(people);

    cout << "Males:" << endl;
    vector<Person> males = select(people,
                                  [] (const Person &p) -> bool
                                  {
                                      return p.gender == Gender::M;
                                  });
    for (Person& p : males) cout << p << endl;

    cout << endl << "Last name starts with C:" << endl;
    vector<Person> cs = select(people,
                               [] (const Person &p) -> bool
                               {
                                   return p.last[0] == 'C';
                               });
    for (Person& p : cs) cout << p << endl;
}
