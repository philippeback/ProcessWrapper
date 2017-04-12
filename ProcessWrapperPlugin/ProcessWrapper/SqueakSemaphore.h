#ifndef SQUEAK_SEMAPHORE_H
#define SQUEAK_SEMAPHORE_H

class SqueakSemaphore {
    
    private: int semaphore_index;
    
    public: SqueakSemaphore(int semaphore_index);

    public: void signal() const;   

    public: void invalidate();

};

#endif // SQUEAK_SEMAPHORE_H
