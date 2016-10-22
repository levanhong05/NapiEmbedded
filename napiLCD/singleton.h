#ifndef SINGLETON_H
#define SINGLETON_H

#include <QObject>

template <class T>
class Singleton
{
public:
    Singleton();
    static T& Instance()
    {
        static T _instance; // create static instance of our class
        return _instance;   // return it
    }
};

#endif // SINGLETON_H
