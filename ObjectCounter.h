#ifndef OBJECT_COUNTER_H
#define OBJECT_COUNTER_H

template<typename T>
class Counter {
    public:
        Counter() { ++count; }
        Counter(const Counter&) { ++count; }
        ~Counter() { --count; }

        static size_t howMany()
        { return count; }
    private:
        static size_t count;
};

#endif
