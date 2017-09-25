// -*- C++ -*-
#ifndef INCLUDED_COUNTED_PTR
#define INCLUDED_COUNTED_PTR


namespace CommonUtils{

/**
 * @class counted_ptr<T>
 *
 * @brief: 计数指针
 *  非线程安全
 */

template <class Ty>
class counted_ptr {
  ///
  Ty*   ptr;
  ///
  long* count;
  
  template<class Y> friend class counted_ptr;
  
  template<class Y, class U> 
  friend counted_ptr<Y> dynamic_pointer_cast(counted_ptr<U> const & r);
  
  counted_ptr(Ty* p, long* c):ptr(p),count(c)  {
     if(ptr==0) {
        count = new long(1);
     } else {
         ++*count;
     }
  }
  
public:
  ///
  explicit counted_ptr(Ty* p = 0)
    : ptr(p), count(new long(1)) {
  }

  ///
  counted_ptr(const counted_ptr<Ty>& p)
    : ptr(p.ptr), count(p.count) {
    ++*count;
  }
  
  template<class Y>
  counted_ptr(const counted_ptr<Y>& p)
    : ptr(p.ptr), count(p.count) {
    ++*count;
  }
  
  
  ///
  ~counted_ptr() {
    dispose();
  }

  ///
  counted_ptr<Ty>& operator=(const counted_ptr<Ty>& p) {
    if (this != &p) {
      dispose();
      ptr   = p.ptr;
      count = p.count;
      ++*count;
    }
    return *this;
  }
  
  template<class Y>
    counted_ptr & operator=(counted_ptr<Y> const & p) // never throws
    {
       if ((void*)this != (void*)&p)
       {
    	   dispose();
    	   ptr = p.ptr;
    	   count = p.count;
    	   ++*count;
       }
       return *this;
    }

  ///
  Ty& operator*() const {
    return *ptr;
  }

  ///
  Ty* operator->() const {
    return ptr;
  }

  ///
  Ty* get() const {
    return ptr;
  }
  
  operator bool () const
    {
        return ptr != 0;
    }
    
private:
  ///
  void dispose() {
    if (--*count == 0) {
      delete count;
      delete ptr;
    }
  }
};

template<class T, class U> inline counted_ptr<T> dynamic_pointer_cast(counted_ptr<U> const & r)
{
    return counted_ptr<T>(dynamic_cast<T*>(r.ptr), r.count);
}

}
#endif // INCLUDED_COUNTED_PTR


