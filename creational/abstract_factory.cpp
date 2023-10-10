/*
 * Example of `Abstract Factory' design pattern (Creational Pattern).
 * The Abstract Factory is defining an interface to create families of 
 * related or dependent objects without specifying their concrete classes.
 * 
 * The class consists of the following entities
 * 1. Abstract Factory
 * 2. Concrete Factory
 * 3. Abstract Product
 * 4. Concrete Product
 * 5. Client
 */

#include<iostream>
using namespace std;

class Vehicle{
public:
    virtual void book(int distance) = 0;
    virtual void setVehicleType() = 0;
    virtual void setBaseCost() = 0;
    virtual void setVehicleChargesPerUnitDistance() = 0;
    virtual int calculateCostOfBooking(int distance) = 0;
};

class Car: public Vehicle {
public:
    string carType;
    int baseCost;
    int chargesPerUnitDistance;

    void book(int distance) override {
        setVehicleType();
        setBaseCost();
        setVehicleChargesPerUnitDistance();
        int cost = calculateCostOfBooking(distance);
        cout<<"You have booked a "<<carType<<" Car for a distance of "<<distance<<" kms at a total cost of "<<cost<<". "<<endl;
    }

    int calculateCostOfBooking(int distance) override {
        int serviceCharge = 3;
        return baseCost + chargesPerUnitDistance * distance + serviceCharge;
    }

};

class MicroCar: public Car {
public:
    MicroCar(){}

    void setVehicleType() override {
        carType = "Micro";
    }

    void setBaseCost() override {
        baseCost = 50;
    }

    void setVehicleChargesPerUnitDistance() override {
        chargesPerUnitDistance = 10;
    }
};

class MiniCar: public Car {
public:
    MiniCar(){}

    void setVehicleType() override {
        carType = "Mini";
    }

    void setBaseCost() override {
        baseCost = 100;
    }

    void setVehicleChargesPerUnitDistance() override {
        chargesPerUnitDistance = 20;
    }
};

class MegaCar: public Car {
public:
    MegaCar(){}

    void setVehicleType() override {
        carType = "Mega";
    }

    void setBaseCost() override {
        baseCost = 150;
    }

    void setVehicleChargesPerUnitDistance() override {
        chargesPerUnitDistance = 30;
    }
};


class Auto: public Vehicle {
public:
    string shareType;
    int baseCost;
    int chargesPerUnitDistance;

    void book(int distance) override {
        setVehicleType();
        setBaseCost();
        setVehicleChargesPerUnitDistance();
        int cost = calculateCostOfBooking(distance);
        cout<<"You have booked a "<<shareType<<" Autorickshaw for a distance of "<<distance<<" kms at a total cost of "<<cost<<". "<<endl;
    }

    int calculateCostOfBooking(int distance) override {
        int serviceCharge = 1;
        return baseCost + chargesPerUnitDistance * distance + serviceCharge;
    }
};

class PersonalAuto: public Auto {
public:
    PersonalAuto(){}

    void setVehicleType() override {
        shareType = "Personal";
    }

    void setBaseCost() override {
        baseCost = 10;
    }

    void setVehicleChargesPerUnitDistance() override {
        chargesPerUnitDistance = 15;
    }
};

class SharedAuto: public Auto {
public:
    SharedAuto(){}

    void setVehicleType() override {
        shareType = "Shared";
    }

    void setBaseCost() override {
        baseCost = 0;
    }

    void setVehicleChargesPerUnitDistance() override {
        chargesPerUnitDistance = 10;
    }
};


class Bike: public Vehicle {
public:
    string bikeType;
    int baseCost;
    int chargesPerUnitDistance;

    void book(int distance) override {
        setVehicleType();
        setBaseCost();
        setVehicleChargesPerUnitDistance();
        int cost = calculateCostOfBooking(distance);
        cout<<"You have booked a "<<bikeType<<" Bike for a distance of "<<distance<<" kms at a total cost of "<<cost<<". "<<endl;
    }

    int calculateCostOfBooking(int distance) override {
        return baseCost + chargesPerUnitDistance * distance;
    }
};

class SportsBike: public Bike {
public:
    SportsBike(){}

    void setVehicleType() override {
        bikeType = "Sports";
    }

    void setBaseCost() override {
        baseCost = 40;
    }

    void setVehicleChargesPerUnitDistance() override {
        chargesPerUnitDistance = 15;
    }
};

class NormalBike: public Bike {
public:
    NormalBike(){}

    void setVehicleType() override {
        bikeType = "Normal";
    }

    void setBaseCost() override {
        baseCost = 20;
    }

    void setVehicleChargesPerUnitDistance() override {
        chargesPerUnitDistance = 5;
    }
};

class AbstractVehicleFactory {
public:
    virtual Vehicle*getVehicle(string type) = 0;
};

class CarFactory: public AbstractVehicleFactory {
public:
    CarFactory(){}

    Vehicle*getVehicle(string type) override {
        if(type.compare("Micro") == 0){
            return new MicroCar();
        }
        else if(type.compare("Mini") == 0){
            return new MiniCar();
        }
        else if(type.compare("Mega") == 0){
            return new MegaCar();
        }
        else{
            return new MiniCar();
        }
    }	
};

class AutoFactory: public AbstractVehicleFactory {
public:
    AutoFactory(){}

    Vehicle*getVehicle(string type) override {
        if(type.compare("Personal") == 0){
            return new PersonalAuto();
        }
        else if(type.compare("Shared") == 0){
            return new SharedAuto();
        }
        else{
            return new PersonalAuto();
        }
    }	
};

class BikeFactory: public AbstractVehicleFactory {
public:
    BikeFactory(){}

    Vehicle*getVehicle(string type) override {
        if(type.compare("Sports") == 0){
            return new SportsBike();
        }
        else if(type.compare("Normal") == 0){
            return new NormalBike();
        }
        else{
            return new NormalBike();
        }
    }	
};

class FactoryProvider {
public:
    static AbstractVehicleFactory*getVehicleFactory(string factoryType){
        if(factoryType.compare("Car") == 0){
            return new CarFactory();
        }
        else if(factoryType.compare("Auto") == 0){
            return new AutoFactory();
        }
        else if(factoryType.compare("Bike") == 0){
            return new BikeFactory();
        }
        else{
            return new CarFactory();
        }
    }
};

int main(){
    int distance = 10;

    /*
    * Book a Mini Car for a distance of 10 kms
    */
    AbstractVehicleFactory*carFactory = FactoryProvider::getVehicleFactory("Car");
    Vehicle*miniCar = carFactory->getVehicle("Mini");
    miniCar->book(distance);


    /*
    * Book a Personal Auto for a distance of 10 kms
    */
    AbstractVehicleFactory*autoFactory = FactoryProvider::getVehicleFactory("Auto");
    Vehicle*personalAuto = autoFactory->getVehicle("Personal");
    personalAuto->book(distance);


    /*
    * Book a Sports Bike for a distance of 10 kms
    */
    AbstractVehicleFactory*bikeFactory = FactoryProvider::getVehicleFactory("Bike");
    Vehicle*sportsBike = bikeFactory->getVehicle("Sports");
    sportsBike->book(distance);

    return 0;
}
