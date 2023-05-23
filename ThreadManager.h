#pragma once
#include "audiomanager.h"

#include <Windows.h>

using namespace System;
using namespace System::Threading;
using namespace System::Collections::Generic;

public ref class DispatchQueue
{
private:
    Semaphore^ semaphore;
    AutoResetEvent^ event;
    Thread^ workerThread;

public:
    DispatchQueue();

    void Dispatch(Action^ action);

private:
    void Run();

    static void ExecuteAction(Object^ state);
};