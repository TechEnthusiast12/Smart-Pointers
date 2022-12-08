// Parash Sherpa

// Implementation of Smart Pointers

#ifndef my_memory_h
#define my_memory_h

#include <iostream>

// This is a unique pointer class. Only 1 unique pointer can point to a specific block of memory
template<class T>
class my_unique_ptr{
private:
    T * ptr; // Private data member

public:
    // Default Constructor
    my_unique_ptr(): ptr(nullptr)
    {
    }
    
    // Parameterized Constructor
    my_unique_ptr(T * param){
        ptr = param;
    }
    
    // Copy Constructor
    my_unique_ptr(const my_unique_ptr<T> & param) = delete;
    
    // Copy Assignment
    my_unique_ptr<T> & operator=(const my_unique_ptr<T> & param) = delete;
    
    // Dereferencing operator
    T& operator*(){
    
        return *ptr;
    }
    
    // Member access operator
    T* operator->(){
        return ptr;
    }
    
    // Move Constructor
    my_unique_ptr(my_unique_ptr<T> && param){
        if(param.isNullptr()){
            ptr = nullptr;
        }
        else{
            ptr = std::move(param.ptr);
            param.ptr = nullptr;
        }
    }
    
    // Move Assignment
    my_unique_ptr<T> & operator=(my_unique_ptr<T> && param){
        if(param.isNullptr()){
            if(isNullptr()){
                ptr = nullptr;
            }
            else{
                my_unique_ptr<T> temp;
                temp.ptr = std::move(ptr);
                ptr = nullptr;
                
            }
        }
        else{
            if(isNullptr()){
                ptr = std::move(param.ptr);
                param.ptr = nullptr;
            }
            else{
                my_unique_ptr<T> temp;
                temp.ptr = std::move(ptr);
                ptr = std::move(param.ptr);
                param.ptr = nullptr;
            }
        }
        return *this;
    }
    
    // Destructor
    ~my_unique_ptr(){
            delete ptr;
        
    }
    
    // Checks if the pointer is null or not
    bool isNullptr(){
        if(ptr == nullptr){
            return true;
        }
        return false;
    }
    
};


// This is a Shared Pointer class that has a counter that can keep track of the number of shared pointers that is pointing to a block of memmory
template <class T>
class my_shared_ptr {
private:
    T* ptr;            // Raw pointer as a data member
    int * counter;    // Keeps track of the number of pointers pointing to a block of memory
    
public:
    // Default Constructor
    my_shared_ptr(): ptr(nullptr), counter(nullptr)
    {
        
    }
    
    // Parameterized Constructor
    my_shared_ptr(T* param){
        ptr = param;
        counter = new int(0);
        (*counter)++;
    }
    
    // Dereference operator
    T& operator*() const{
        if(ptr == nullptr){
            throw std::out_of_range("Pointer is null so you can't dereference");
            }
           return *ptr;
       }
       
    
    // Member access operator
    T* operator->() const{
           return ptr;
      }
    
    
    // Copy Constructor
    my_shared_ptr(const my_shared_ptr<T>& param){
        if(param.isNullptr()){
            ptr = nullptr;
            counter = nullptr;
        }
        else{
            ptr = param.ptr;
            counter = param.counter;
            (*counter)++;
        }
        
    }
    
    // Move Constructor
    my_shared_ptr(my_shared_ptr<T> && param){
        if(param.isNullptr()){
            ptr = nullptr;
            counter = nullptr;
        }
        else{
            ptr = std::move(param.ptr);
            counter = std::move(param.counter);
        }
    }
    
    // Copy Assignment
    my_shared_ptr<T>& operator=(const my_shared_ptr<T>& param)
    {
        if(param.isNullptr()){
            
            if(isNullptr()){
                ptr = nullptr;
                counter = nullptr;
            }
            
            else{
                my_shared_ptr<T> temp;
                temp.ptr = ptr;
                temp.counter = counter;
                ptr = nullptr;
                counter = nullptr;
            }
        }
        
        else{
            
            if(isNullptr()){
                ptr = param.ptr;
                counter = param.counter;
                (*counter)++;
            }
            else{
                my_shared_ptr<T> temp;
                temp.ptr = ptr;
                temp.counter = counter;
                ptr = param.ptr;
                counter = param.counter;
                (*counter)++;
            }
        }
        return *this;
    }
    
    //Move Assignment
    my_shared_ptr<T> & operator=(my_shared_ptr<T>&& param){
       if(param.isNullptr()){
           
           if(isNullptr()){
               ptr = nullptr;
               counter = nullptr;
           }
           
           else{
               my_shared_ptr<T> temp;
               temp.ptr = std::move(ptr);
               temp.counter = std::move(counter);
               ptr = nullptr;
               counter = nullptr;
           }
       }
       
       else{
           
           if(isNullptr()){
               ptr = std::move(param.ptr);
               counter = std::move(param.counter);
           }
           else{
               my_shared_ptr<T> temp;
               temp.ptr = std::move(ptr);
               temp.counter = std::move(counter);
               ptr = std::move(param.ptr);
               counter = std::move(param.counter);
           }
       }
        return *this;
    }
    
    // Destructor
    ~my_shared_ptr(){
        
        if(counter == nullptr){
            
        }
        else{
            if((*counter)-- == 0){
                delete ptr;
                delete counter;
            }
        }
    }
    
    // Checks if the shared pointer is null or not
    bool isNullptr() const{
        if(ptr == nullptr){
            return true;
        }
        return false;
    }
    
};


#endif /* my_memory_h */
