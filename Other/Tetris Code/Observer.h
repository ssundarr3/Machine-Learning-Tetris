#ifndef OBSERVER_H
#define OBSERVER_H

class Subject;
enum class SubscriberType;

class Observer {
public:
	Observer();
	virtual void Notify(Subject &) = 0;
	virtual SubscriberType GetSubscriberType() = 0;
	virtual ~Observer() = 0;
};

#endif
