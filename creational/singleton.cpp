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
   protected:
       Singleton(const std::string value): m_value(value)
       { }
       ~Singleton() {}
       std::string m_value;
   public:
      static Singleton& getInstance(std::string m_value)
      {
         // Double-checked locking pattern
         if(!m_pInstance)
         {
            lock_guard<mutex> _lock(m_mutex); 
            if(!m_pInstance)
            {
               m_pInstance = new Singleton(m_value);
            }
         }
         // Return object instead of pointer
         return *m_pInstance; 
      }

      std::string value() const {
         return m_value;
      } 
};

// Supported in C++ 11. nullptr is defined to initialize the pointer by null.
Singleton* Singleton::m_pInstance = nullptr; 
std::mutex Singleton::m_mutex; 

void ThreadFoo(){
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::getInstance("FOO");
    std::cout << singleton->value() << "\n";
}

void ThreadBar(){
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::getInstance("BAR");
    std::cout << singleton->value() << "\n";
}

int main()
{   
   //new Singleton(); // Won't work
   Singleton s = Singleton::getInstance("FOO"); // Ok
   std::cout << s->value() << "\n";

   std::cout << "Object created" << std::endl;
   
   std::cout <<"If you see the same value, then singleton was reused (yay!\n" <<
                "If you see different values, then 2 singletons were created (booo!!)\n\n" <<
                "RESULT:\n";   
    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);
    t1.join();
    t2.join();
    
    return 0;
}
