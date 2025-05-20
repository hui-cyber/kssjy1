#include<iostream>
using namespace std;
#include<string>
#include<random>
#include<math.h>
#define MAX_VEHICLES 100;         // 最大车辆数
#define MAX_LIGHTS 10;           // 最大交通信号灯数
#define MAX_ENTRANCES 5;        // 最大入口数
#define MAX_EXITS 5;            // 最大出口数

//定义天气状况枚举类型
enum class WeatherCondition 
{
    //晴天
    CLEAR,
    //雨天 
    RAINY,
    //雪天   
    SNOWY,
    //大雾
    FOGGY,
    //雷雨 
    STORMY
};

class Vehicle
{
protected:
    int id;                   // 车辆 ID
    int speed;                // 车辆速度
    int position;             // 车辆位置
    int maxSpeed;             // 车辆最大速度
    int acceleration;         // 车辆加速度
    bool isStopped;           // 车辆是否停止
    string direction;    // 车辆行驶方向
    int lane;                 // 车辆所在车道
public:
    Vehicle()
    {
        id=0;
        speed=0;
        position=0;
        maxSpeed=0;
        acceleration=0;
        isStopped=true;
        direction="forward";
        lane=0;
    }

    Vehicle(int i, int s,int pos,int maxSpd , int accel , const std::string& dir = "forward",int ln)
    {
        id=i;
        speed=s;
        position=pos;
        maxSpeed=maxSpd;
        acceleration=accel;
        isStopped=true||false;
        direction=dir;
        lane=ln; 
    }

    // 获取车辆 ID
    virtual int getId() 
    {
        return id;
    }

    // 获取车辆当前速度
    virtual int getSpeed() 
    {
        return speed;
    }

    // 获取车辆当前位置
    virtual int getPosition()
    {
        return position;
    }

    // 获取车辆最大速度
    virtual int getMaxSpeed()
    {
        return maxSpeed;
    }

    // 获取车辆加速度
    virtual int getAcceleration()
    {
        return acceleration;
    }

    // 获取车辆行驶方向
    virtual std::string getDirection()
    {
        return direction;
    }

    // 获取车辆所在车道
    virtual int getLane()
    {
        return lane;
    }

    // 判断车辆是否停止
    virtual bool getIsStopped()
    {
        return isStopped;
    }

    // 设置车辆速度
    virtual void setSpeed(int newSpeed) 
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
    virtual void setPosition(int newPosition) 
    {
        position = newPosition;
    }

    // 设置车辆最大速度
    virtual void setMaxSpeed(int newMaxSpeed) 
    {
        maxSpeed = newMaxSpeed;
    }

    // 设置车辆加速度
    virtual void setAcceleration(int newAcceleration) 
    {
        acceleration = newAcceleration;
    }

    // 设置车辆行驶方向
    virtual void setDirection(const std::string& newDirection)
    {
        direction = newDirection;
    }

    // 设置车辆所在车道
    virtual void setLane(int newLane)
    {
        lane = newLane;
    }

    // 车辆加速
    virtual void accelerate()=0; 
    
    // 车辆减速
    virtual void decelerate() 
    {
        setSpeed(speed - acceleration);
    }

    // 车辆停止
    virtual void stop() 
    {
        isStopped = true;
        speed = 0;
    }

    // 车辆启动
    virtual void start() 
    {
        isStopped = false;
    }

    // 车辆移动
    virtual void move()=0; 
    
};

//派生类Car类-加速快-灵活
class Car : public Vehicle 
{
public:
    //构造函数
    Car()
    {
        id=0;
        speed=0;
        position=0;
        maxSpeed=0;
        acceleration=0;
        isStopped=true;
        direction="forward";
        lane=0;
    }
    //构造函数
    Car(int i, int s,int pos,int maxSpd = 100, int accel = 10, const std::string& dir = "forward",int ln=0)
    {
        id=i;
        speed=s;
        position=pos;
        maxSpeed=maxSpd;
        acceleration=accel;
        isStopped=true||false;
        direction=dir;
        lane=ln; 
    }

    //轿车加速
    void accelerate()
    {
        if(!getIsStopped())
        {
            //轿车加速系数
            setSpeed(speed+acceleration*1.2);
        }
    }

    //轿车移动
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

//派生类Truck类-加速慢-不灵活
class Truck: public Vehicle
{
public:
    Truck()
    {
        id=0;        
        speed=0;                                    
        position=0;
        maxSpeed=0;
        acceleration=0;
        isStopped=true;
        direction="forward";
        lane=0;
    }
    Truck(int i, int s,int pos,int maxSpd = 200, int accel = 20, const std::string& dir = "forward",int ln)
    {
        id=i;
        speed=s;
        position=pos;
        maxSpeed=maxSpd;
        acceleration=accel;
        isStopped=true||false;
        direction=dir;
        lane=ln; 
    }

    //卡车加速更慢
    void accelerate()
    {
        if(!getIsStopped())
        {
            setSpeed(speed+acceleration*0.8);   
        }
    }

    //卡车移动，卡车惯性大
    void move() 
    {
        //卡车速度较低时移动距离减少，模拟卡车惯性
        if(!isStopped)
        {
            if(speed<5)
            {
                setPosition(getPosition()+speed*0.9);
            }
        }
        else
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
        
        
    }
};

//派生类Bus类-固定站点-加速中等
class Bus: public Vehicle
{
private:
    // 最大站点数
    int MAX_STOPS = 10;
    // 公交车站点数组  
    int busStops[MAX_STOPS];
    // 实际站点数量          
    int stopCount;
    // 当前目标站点索引                    
    int currentStopIndex;             
    
public:
    // 构造函数 - 使用数组初始化站点
    Bus(int id, int lane, const int stops[], int count) : Vehicle(id, 0, 0, 25, 1.5, "forward", lane),currentStopIndex(0) 
    {
        // 复制站点数据，确保不超过最大容量
        stopCount = (count < MAX_STOPS) ? count : MAX_STOPS;
        // 复制站点数据
        for (int i = 0; i < stopCount; i++) 
        {
            busStops[i] = stops[i];
        }
    }

    // 重写移动方法 - 公交车会在站点停留
    void move() 
    {
        if (!getIsStopped()) 
        {
            // 检查是否接近下一站
            if (currentStopIndex < stopCount &&abs(getPosition() - busStops[currentStopIndex]) < 3) 
            {
                // 到达站点，停车
                stop();
                cout << "Bus " << getId() << " stopped at station." << endl;
                
                // 更新下一个站点
                currentStopIndex = (currentStopIndex + 1) % stopCount;
            } 
            else 
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
        }
    }
};

//派生类EmergencyVehicle类-紧急车辆-优先通行-加速快
class EmergencyVehicle : public Vehicle 
{
private:
    bool useAlarm;                      // 警报器启用状态
    int detectionRange;                 // 交通灯检测范围（米）
    static double ALARM_ACC=2.0;      // 警报模式加速系数
    static double NORMAL_ACC=1.5;     // 普通模式加速系数

    //检测前方红灯（返回最近红灯位置，未找到返回-1）
    int detectRedLight()
    {
        // 找到最近的红灯
        int closestRed = -1;
        int minDistance = detectionRange;
        for (int i = 0; i < Road::getLightCount();i++) 
        {
            TrafficLight& light = Road::getTrafficLight(i);
            int lightPos = light.getPosition();

            // 方向相关的距离计算
            int distance = (direction == "forward") ? 
                (lightPos - position) : 
                (position - lightPos);

                if (distance > 0 && distance <= minDistance) 
                {
                    if (light.getState() == TrafficLightState::RED) 
                    {
                        closestRed = lightPos;
                        minDistance = distance;
                    }
                }
        }
        return closestRed;
    }

    // 强制清除前方红灯（仅限警报模式下）
    void clearRedLight(int lightPos) 
    {
        for (int i = 0; i < Road::getLightCount();i++) 
        {
            TrafficLight& light = Road::getTrafficLight(i);
            if (light.getPosition() == lightPos && light.getState() == TrafficLightState::RED) 
            {
                light.setState(TrafficLightState::GREEN);
                cout << "紧急车辆 " << getId() 
                     << " 强制开启绿灯（位置：" << lightPos << ")\n";
            }
        }
    }
    
    // 处理交通灯逻辑
    void handleTrafficLights() 
    {
        // 警报模式下，检测前方红灯并强制绿灯
        if (!useAlarm) 
        {
            return;
        }
        // 正常模式下，检测前方红灯并处理
        int redLightPos = detectRedLight();
        if (redLightPos != -1) 
        {
            clearRedLight(redLightPos);
            // 强制设置前方3米内为绿灯
            for(int i = 0; i < Road::getLightCount();i++) 
            {
                TrafficLight& light = Road::getTrafficLight(i);
                if(light.getPosition() > position && light.getPosition() < position + 3) 
                {
                    light.setState(TrafficLightState::GREEN);
                }
            }
        }
    }
public:
    //构造函数
   EmergencyVehicle(int id, int speed, int pos, int maxSpd = 140, int accel = 20,std::string& dir = "forward", int ln = 0, bool alarm = true): Vehicle(id, speed, pos, maxSpd, accel, dir, ln),useAlarm(alarm), detectionRange(5) 
    {
        //设置默认最大速度
        if (maxSpd <= 0)
        {
            //设置默认最大速度
            setMaxSpeed(140);
        }

        //设置默认加速度
        if (accel <= 0)
        {
            //设置默认加速度
            setAcceleration(20);
        }

        // 确保初始状态为启动
        start(); 
    }

    // 重写加速方法
    void accelerate() override {
        double accFactor = useAlarm ? ALARM_ACC : NORMAL_ACC;
        int newSpeed = speed + static_cast<int>(acceleration * accFactor);
        setSpeed(std::min(newSpeed, maxSpeed));
    }

    // 重写移动方法
    void move() override {
        handleTrafficLights();
        executeMovement();
        maintainPriority();
    }
};

enum class TrafficLightState 
{
    GREEN,               // 绿灯
    YELLOW,              // 黄灯 
    RED,                 // 红灯
    PEDESTRIAN_GREEN,    // 行人绿灯
    PEDESTRIAN_RED       // 行人信号灯处于红灯状态，意味着行人此时不可以通行
};

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
    // 构造函数
    TrafficLight()
    {
        position=0; 
        state=TrafficLightState::RED;     // 初始状态为红灯
        cycleDuration=0;           
        currentTime=0; 
        yellowDuration=0; 
        hasPedestrianSignal=false;        // 是否有行人信号
    } 

    TrafficLight(int pos, int duration, int yellowDur = 3, bool hasPed = false)
    {
        position=pos; 
        state=TrafficLightState::RED;     // 初始状态为红灯
        cycleDuration=duration;           
        currentTime=0; 
        yellowDuration=yellowDur; 
        hasPedestrianSignal=hasPed;        // 是否有行人信号
    }

    // 获取信号灯位置
    int getgetPosition()
    {
        return position;
    }

    //获取信号灯周期
    int getCycleDuration()
    {
        return cycleDuration;
    }

    // 获取黄灯持续时间
    int getYellowDuration()
    {
        return yellowDuration;
    }

    // 更新信号灯状态
    void update() 
    {
        // 每次调用 update 方法时，当前时间加 1，模拟时间流逝
        currentTime++;
        switch (state)
        {
            // 状态为绿灯
            case TrafficLightState::GREEN:
                // 检查是否达到绿灯持续时间的末尾（减去黄灯持续时间）
                if (currentTime >= cycleDuration - yellowDuration) 
                {
                    //信号灯状态为黄灯
                    state = TrafficLightState::YELLOW;
                    currentTime = 0;
                }
                break;

            // 状态为黄灯
            case TrafficLightState::YELLOW:
                // 检查是否达到黄灯持续时间的末尾
                if (currentTime >= yellowDuration) 
                {   
                    //信号灯状态为红灯    
                    state = TrafficLightState::RED;
                    //检查是否有行人信号灯
                    if (hasPedestrianSignal) 
                    {
                        // 行人信号灯变绿
                        state = TrafficLightState::PEDESTRIAN_GREEN;
                    }
                    currentTime = 0;
                }
                break;

            //状态为红灯
            case TrafficLightState::RED:
                // 检查是否有行人信号灯且行人信号灯状态为绿灯
                if (hasPedestrianSignal && state == TrafficLightState::PEDESTRIAN_GREEN) 
                {
                    // 检查是否达到行人绿灯持续时间的末尾
                    if (currentTime >= cycleDuration) 
                    {
                        // 如果达到末尾，将行人信号灯状态变为红灯
                        state = TrafficLightState::PEDESTRIAN_RED;
                        currentTime = 0;
                    }
                }

                else 
                {
                    // 如果没有行人信号灯或者行人信号灯不是绿灯
                    // 检查是否达到红灯持续时间的末尾
                    if (currentTime >= cycleDuration) 
                    {
                        state = TrafficLightState::GREEN;
                        currentTime = 0;
                    }
                }
                break;

            // 当前行人信号灯状态为绿灯
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
                return yellowDuration - currentTime;

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
    int length;                             //道路长度
    int numLanes;                           //道路车道数
    int vehicleCount;                       // 当前车辆数量
    int lightCount;                         // 当前交通信号灯数量
    int entrances[MAX_ENTRANCES];           // 入口位置数组
    int entranceCount;                      // 入口数量
    int exits[MAX_EXITS];                   // 出口位置数组
    int exitCount;                          // 出口数量
    Vehicle *vehicles[MAX_VEHICLES];          //使用基类指针
    TrafficLight trafficLights[MAX_LIGHTS];   //交通信号灯数组，对象数组
    WeatherCondition currentWeather;
    int weatherIntensity;
public:
    //构造函数
    Road(int len,int num,int vc,int lc,int ec,int ex,int *entr,int *exit,int we):currentWeather(CLEAR)
    {
        length=len;
        numLanes=num;
        vehicleCount=vc;
        lightCount=lc;
        entranceCount=ec;
        exitCount=ex;
        weatherIntensity=we;
        //确保不超过传入的入口数量并且不超过类预设的最大入口数
        for(int i=0;i<entranceCount&&i<MAX_ENTRANCES;i++)
        {
            entrances[i]=entr[i];
        }
        //确保不超过传入的出口数量并且不超过类预设的最大出口数
        for(int i=0;i<exitCount&&i<MAX_EXITS;i++)
        {
            exits[i]=exit[i];
        }
    }

    //添加车辆，接受基类指针
    bool addVehicle(Vehicle* obj)
    {
        //当前道路上的车辆数量大于类中定义的最大车辆数（MAX_VEHICLE）||车辆要进入的车道编号大于等于道路范围
        if(vehicleCount>=MAX_VEHICLES||obj->getLane()>=numLanes)
        {
            return false;
        }

        //加入新车辆,把传入的对象obj复制到vehicles数组
        else
        {
            //存储指针
            vehicles[vehicleCount++]=obj;
            return true;
        }
    }

    //添加交通信号灯
    bool addTrafficLight(TrafficLight& light)
    {
        if(lightCount>=MAX_LIGHTS)
        {
            return false;
        }
        else
        {
            trafficLights[lightCount++]=light;
            return true;
        }
    }

    //获取道路长度
    int getLength()
    {
        return length;
    }

    //获取道路车道数
    int getNumLanes()
    {
        return numLanes;
    }

    //获取当前车辆数量
    int getVehicleCount()
    {
        return vehicleCount;
    }

    //获取当前交通信号灯数量
    int getLightCount()
    {
        return lightCount;
    }

    //获取入口位置数组
    int* getEntrances()
    {
        return entrances;
    }

    //获取入口数量
    int getEntranceCount()
    {
        return entranceCount;
    }

    //获取出口位置数组
    int* getExits()
    {
        return exits;
    }

    //获取出口数量
    int getExitCount()
    {
        return exitCount;
    }

    //更新道路状态
    void update()
    {
        //更新所有交通信号灯
        for(int i=0;i<lightCount;i++)
        {
            trafficLights[i].update();
        }

        //更新所有车辆
        for(int i=0;i<vehicleCount;i++)
        {
            for(int j=0;j<lightCount;j++)
            {
                //车辆超过信号灯位置并且信号灯为红灯
                if(vehicles[i]->getPosition()>=trafficLights[j].getPosition()&&trafficLights[j].getState()==TrafficLightState::RED)
                {
                    //车辆停止
                    vehicles[i]->stop();
                    break;
                }
                else
                {
                    //允许车辆继续前进
                    vehicles[i]->start();
                }
            }

            //避开障碍
            for(int j=0;j<vehicleCount;j++)
            {
                //避免车辆与自己进行距离检查
                if(i==j)
                {
                    continue;
                }
                //两辆车在同一个车道，前车判断，安全距离小于5时触发减速
                if(vehicles[i]->getLane() == vehicles[j]->getLane() &&vehicles[i]->getPosition() < vehicles[j]->getPosition() &&vehicles[j]->getPosition() - vehicles[i]->getPosition() < 5)
                {
                    //后车执行减速
                    vehicles[i]->decelerate();
                    break;
                }

                //移动车辆
                vehicles[i]->accelerate();
                vehicles[i]->move();

                //检查车辆是否到达出口
                for(int j=0;j<exitCount;j++)
                {
                    if(vehicles[i]->getPosition()>=exits[j])
                    {
                        //移除车辆
                        for(int k=i;k<vehicleCount-1;k++)
                        {
                            vehicles[k]=vehicles[k+1];
                        }
                        --vehicleCount;
                        --i;
                        break;
                    }
                }
            }   
        }
    }

    void display()
    {
        //显示道路信息
        cout<<"Road Status:"<<endl;               
        cout<<"Length:"<<length;                 //道路长度
        cout<<",Lanes:"<<numLanes<<endl;         //道路车道数
        cout<<"Vehicles:"<<vehicleCount<<endl;   //当前车辆数量

        //显示车辆信息
        for(int i=0;i<vehicleCount;i++)
        {
            cout<<"Vehicle"<<vehicles[i].getId()                  //车辆编号
                <<"at position"<<vehicles[i].getPosition()        //车辆位置
                <<",lane"<<vehicles[i].getLane()                  //车辆所在车道
                <<",speed"<<vehicles[i].getSpeed()<<endl;         //车辆速度
        }
        
        //显示交通信号灯信息
        cout<<"Traffic Lights:"<<lightCount<<endl;
        for(int i=0;i<lightCount;i++)
        {
            //交通信号灯位置
            cout<<"Light at position"<<trafficLights[i].getPosition()  
                <<"is"; 
            //交通信号灯状态
            switch(trafficLights[i].getState())
            {
                case TrafficLightState::GREEN:
                    cout<<"GREEN"<<endl;
                    break;
                case TrafficLightState::YELLOW:
                    cout<<"YELLOW"<<endl;
                    break;
                case TrafficLightState::RED:
                    cout<<"RED"<<endl;
                    break;
                default:
                    cout<<"OTHER"<<endl;
            }

        }
            
    }
};

//定义天气状况枚举类型
enum class WeatherCondition 
{
    //晴天
    CLEAR,
    //雨天 
    RAINY,
    //雪天   
    SNOWY,
    //大雾
    FOGGY,
    //雷雨 
    STORMY
};

//定义天气类
class Weather 
{
private:
    WeatherCondition currentCondition;      // 当前天气状况
    int intensity;                          // 天气强度
    double visibility;                      // 能见度   
    double friction;                        // 摩擦系数
    int timeStep;                           // 时间步计数器

    // 使用确定性算法更新天气
    void updateWeatherBasedOnTime() 
    {
        // 使用时间步生成伪随机数
        int pseudoRandom = (timeStep * 1103515245 + 12345) % 32768;

        // 基于伪随机数选择天气类型
        int conditionIndex = pseudoRandom % 5;
        currentCondition = static_cast<WeatherCondition>(conditionIndex);
        
        // 计算天气强度（基于时间步的复杂函数）
        intensity = ((pseudoRandom / 5) % 100);
        
        // 根据天气类型调整强度范围
        switch (currentCondition) {
            case WeatherCondition::CLEAR:
                intensity = 0;
                break;
            case WeatherCondition::RAINY:
                intensity = 30 + (intensity % 50);
                break;
            case WeatherCondition::SNOWY:
                intensity = 20 + (intensity % 50);
                break;
            case WeatherCondition::FOGGY:
                intensity = 40 + (intensity % 50);
                break;
            case WeatherCondition::STORMY:
                intensity = 60 + (intensity % 40);
                break;
        }
        
        updateWeatherParameters();
    }
    
     // 根据天气类型和强度更新相关参数
    void updateWeatherParameters() 
    {
        switch (currentCondition) 
        {
            //晴天
            case WeatherCondition::CLEAR:
                visibility = 1.0;
                friction = 1.0;
                break;
            //雨天
            case WeatherCondition::RAINY:
                visibility = 1.0 - (intensity / 200.0);
                friction = 0.9 - (intensity / 1000.0);
                break;
            //雪天
            case WeatherCondition::SNOWY:
                visibility = 1.0 - (intensity / 150.0);
                friction = 0.8 - (intensity / 200.0);
                break;
            //大雾
            case WeatherCondition::FOGGY:
                visibility = 0.8 - (intensity / 250.0);
                friction = 0.95;
                break;
            //雷雨
            case WeatherCondition::STORMY:
                visibility = 0.6 - (intensity / 300.0);
                friction = 0.75 - (intensity / 400.0);
                break;
        }
    }
public:
    // 构造函数
    Weather() : timeStep(0) 
    {
        // 使用确定性算法初始化天气
        updateWeatherBasedOnTime();
    }
    
    void update() 
    {
        timeStep++;
        // 每20个时间步更新一次天气（约5%概率变化）
        if (timeStep % 20 == 0) 
        {
            updateWeatherBasedOnTime();
        }
    }

    // 获取天气状态描述
    char* getCondition() 
    {
        switch (currentCondition) 
        {
            case WeatherCondition::CLEAR: return "Clear";
            case WeatherCondition::RAINY: return "Rainy";
            case WeatherCondition::SNOWY: return "Snowy";
            case WeatherCondition::FOGGY: return "Foggy";
            case WeatherCondition::STORMY: return "Stormy";
            default: return "Unknown";
        }
    }

    // 获取天气强度
    int getIntensity() 
    {
        return intensity;
    }
    
    // 获取能见度系数
    double getVisibilityFactor() 
    {
        return visibility;
    }
    
    // 获取路面摩擦系数
    double getFrictionFactor() 
    {
        return friction;
    }
};