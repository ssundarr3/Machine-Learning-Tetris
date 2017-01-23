#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
class Observer;
class Info;
enum class SubjectType;
enum class SubscriberType;

class Subject {
	std::vector<Observer *> observers;
public:
	Subject();
	void Attach(Observer *);
	void Detach(SubscriberType);
	void NotifyObservers(SubscriberType);
	virtual SubjectType GetSubjectType() = 0;
	virtual Info GetInfo() = 0;
	virtual Info GetInfo(int);
	virtual ~Subject() = 0;
};

#endif
