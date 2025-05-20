#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include "Vehicle.h"
#include "Road.h"
#include "TrafficLight.h"

// 静态成员变量的定义
double EmergencyVehicle::ALARM_ACC = 2.0;
double EmergencyVehicle::NORMAL_ACC = 1.5;

// Road类静态成员变量的定义
int Road::vehicleCount = 0;
int Road::lightCount = 0;
Vehicle* Road::vehicles[Road::MAX_VEHICLES];
TrafficLight Road::trafficLights[Road::MAX_LIGHTS];


int main() {
    // 创建道路
    int entrances[] = {0, 50, 100};
    int exits[] = {150, 200};
    Road road(200, 3, 0, 0, 3, 2, entrances, exits);
    
    // 添加交通灯
    TrafficLight light1(30, 20, 3, false);
    TrafficLight light2(80, 20, 3, true);
    TrafficLight light3(130, 20, 3, false);
    
    road.addTrafficLight(light1);
    road.addTrafficLight(light2);
    road.addTrafficLight(light3);
    
    // 创建车辆
    Car car1(1, 5, 0, 100, 10, "forward", 0);
    Truck truck1(2, 3, 10, 80, 8, "forward", 1);
    
    // 创建公交车
    int busStops[] = {20, 60, 100, 140, 180};
    Bus bus1(3, 2, busStops, 5);
    
    // 创建紧急车辆
    std::string direction = "forward";
    EmergencyVehicle ambulance(4, 0, 5, 120, 15, direction, 0, true);
    
    // 添加车辆到道路
    road.addVehicle(&car1);
    road.addVehicle(&truck1);
    road.addVehicle(&bus1);
    road.addVehicle(&ambulance);
    
    // 启动所有车辆
    car1.start();
    truck1.start();
    bus1.start();
    ambulance.start();
    
    // 模拟交通流
    for (int i = 0; i < 20; i++) {
        std::cout << "\n===== 时间步骤: " << i << " =====\n";
        
        // 更新道路状态
        road.update();
        
        // 显示道路状态
        road.display();
        
        // 暂停一下，便于观察
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    std::cout << "\n交通模拟结束!\n";
    return 0;
}