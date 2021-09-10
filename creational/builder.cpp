/*
 * Example of `builder' design pattern  (Creational Pattern).
 * a builder pattern encapsulates or hides the process of building 
 * a complex object and separates the representation of the object 
 * and its construction. The separation allows us to construct different 
 * representations using the same construction process.
 *
 * The class consists of the following entities
 * 1. Builder
 * 2. Concrete Builder
 * 3. Director
 * 4. Product
 */


#include <iostream>
#include <string>

/* Parts Builder */
class Wheel
{
    public:
        int size;
};

class Engine
{
    public:
        int horsepower;
};

class Body
{
    public:
        std::string shape;
};

/* Product */
class Car
{
    public:
        Wheel*   wheels[4];
        Engine*  engine;
        Body* body;
    
        void specifications()
        {
            std::cout << "body:" << body->shape << std::endl;
            std::cout << "engine horsepower:" << engine->horsepower << std::endl;
            std::cout << "tire size:" << wheels[0]->size << "'" << std::endl;
        }
};

/* Builder */
class Builder
{
    public:
        virtual Wheel* getWheel() = 0;
        virtual Engine* getEngine() = 0;
        virtual Body* getBody() = 0;
};

/* Director is responsible for the whole process */
class Director
{
    Builder* builder;

    public:
        void setBuilder(Builder* newBuilder)
        {
            builder = newBuilder;
        }

        Car* getCar()
        {
            Car* car = new Car();

            car->body = builder->getBody();

            car->engine = builder->getEngine();

            car->wheels[0] = builder->getWheel();
            car->wheels[1] = builder->getWheel();
            car->wheels[2] = builder->getWheel();
            car->wheels[3] = builder->getWheel();

            return car;
        }
};

/* Concrete Builder for Jeep SUV cars */
class JeepBuilder : public Builder
{
    public:
        Wheel* getWheel()
        {
            Wheel* wheel = new Wheel();
            wheel->size = 22;
            return wheel;
        }

        Engine* getEngine()
        {
            Engine* engine = new Engine();
            engine->horsepower = 400;
            return engine;
        }

        Body* getBody()
        {
            Body* body = new Body();
            body->shape = "SUV";
        }
};

/* Concrete builder for Nissan family cars */
class NissanBuilder : public Builder
{
    public:
        Wheel* getWheel()
        {
            Wheel* wheel = new Wheel();
            wheel->size = 16;
            return wheel;
        }

        Engine* getEngine()
        {
            Engine* engine = new Engine();
            engine->horsepower = 85;
            return engine;
        }

        Body* getBody()
        {
            Body* body = new Body();
            body->shape = "hatchback";
        }
};


int main()
{
    Car* car; // Final product

    /* A director who controls the process */
    Director director;

    /* Concrete builders */
    JeepBuilder jeepBuilder;
    NissanBuilder nissanBuilder;

    /* Build a Jeep */
    std::cout << "Jeep" << std::endl;
    director.setBuilder(&jeepBuilder); // using JeepBuilder instance
    car = director.getCar();
    car->specifications();

    std::cout << std::endl;

    /* Build a Nissan */
    std::cout << "Nissan" << std::endl;
    director.setBuilder(&nissanBuilder); // using NissanBuilder instance
    car = director.getCar();
    car->specifications();

    return 0;
}
