#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<random>
class Vehicle
{
private:
    int id;                   // 车辆 ID
    int speed;                // 车辆速度
    int position;             // 车辆位置
    int maxSpeed;             // 车辆最大速度
    int acceleration;         // 车辆加速度
    bool isStopped;           // 车辆是否停止
    std::string direction;    // 车辆行驶方向
    int lane;                 // 车辆所在车道
public:
    Vehicle(int i, int maxSpd = 5, int accel = 1, const std::string& dir = "forward",int ln=0)
    {
        id=i;
        speed=0;
        position=0;
        maxSpeed=maxSpd;
        acceleration=accel;
        isStopped=true||false;
        direction=dir;
        lane=ln; 
    }

    // 获取车辆 ID
    int getId() 
    {
        return id;
    }

    // 获取车辆当前速度
    int getSpeed() 
    {
        return speed;
    }

    // 获取车辆当前位置
    int getPosition()
    {
        return position;
    }

    // 获取车辆最大速度
    int getMaxSpeed()
    {
        return maxSpeed;
    }

    // 获取车辆加速度
    int getAcceleration()
    {
        return acceleration;
    }

    // 获取车辆行驶方向
    std::string getDirection()
    {
        return direction;
    }

    // 判断车辆是否停止
    bool getIsStopped()
    {
        return isStopped;
    }

    // 设置车辆速度
    void setSpeed(int newSpeed) 
    {
        if (newSpeed < 0) 
        {
            speed = 0;

        } 
        else if (newSpeed > maxSpeed)
        {
            speed = maxSpeed;
        } 
        else
        {
            speed = newSpeed;
        }
    }

    // 设置车辆位置
    void setPosition(int newPosition) 
    {
        position = newPosition;
    }

    // 设置车辆最大速度
    void setMaxSpeed(int newMaxSpeed) 
    {
        maxSpeed = newMaxSpeed;
    }

    // 设置车辆加速度
    void setAcceleration(int newAcceleration) 
    {
        acceleration = newAcceleration;
    }

    // 设置车辆行驶方向
    void setDirection(const std::string& newDirection)
    {
        direction = newDirection;
    }

    // 设置车辆所在车道
    void setLane(int newLane)
    {
        lane = newLane;
    }

    // 车辆加速
    void accelerate() 
    {
        if (!isStopped) 
        {
            setSpeed(speed + acceleration);
        }
    }

    // 车辆减速
    void decelerate() 
    {
        setSpeed(speed - acceleration);
    }

    // 车辆停止
    void stop() 
    {
        isStopped = true;
        speed = 0;
    }

    // 车辆启动
    void start() 
    {
        isStopped = false;
    }

    // 车辆移动
    void move() 
    {
        if (!isStopped) 
        {
            if (direction == "forward") 
            {
                position += speed;
            }
            else if (direction == "backward") 
            {
                position -= speed;
            }
        }
    }
};

// 定义交通信号灯状态枚举
enum class TrafficLightState {
    GREEN,               // 绿灯
    YELLOW,              // 黄灯 
    RED,                 // 红灯
    PEDESTRIAN_GREEN,    // 行人绿灯
    PEDESTRIAN_RED       // 行人信号灯处于红灯状态，意味着行人此时不可以通行
};

// 定义交通信号灯类
class TrafficLight
{
private:
    int position;                // 信号灯位置
    TrafficLightState state;     // 信号灯状态
    int cycleDuration;           // 信号灯周期
    int currentTime;             // 信号灯当前时间
    int yellowDuration;          // 黄灯持续时间
    bool hasPedestrianSignal;    // 是否有行人信号
public:
    TrafficLight(int pos, int duration, int yellowDur = 3, bool hasPed = false)
    {
        position=pos; 
        state=TrafficLightState::RED;     // 初始状态为红灯
        cycleDuration=duration;           
        currentTime=0; 
        yellowDuration=yellowDur; 
        hasPedestrianSignal=hasPed;        // 是否有行人信号
    }
        

    // 更新信号灯状态
    void update() 
    {
        currentTime++;
        switch (state)
        {
            // 绿灯
            case TrafficLightState::GREEN:
                if (currentTime >= cycleDuration - yellowDuration) 
                {
                    state = TrafficLightState::YELLOW;
                    currentTime = 0;
                }
                break;

            // 黄灯
            case TrafficLightState::YELLOW:
                if (currentTime >= yellowDuration) 
                {
                    state = TrafficLightState::RED;
                    if (hasPedestrianSignal) 
                    {
                        // 行人信号灯变绿
                        state = TrafficLightState::PEDESTRIAN_GREEN;
                    }
                    currentTime = 0;
                }
                break;

            // 红灯
            case TrafficLightState::RED:
                if (hasPedestrianSignal && state == TrafficLightState::PEDESTRIAN_GREEN) 
                {
                    if (currentTime >= cycleDuration) 
                    {
                        state = TrafficLightState::PEDESTRIAN_RED;
                        currentTime = 0;
                    }
                } 
                else 
                {
                    if (currentTime >= cycleDuration) 
                    {
                        state = TrafficLightState::GREEN;
                        currentTime = 0;
                    }
                }
                break;

            // 行人绿灯
            case TrafficLightState::PEDESTRIAN_GREEN:
                if (currentTime >= cycleDuration) 
                {
                    state = TrafficLightState::PEDESTRIAN_RED;
                    currentTime = 0;
                }
                break;

            // 行人信号灯处于红灯状态，意味着行人此时不可以通行
            case TrafficLightState::PEDESTRIAN_RED:
                if (currentTime >= cycleDuration) 
                {
                    state = TrafficLightState::GREEN;
                    currentTime = 0;
                }
                break;
        }
    }
    // 获取信号灯状态
    TrafficLightState getState()  
    {
        return state;
    }
    // 获取信号灯位置
    int getPosition() 
    {
        return position;
    }
    // 获取当前倒计时
    int getCountdown() 
    {
        switch (state) 
        {
            // 绿灯倒计时
            case TrafficLightState::GREEN:            
               return cycleDuration - yellowDuration - currentTime;

            // 黄灯倒计时
            case TrafficLightState::YELLOW:

            // 红灯倒计时
            case TrafficLightState::RED:
                if (hasPedestrianSignal && state == TrafficLightState::PEDESTRIAN_GREEN) 
                {
                    return cycleDuration - currentTime;
                }

            // 行人绿灯倒计时
            case TrafficLightState::PEDESTRIAN_GREEN:
                return cycleDuration - currentTime;

            // 行人信号灯处于红灯状态，意味着行人此时不可以通行
            case TrafficLightState::PEDESTRIAN_RED:
                return cycleDuration - currentTime;

            // 其他状态
            default:
                return 0;
        }
    }

    // 判断是否有行人信号灯
    bool hasPedestrianLight() 
    {
        return hasPedestrianSignal;
    }
};


class Road 
{
private:
    int length;
    std::vector<Vehicle> vehicles;

public:
    Road(int len) : length(len) {}

    void addVehicle(const Vehicle& vehicle) {
        vehicles.push_back(vehicle);
    }

    void update() {
        for (auto& vehicle : vehicles) {
            vehicle.move();
            if (vehicle.getPosition() >= length) {
                // 车辆驶出道路
                auto it = std::find_if(vehicles.begin(), vehicles.end(), [&](const Vehicle& v) {
                    return v.getId() == vehicle.getId();
                });
                if (it != vehicles.end()) {
                    vehicles.erase(it);
                }
            }
        }
    }

    void showVehicles() const {
        for (const auto& vehicle : vehicles) {
            std::cout << "Vehicle " << vehicle.getId() << " at position " << vehicle.getPosition() << std::endl;
        }
    }
};
