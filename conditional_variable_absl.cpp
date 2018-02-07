#include <iostream>
#include <string>
#include <thread>
#include "absl/synchronization/mutex.h"
 

absl::Mutex m;
absl::CondVar cv;
std::string data;
bool ready GUARDED_BY(m) = false;
bool processed GUARDED_BY(m) = false;
 
void worker_thread()
{
    // Wait until main() sends data

    m.LockWhen(absl::Condition(&ready));
 
    // after the wait, we own the lock.
    std::cout << "Worker thread is processing data\n";
    data += " after processing";
 
    // Send data back to main()
    processed = true;
    std::cout << "Worker thread signals data processing completed\n";
 
    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    m.Unlock();

}
 
int main()
{
    std::thread worker(worker_thread);
 
    data = "Example data";
    // send data to the worker thread
    {
        absl::MutexLock lk(&m);
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    }

 
    // wait for the worker

    m.LockWhen(absl::Condition(&processed));
    m.Unlock();

    std::cout << "Back in main(), data = " << data << '\n';
 
    worker.join();
}
