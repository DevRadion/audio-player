#include "ThreadManager.h"

DispatchQueue::DispatchQueue()
{
	semaphore = gcnew Semaphore(0, Int32::MaxValue);
	event = gcnew AutoResetEvent(false);
	workerThread = gcnew Thread(gcnew ThreadStart(this, &DispatchQueue::Run));
	workerThread->IsBackground = true;
	workerThread->Start();
}

void DispatchQueue::Dispatch(Action^ action)
{
	semaphore->Release();
	event->WaitOne();
	ThreadPool::QueueUserWorkItem(gcnew WaitCallback(DispatchQueue::ExecuteAction), Tuple::Create(this, action));
}

void DispatchQueue::Run()
{
	while (true)
	{
		semaphore->WaitOne();
		event->Set();
	}
}

void DispatchQueue::ExecuteAction(Object^ state)
{
	Tuple<DispatchQueue^, Action^>^ tuple = static_cast<Tuple<DispatchQueue^, Action^>^>(state);
	DispatchQueue^ queue = tuple->Item1;
	Action^ action = tuple->Item2;
	action->Invoke();
}