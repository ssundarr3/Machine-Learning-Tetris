#include "Subject.h"
#include "SubscriberType.h"
#include "Observer.h"
#include "Info.h"

Subject::Subject() {}

void Subject::Attach(Observer *newObserver) {
	observers.emplace_back(newObserver);
}

void Subject::Detach(SubscriberType t) {
	while(1) {
		int badIndex = -1;

		for (int i = 0; i < observers.size(); ++i) {
			if (observers[i]->GetSubscriberType() == t) {
				badIndex = i;
				break;
			}
		}

		if (badIndex != -1) {
			observers.erase(observers.begin() + badIndex);
		} else {
			break;
		}
	}
}

void Subject::NotifyObservers(SubscriberType t) {
	for (int i = 0; i < observers.size(); ++i) {
		if (observers[i]->GetSubscriberType() == t) {
			observers[i]->Notify(*this);
		}
	}
}

Info Subject::GetInfo(int colNum) {}

Subject::~Subject() {}
