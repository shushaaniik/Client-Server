#ifndef __THREAD_POOL_HPP__
#define __THREAD_POOL_HPP__

#include <functional>
#include <unordered_set>
#include <queue>

#include <pthread.h>

namespace os 
{
    typedef void* input_t;
    typedef void* output_t;
    typedef std::function<output_t(input_t)> entry_point_t;
    typedef std::function<output_t(input_t, output_t)> callback_t;

    struct execution_context {
        entry_point_t _entry_point;
        callback_t _callback;
        input_t _input;
    };

    class threadpool {
        public:
            static threadpool& instance(); 
            threadpool(threadpool const&)      = delete;
            void operator=(threadpool const&)  = delete;
            void enqueue_work(entry_point_t entry_point, input_t input, callback_t callback); 
            void state();
            void destroy();
            void exit();
        protected:
            threadpool();
            void validate(int err);
            void create_worker(bool is_main);
            void do_work(bool is_main);
            static void* start_routine(void* input);
        private:
            pthread_mutex_t _works_lock;
            pthread_mutex_t _workers_lock;
            pthread_cond_t _can_be_dequeued;
            std::size_t busy_count;
            std::queue<execution_context> _works;
            std::unordered_set<pthread_t> _workers;
    };
};

#endif
