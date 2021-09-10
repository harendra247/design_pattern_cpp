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
   // Supported in C++ 11. move constructor
   Singleton(const Singleton&) = delete; 
   Singleton& operator=(const Singleton&) = delete;
   static Singleton* m_pInstance;
   public:
   static Singleton& getInstance()
   {
      // Double-checked locking pattern
      if(!m_pInstance)
      {
         mutex _mutex;
         lock_guard<mutex> _lock(_mutex); 
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


int main()
{
    //new Singleton(); // Won't work
    Singleton s = Singleton::getInstance(); // Ok

    std::cout << "Object created" << std::endl;
}
