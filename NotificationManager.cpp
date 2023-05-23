#include "NotificationManager.h"

NotificationManager::NotificationManager()
{
	observers = gcnew List<NotificationObserver^>();
}

NotificationManager::~NotificationManager()
{

}

void NotificationManager::notify(NotificationKey key, void* value)
{
	for each (NotificationObserver^ observer in observers)
	{
		observer->onNotification(key, value);
	}
}

void NotificationManager::subscribe(NotificationObserver^ observer)
{
	observers->Add(observer);
}