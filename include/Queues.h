
#if !defined(_QUEUE_H_)
#define _QUEUE_H_
#include <list>
#include <pthread.h>
#include <vector>
#include <queue>

namespace CommonUtils{

/* 2015-11-20   que 去掉入队、出队的额外互斥量，修改pthread_cond_signal 为 pthread_cond_broadcast，激活所有等待此条件的线程
 *
 */

static void clean (void *arg)
{
	pthread_mutex_unlock ((pthread_mutex_t *)arg);
}

template < class Data > class Queue
{
	public:
		Queue (int qsize);
		virtual ~ Queue ();
		void push_first (const Data & stask);
		void pop (Data & stask);
		int size ();
		int maxsize ();		// 容器大小
	private:
		int _qsize;		// 容器大小
		int _size;		//容器内的数据个数
		std::list < Data > _plist;
		pthread_mutex_t _connect_lock;

		pthread_cond_t _customer_cond;
		pthread_cond_t _producer_cond;
};

template < class Data > Queue < Data >::Queue (int qsize):_qsize (qsize), _size (0)
{
	pthread_mutex_init (&_connect_lock, NULL);

	pthread_cond_init (&_customer_cond, NULL);
	pthread_cond_init (&_producer_cond, NULL);
}

template < class Data > Queue < Data >::~Queue ()
{
	pthread_cond_destroy (&_producer_cond);
	pthread_cond_destroy (&_customer_cond);
	
	pthread_mutex_destroy (&_connect_lock);

}

template < class Data > void Queue < Data >::push_first (const Data & stask)
{
    pthread_cleanup_push((void (*)(void *))clean,(void *)(&_connect_lock));


	pthread_mutex_lock (&_connect_lock);

	while (_plist.size () == _qsize)
	{
		pthread_cond_wait (&_customer_cond, &_connect_lock);
	}

	_plist.push_back (stask);
	_size++;

	pthread_cond_broadcast (&_producer_cond);
	pthread_cleanup_pop(1);
}

template < class Data > void Queue < Data >::pop (Data & stask)
{
	pthread_cleanup_push((void (*)(void *))clean,(void *)(&_connect_lock));

	pthread_mutex_lock (&_connect_lock);

	while (_plist.size () == 0)
	{
		pthread_cond_wait (&_producer_cond, &_connect_lock);
	}

	stask = _plist.front ();
	_plist.pop_front ();
	_size--;


	pthread_cond_broadcast (&_customer_cond);
	pthread_cleanup_pop(1);
}

template < class Data > int Queue < Data >::size ()
{
	return _size;
}

template < class Data > int Queue < Data >::maxsize ()
{
	return _qsize;

}




//////////////////////
//通过重载对象的 < 实现高、低优先级队列
template<class T>
class CycleQueue
{
public:
    CycleQueue(int iMaxsize);
    ~CycleQueue();

    void push_first(const T &value);
    void pop(T &value);

    int size();
    int maxsize();


private:
    void _push(const T &value);
    void _pop(T &value);
    void _resize();
    std::vector<T> *m_vecCycle;
    int m_iHead;    ///队列头位置
    int m_iTail;    ///队列尾位置
    int m_iQSize;   ///队列大小
    int m_iSize;    ///队列容纳数据量

    pthread_mutex_t _connect_lock;
    pthread_cond_t _producer_cond;

};


template<class T>
CycleQueue<T>::CycleQueue(int iMaxsize)
{
    m_iQSize = iMaxsize;
    m_iHead = m_iTail = m_iSize = 0;
    m_vecCycle = new std::vector<T>(m_iQSize);


    pthread_mutex_init (&_connect_lock, NULL);
    pthread_cond_init (&_producer_cond, NULL);
}


template<class T>
CycleQueue<T>::~CycleQueue()
{
    delete m_vecCycle;

    pthread_cond_destroy (&_producer_cond);
    pthread_mutex_destroy (&_connect_lock);
}



template<class T>
void CycleQueue<T>::push_first(const T& value)
{
    pthread_cleanup_push((void (*)(void *))clean,(void *)(&_connect_lock));

    pthread_mutex_lock (&_connect_lock);

    if(m_iSize >=  m_iQSize )
    {
        ///队列已满
        _resize();
    }

    _push(value);

    pthread_cond_broadcast (&_producer_cond);
    pthread_cleanup_pop(1);

}


template<class T>
void CycleQueue<T>::pop(T &value)
{
    pthread_cleanup_push((void (*)(void *))clean,(void *)(&_connect_lock));

    pthread_mutex_lock (&_connect_lock);

    while (m_iSize == 0)
    {
        pthread_cond_wait (&_producer_cond, &_connect_lock);
    }

    _pop(value);

    pthread_cleanup_pop(1);
}


template<class T>
int CycleQueue<T>::size()
{

    pthread_mutex_lock (&_connect_lock);

    int iSize = m_iSize;

    pthread_mutex_unlock(&_connect_lock);

    return iSize;
}

template<class T>
int CycleQueue<T>::maxsize()
{

    pthread_mutex_lock (&_connect_lock);

    int iQSize = m_iQSize;

    pthread_mutex_unlock(&_connect_lock);

    return iQSize;
}

template<class T>
void CycleQueue<T>::_push(const T &value)
{
    (*m_vecCycle)[ m_iTail++ ] = value;
    m_iTail = m_iTail % m_iQSize;
    m_iSize++;
}

template<class T>
void CycleQueue<T>::_pop(T &value)
{
    value = (*m_vecCycle)[m_iHead++];
    m_iHead = m_iHead % m_iQSize;
    m_iSize--;
}

template<class T>
void CycleQueue<T>::_resize()
{
    int iQSize = m_iQSize*3/2 + 1;
    std::vector<T> *vec = new std::vector<T>(iQSize);

    T value;
    int iSize = m_iSize ;
    for(int i = 0 ; i < iSize ; ++i)
    {
        _pop(value);
        (*vec)[i] = value;
    }

    ///
    delete m_vecCycle;
    m_iHead = 0;
    m_iTail = m_iSize = iSize;
    m_iQSize = iQSize;
    m_vecCycle = vec;

}


////////////////////////////////////////

template<class T>
class PriorityQueue
{
public:
    PriorityQueue();
    ~PriorityQueue();

    void push(const T &value);   ////非阻塞
    void pop(T &value);
    ///void top(T &value);   ///不提供(读、  取异步，无法同步)
    int size();

private:
    std::priority_queue<T> m_priQueue;
    pthread_mutex_t _connect_lock;
    pthread_cond_t _producer_cond;

};

template<class T>
PriorityQueue<T>::PriorityQueue()
{
    pthread_mutex_init (&_connect_lock, NULL);
    pthread_cond_init (&_producer_cond, NULL);
}

template<class T>
PriorityQueue<T>::~PriorityQueue()
{
    pthread_cond_destroy (&_producer_cond);
    pthread_mutex_destroy (&_connect_lock);
}

template<class T>
void PriorityQueue<T>::push(const T &value)
{
    pthread_cleanup_push((void (*)(void *))clean,(void *)(&_connect_lock));

    pthread_mutex_lock (&_connect_lock);

    m_priQueue.push(value);

    pthread_cond_broadcast (&_producer_cond);

    pthread_cleanup_pop(1);
}


template<class T>
void PriorityQueue<T>::pop(T &value)
{
    pthread_cleanup_push((void (*)(void *))clean,(void *)(&_connect_lock));


    pthread_mutex_lock (&_connect_lock);

    while(m_priQueue.empty())
        pthread_cond_wait (&_producer_cond, &_connect_lock);

    value = m_priQueue.top();
    m_priQueue.pop();

    pthread_cleanup_pop(1);
}

template<class T>
int PriorityQueue<T>::size()
{
    pthread_mutex_lock (&_connect_lock);

    int iSize = m_priQueue.size();

    pthread_mutex_unlock (&_connect_lock);


    return iSize;
}

}
#endif
