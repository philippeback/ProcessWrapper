#include "SqueakSemaphore.h"
#include "Logger.h"

extern "C" int signalSemaphore(int);

SqueakSemaphore::SqueakSemaphore(int semaphore_index) :
    semaphore_index(semaphore_index) {
}
	
void SqueakSemaphore::signal() const {
    if (semaphore_index > -1) {
        signalSemaphore(semaphore_index);
    } else {
        Logger::debug("SqueakSemaphore::signal semaphore is invalid");
    }
};

void SqueakSemaphore::invalidate() {
    semaphore_index = -1;
}
