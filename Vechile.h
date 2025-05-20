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