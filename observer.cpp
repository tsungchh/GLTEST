#include "observer.h"


Observer::Observer(Subject* sub)
{
    model = sub;
    model->attach(this);
}

Observer::~Observer()
{

}


void Subject::attach(Observer* obs)
{
     views.push_back(obs);
}

void Subject::notify()
{
    for(size_t i=0; i<views.size(); ++i)
    {
        views[i]->update();
    }
}
