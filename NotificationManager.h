#pragma once
#include <vector>

using namespace System;
using namespace System::Collections::Generic;

enum NotificationKey
{
	UPDATE_TIMELINE
};

interface class NotificationObserver
{
public:
    virtual void onNotification(NotificationKey key, void* value) = 0;
};

public ref class NotificationManager
{
    static NotificationManager^ instance = nullptr;

public:

    static property NotificationManager^ Instance
    {
        NotificationManager^ get()
        {
            if (instance == nullptr)
                instance = gcnew NotificationManager();
            return instance;
        }
    }

	void notify(NotificationKey key, void* value);

	void subscribe(NotificationObserver^ observer);

private:
	NotificationManager();

	~NotificationManager();

    List<NotificationObserver^>^ observers;
};

