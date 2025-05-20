#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<random>
#include<math.h>

// 前向声明
class Road;
enum class TrafficLightState;
class TrafficLight;
class Vehicle
{
protected:
    int id;                   // ���� ID
    int speed;                // �����ٶ�
    int position;             // ����λ��
    int maxSpeed;             // ��������ٶ�
    int acceleration;         // �������ٶ�
    bool isStopped;           // �����Ƿ�ֹͣ
    std::string direction;    // ������ʻ����
    int lane;                 // �������ڳ���
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
        isStopped=(s == 0); // 如果速度为0则停止，否则行驶中
        direction=dir;
        lane=ln; 
    }

    // ��ȡ���� ID
    virtual int getId() 
    {
        return id;
    }

    // ��ȡ������ǰ�ٶ�
    virtual int getSpeed() 
    {
        return speed;
    }

    // ��ȡ������ǰλ��
    virtual int getPosition()
    {
        return position;
    }

    // ��ȡ��������ٶ�
    virtual int getMaxSpeed()
    {
        return maxSpeed;
    }

    // ��ȡ�������ٶ�
    virtual int getAcceleration()
    {
        return acceleration;
    }

    // ��ȡ������ʻ����
    virtual std::string getDirection()
    {
        return direction;
    }

    // ��ȡ�������ڳ���
    virtual int getLane()
    {
        return lane;
    }

    // �жϳ����Ƿ�ֹͣ
    virtual bool getIsStopped()
    {
        return isStopped;
    }

    // ���ó����ٶ�
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

    // ���ó���λ��
    virtual void setPosition(int newPosition) 
    {
        position = newPosition;
    }

    // ���ó�������ٶ�
    virtual void setMaxSpeed(int newMaxSpeed) 
    {
        maxSpeed = newMaxSpeed;
    }

    // ���ó������ٶ�
    virtual void setAcceleration(int newAcceleration) 
    {
        acceleration = newAcceleration;
    }

    // ���ó�����ʻ����
    virtual void setDirection(const std::string& newDirection)
    {
        direction = newDirection;
    }

    // ���ó������ڳ���
    virtual void setLane(int newLane)
    {
        lane = newLane;
    }

    // ��������
    virtual void accelerate()=0; 
    
    // ��������
    virtual void decelerate() 
    {
        setSpeed(speed - acceleration);
    }

    // ����ֹͣ
    virtual void stop() 
    {
        isStopped = true;
        speed = 0;
    }

    // ��������
    virtual void start() 
    {
        isStopped = false;
    }

    // �����ƶ�
    virtual void move()=0; 
    
};

//������Car��-���ٿ�-���
class Car : public Vehicle 
{
public:
    //���캯��
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
    //���캯��
    Car(int i, int s,int pos,int maxSpd = 100, int accel = 10, const std::string& dir = "forward",int ln=0)
    {
        id=i;
        speed=s;
        position=pos;
        maxSpeed=maxSpd;
        acceleration=accel;
        isStopped=(s == 0); // 如果速度为0则停止，否则行驶中
        direction=dir;
        lane=ln; 
    }

    //�γ�����
    void accelerate()
    {
        if(!getIsStopped())
        {
            //�γ�����ϵ��
            setSpeed(speed+acceleration*1.2);
        }
    }

    //�γ��ƶ�
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

//������Truck��-������-�����
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
        isStopped=(s == 0); // 如果速度为0则停止，否则行驶中
        direction=dir;
        lane=ln; 
    }

    //�������ٸ���
    void accelerate()
    {
        if(!getIsStopped())
        {
            setSpeed(speed+acceleration*0.8);   
        }
    }

    //�����ƶ����������Դ�
    void move() 
    {
        //�����ٶȽϵ�ʱ�ƶ�������٣�ģ�⿨������
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

//������Bus��-�̶�վ��-�����е�
class Bus: public Vehicle
{
private:
    // ���վ����
    int MAX_STOPS = 10;
    // ������վ������  
    int busStops[MAX_STOPS];
    // ʵ��վ������          
    int stopCount;
    // ��ǰĿ��վ������                    
    int currentStopIndex;             
    
public:
    // ���캯�� - ʹ�������ʼ��վ��
    Bus(int id, int lane, const int stops[], int count) : Vehicle(id, 0, 0, 25, 1.5, "forward", lane),currentStopIndex(0) 
    {
        // ����վ�����ݣ�ȷ���������������
        stopCount = (count < MAX_STOPS) ? count : MAX_STOPS;
        // ����վ������
        for (int i = 0; i < stopCount; i++) 
        {
            busStops[i] = stops[i];
        }
    }

    // ��д�ƶ����� - ����������վ��ͣ��
    void move() 
    {
        if (!getIsStopped()) 
        {
            // ����Ƿ�ӽ���һվ
            if (currentStopIndex < stopCount &&abs(getPosition() - busStops[currentStopIndex]) < 3) 
            {
                // ����վ�㣬ͣ��
                stop();
                cout << "Bus " << getId() << " stopped at station." << endl;
                
                // ������һ��վ��
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

//������EmergencyVehicle��-��������-����ͨ��-���ٿ�
class EmergencyVehicle : public Vehicle 
{
private:
    bool useAlarm;                      // ����������״̬
    int detectionRange;                 // ��ͨ�Ƽ�ⷶΧ���ף�
    static double ALARM_ACC;      // 警报模式加速系数
    static double NORMAL_ACC;     // 普通模式加速系数

    //���ǰ����ƣ�����������λ�ã�δ�ҵ�����-1��
    int detectRedLight()
    {
        // �ҵ�����ĺ��
        int closestRed = -1;
        int minDistance = detectionRange;
        for (int i = 0; i < Road::getLightCount();i++) 
        {
            TrafficLight& light = Road::getTrafficLight(i);
            int lightPos = light.getPosition();

            // ������صľ������
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

    // ǿ�����ǰ����ƣ����޾���ģʽ�£�
    void clearRedLight(int lightPos) 
    {
        for (int i = 0; i < Road::getLightCount();i++) 
        {
            TrafficLight& light = Road::getTrafficLight(i);
            if (light.getPosition() == lightPos && light.getState() == TrafficLightState::RED) 
            {
                light.setState(TrafficLightState::GREEN);
                cout << "�������� " << getId() 
                     << " ǿ�ƿ����̵ƣ�λ�ã�" << lightPos << ")\n";
            }
        }
    }
    
    // ������ͨ���߼�
    void handleTrafficLights() 
    {
        // ����ģʽ�£����ǰ����Ʋ�ǿ���̵�
        if (!useAlarm) 
        {
            return;
        }
        // ����ģʽ�£����ǰ����Ʋ�����
        int redLightPos = detectRedLight();
        if (redLightPos != -1) 
        {
            clearRedLight(redLightPos);
            // ǿ������ǰ��3����Ϊ�̵�
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
    //���캯��
   EmergencyVehicle(int id, int speed, int pos, int maxSpd = 140, int accel = 20,std::string& dir = "forward", int ln = 0, bool alarm = true): Vehicle(id, speed, pos, maxSpd, accel, dir, ln),useAlarm(alarm), detectionRange(5) 
    {
        //����Ĭ������ٶ�
        if (maxSpd <= 0)
        {
            //����Ĭ������ٶ�
            setMaxSpeed(140);
        }

        //����Ĭ�ϼ��ٶ�
        if (accel <= 0)
        {
            //����Ĭ�ϼ��ٶ�
            setAcceleration(20);
        }

        // ȷ����ʼ״̬Ϊ����
        start(); 
    }

    // ��д���ٷ���
    void accelerate() override {
        double accFactor = useAlarm ? ALARM_ACC : NORMAL_ACC;
        int newSpeed = speed + static_cast<int>(acceleration * accFactor);
        setSpeed(std::min(newSpeed, maxSpeed));
    }

    // 重写移动方法
    void move() override {
        handleTrafficLights();
        // 执行移动
        if (!isStopped) {
            if (direction == "forward") {
                position += speed;
            } else if (direction == "backward") {
                position -= speed;
            }
        }
    }
    
    // 执行移动操作
    void executeMovement() {
        if (!isStopped) {
            if (direction == "forward") {
                position += speed;
            } else if (direction == "backward") {
                position -= speed;
            }
        }
    }
    
    // 维持优先权
    void maintainPriority() {
        // 紧急车辆优先通行的实现
        // 在实际应用中，可以添加更复杂的逻辑
    }
};
