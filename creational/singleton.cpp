/*
 * Example of `Singleton' design pattern (Creational Pattern).
 * Singleton pattern is defined as ensuring that only a 
 * single instance of a class exists and a global point 
 * of access to it exists.
 */


#include <iostream>
#include <thread> 
#include <mutex>
using namespace std;

class Singleton
{
   private:
      // Supported in C++ 11. To assign the member variable by their default values.
      Singleton() = default;
      ~Singleton() = default;
      // delete copy constructor and assignment
      Singleton(const Singleton&) = delete; 
      Singleton& operator=(const Singleton&) = delete;
      // Supported in C++ 11. move constructor and move assignment
      Singleton(Singleton&&) = delete; 
      Singleton& operator=(Singleton&&) = delete;
      
      static Singleton *m_pInstance;
      static std::mutex m_mutex;
   public:
      static Singleton& getInstance()
      {
         // Double-checked locking pattern
         if(!m_pInstance)
         {
            lock_guard<mutex> _lock(m_mutex); 
            if(!m_pInstance)
            {
               m_pInstance = new Singleton;
            }
         }
         // Return object instead of pointer
         return *m_pInstance; 
      }
};

// Supported in C++ 11. nullptr is defined to initialize the pointer by null.
Singleton* Singleton::m_pInstance = nullptr; 
std::mutex Singleton::m_mutex; 


int main()
{
    //new Singleton(); // Won't work
    Singleton s = Singleton::getInstance(); // Ok

    std::cout << "Object created" << std::endl;
}
