#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Vehicle{
    private:
    int vehicleId;
    string model;
    string manufacturer;
    bool isAvailable;
    public:
    Vehicle(int vehicleId,string model,string manufacturer,bool isAvailable)
        :vehicleId(vehicleId),model(model),manufacturer(manufacturer),isAvailable(isAvailable){}
    int getVehicleId(){
        return vehicleId;
    }
    void setVehicleId(int vehicleId){
        this->vehicleId=vehicleId;
    }
    string getModel()const{
        return model;
    }
    void setModel(string model){
        this->model=model;
    }
    string getManufacturer()const{
        return manufacturer;
    }
    void setManufacturer(string manufacturer){
        this->manufacturer=manufacturer;
    }
    bool getIsAvailable(){
        return isAvailable;
    }
    void setIsAvailable(bool isAvailable){
        this->isAvailable=isAvailable;
    }
    
    void display()const{
        cout<<vehicleId<<" "<<'"'<<model<<'"'<<" "<<'"'<<manufacturer<<'"'<<" "<<(isAvailable ?"Available" : "Unavailable")<<endl;
    }
    
};

class Customer{
  protected:
    int customerId;
    string customerName;
    string customerType;
    public:
    Customer(int customerId,string name,string customerType)
        :customerId(customerId),customerName(name),customerType(customerType){}
    virtual void displayDetails()=0;
};
class Individual:public Customer{
    private:
    int rentLimit;
    public:
    Individual(int id,string name,int limit)
        :Customer(id,name,"Individual"),rentLimit(limit){}
    void displayDetails(){
        cout<<customerId<<" "<<customerName<<" "<<customerType<<" Rent Limit: "<<rentLimit<<endl;
    }
};
class Corporation:public Customer{
    public:
    Corporation(int id,string name)
        :Customer(id,name,"Corporation"){}
    void manageFleet(){
        
    }
    void displayDetails(){
        cout<<customerId<<" "<<customerName<<" "<<customerType<<endl;
    }
};

class RentalServiceInterface{
    public:
    virtual void addVehicle(const Vehicle &vehicle)=0;
    virtual void removeVehicle(int vehicleId)=0;
    virtual void displayAllVehicles()=0;
};
class RentalService:public RentalServiceInterface{
    private:
    vector<Vehicle> vehicles;
    vector<Customer *> customers;
    public:
    void addVehicle( const Vehicle &vehicle) override{
        vehicles.push_back(vehicle);
    }
    void removeVehicle(int vehicleId) override{
        vehicles.erase(
        remove_if(vehicles.begin(),vehicles.end(),
                 [vehicleId](Vehicle &v){
                     return v.getVehicleId()==vehicleId;
                 }),vehicles.end());
    }
    void displayAllVehicles(){
        for(auto &v:vehicles){
            v.display();
        }
    }
    
    void addCustomer(Customer *customer){
        customers.push_back(customer);
    }
    void displayAllCustomers(){
        for(auto &c:customers){
            c->displayDetails();
        }
    }
    void searchVehicle(const string &model)const{
        for(const auto &v:vehicles){
            if(v.getModel()==model){
                v.display();
            }
        }
    }
    void searchVehicleByManufacturer(const string &manufacturer)const{
        for(const auto &v:vehicles){
            if(v.getManufacturer()==manufacturer){
                v.display();
            }
        }
    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    RentalService service;
    //int numberofVehicles=3;
    
    service.addVehicle(Vehicle(101 ,"Model S" ,"Tesla", true));
    service.addVehicle(Vehicle(102 ,"Civic", "Honda",  true));
    service.addVehicle(Vehicle(103 ,"Corolla" ,"Toyota" ,false));
    //int numberofCustomers=2;
    service.addCustomer(new Individual(201 ,"John Doe",2));
    service.addCustomer(new Corporation(202 ,"ABC Corp"));
    cout<<"Vehicles in System:"<<endl;
    service.displayAllVehicles();
    cout<<"\nCustomers in System:"<<endl;
    service.displayAllCustomers();
    cout<<"\nSearch Results:"<<endl;
    cout<<"Model: Civic"<<endl;
    service.searchVehicle("Civic");
    cout<<"Manufacturer: Tesla"<<endl;
    service.searchVehicleByManufacturer("Tesla");

    return 0;
}
