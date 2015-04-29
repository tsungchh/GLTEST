#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>
using namespace std;
class Subject;
class Observer
{
public:
    Observer(Subject* sub);
    ~Observer();

    virtual void update() = 0;

private:
    Subject* model;
};

class Subject
{
public:

    void attach(Observer *obs);

    void notify();
private:

    vector<Observer*> views;

};





#endif // OBSERVER_H
