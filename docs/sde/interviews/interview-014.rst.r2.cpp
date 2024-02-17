#include <iostream>

class AbstractBase {
	public:
		virtual void display() = 0; //
};

class Derived: public AbstractBase {
	public:
		void display() override;
};

int main(int ac, char **av) {
	AbstractBase *ab = new Derived();
	return 0;
}

// Singleton pattern
class Singleton {
public:
	static Singleton& getInstance(void) {
		static Singleton obj;
		return obj;
	}
}

// observer pattern
class EventNotificationsObserver {
	std::vector<EventBase> objs;

	public:
		void register_event(EventBase &obj) {
			objs.push_back(obj);
		}

		void notify_events() {
			for(auto o : objs) o.notify();
		}

		void receive_event(EventBase &obj) {
			obj.processEvent();
		}
}

class EventBase {
}

class MessageReceivedEvent: public EventBase {
}

class MessageSentEvent: public EventBase {
}

