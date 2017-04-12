#include "SharedBuffer.h"
#include <windows.h>
#include "Logger.h"

SharedBuffer::SharedBuffer() :
    closed(false) {
}

BOOL SharedBuffer::close() {
    return close(INFINITE);
}

BOOL SharedBuffer::close(DWORD timeout_milliseconds) {
    if (!mutex.get(timeout_milliseconds)) {
	Logger::info("SharedBuffer::close mutex timeout");
        return false;
    }
    closed = true;
    Logger::info("SharedBuffer::close buffer closed");
    mutex.release();      
    return true;
}

BOOL SharedBuffer::put(const BYTE* buffer, DWORD length) {
    return put(buffer, length, INFINITE);
}

BOOL SharedBuffer::put(const BYTE* buffer, DWORD length, DWORD timeout_milliseconds) {
    if (!mutex.get(timeout_milliseconds)) {
	Logger::info("SharedBuffer::put mutex timeout");
        return false;
    }
    if (closed) {
	Logger::info("SharedBuffer::put buffer is closed");
        return false;
    }
    for (DWORD i = 0; i < length; ++i) {
        queue.push(buffer[i]);
    }
    mutex.release();      
    return true;
}
    
DWORD SharedBuffer::get(BYTE* buffer, DWORD length) {
    return get(buffer, length, INFINITE);
}

DWORD SharedBuffer::get(BYTE* buffer, DWORD length, DWORD timeout_milliseconds) {
    if (!mutex.get(timeout_milliseconds)) {
	Logger::info("SharedBuffer::get mutex timeout");
        return 0;
    }
    DWORD result = length < queue.size() ? length : queue.size();
    for (DWORD i = 0; i < result; ++i) {
        buffer[i] = queue.front();
        queue.pop();
    }
    if (closed && result == 0) {
        result = length + 1;
	Logger::debug("SharedBuffer::get buffer is closed and empty");
    }
    mutex.release();      
    return result;
}
