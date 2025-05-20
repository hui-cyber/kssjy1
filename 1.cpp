#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<random>
class Vehicle
{
private:
    int id;                   // 什么id
    int speed;                // �����ٶ�
    int position;             // ����λ��
    int maxSpeed;             // ��������ٶ�
    int acceleration;         // �������ٶ�
    bool isStopped;           // �����Ƿ�ֹͣ
    std::string direction;    // ������ʻ����
    int lane;                 // �������ڳ���
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

    // ��ȡ���� ID
    int getId() 
    {
        return id;
    }

    // ��ȡ������ǰ�ٶ�
    int getSpeed() 
    {
        return speed;
    }

    // ��ȡ������ǰλ��
    int getPosition()
    {
        return position;
    }

    // ��ȡ��������ٶ�
    int getMaxSpeed()
    {
        return maxSpeed;
    }

    // ��ȡ�������ٶ�
    int getAcceleration()
    {
        return acceleration;
    }

    // ��ȡ������ʻ����
    std::string getDirection()
    {
        return direction;
    }

    // �жϳ����Ƿ�ֹͣ
    bool getIsStopped()
    {
        return isStopped;
    }

    // ���ó����ٶ�
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

    // ���ó���λ��
    void setPosition(int newPosition) 
    {
        position = newPosition;
    }

    // ���ó�������ٶ�
    void setMaxSpeed(int newMaxSpeed) 
    {
        maxSpeed = newMaxSpeed;
    }

    // ���ó������ٶ�
    void setAcceleration(int newAcceleration) 
    {
        acceleration = newAcceleration;
    }

    // ���ó�����ʻ����
    void setDirection(const std::string& newDirection)
    {
        direction = newDirection;
    }

    // ���ó������ڳ���
    void setLane(int newLane)
    {
        lane = newLane;
    }

    // ��������
    void accelerate() 
    {
        if (!isStopped) 
        {
            setSpeed(speed + acceleration);
        }
    }

    // ��������
    void decelerate() 
    {
        setSpeed(speed - acceleration);
    }

    // ����ֹͣ
    void stop() 
    {
        isStopped = true;
        speed = 0;
    }

    // ��������
    void start() 
    {
        isStopped = false;
    }

    // �����ƶ�
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

// ���彻ͨ�źŵ�״̬ö��
enum class TrafficLightState {
    GREEN,               // �̵�
    YELLOW,              // �Ƶ� 
    RED,                 // ���
    PEDESTRIAN_GREEN,    // �����̵�
    PEDESTRIAN_RED       // �����źŵƴ��ں��״̬����ζ�����˴�ʱ������ͨ��
};

// ���彻ͨ�źŵ���
class TrafficLight
{
private:
    int position;                // �źŵ�λ��
    TrafficLightState state;     // �źŵ�״̬
    int cycleDuration;           // �źŵ�����
    int currentTime;             // �źŵƵ�ǰʱ��
    int yellowDuration;          // �ƵƳ���ʱ��
    bool hasPedestrianSignal;    // �Ƿ��������ź�
public:
    TrafficLight(int pos, int duration, int yellowDur = 3, bool hasPed = false)
    {
        position=pos; 
        state=TrafficLightState::RED;     // ��ʼ״̬Ϊ���
        cycleDuration=duration;           
        currentTime=0; 
        yellowDuration=yellowDur; 
        hasPedestrianSignal=hasPed;        // �Ƿ��������ź�
    }
        

    // �����źŵ�״̬
    void update() 
    {
        currentTime++;
        switch (state)
        {
            // �̵�
            case TrafficLightState::GREEN:
                if (currentTime >= cycleDuration - yellowDuration) 
                {
                    state = TrafficLightState::YELLOW;
                    currentTime = 0;
                }
                break;

            // �Ƶ�
            case TrafficLightState::YELLOW:
                if (currentTime >= yellowDuration) 
                {
                    state = TrafficLightState::RED;
                    if (hasPedestrianSignal) 
                    {
                        // �����źŵƱ���
                        state = TrafficLightState::PEDESTRIAN_GREEN;
                    }
                    currentTime = 0;
                }
                break;

            // ���
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

            // �����̵�
            case TrafficLightState::PEDESTRIAN_GREEN:
                if (currentTime >= cycleDuration) 
                {
                    state = TrafficLightState::PEDESTRIAN_RED;
                    currentTime = 0;
                }
                break;

            // �����źŵƴ��ں��״̬����ζ�����˴�ʱ������ͨ��
            case TrafficLightState::PEDESTRIAN_RED:
                if (currentTime >= cycleDuration) 
                {
                    state = TrafficLightState::GREEN;
                    currentTime = 0;
                }
                break;
        }
    }
    // ��ȡ�źŵ�״̬
    TrafficLightState getState()  
    {
        return state;
    }
    // ��ȡ�źŵ�λ��
    int getPosition() 
    {
        return position;
    }
    // ��ȡ��ǰ����ʱ
    int getCountdown() 
    {
        switch (state) 
        {
            // �̵Ƶ���ʱ
            case TrafficLightState::GREEN:            
               return cycleDuration - yellowDuration - currentTime;

            // �ƵƵ���ʱ
            case TrafficLightState::YELLOW:

            // ��Ƶ���ʱ
            case TrafficLightState::RED:
                if (hasPedestrianSignal && state == TrafficLightState::PEDESTRIAN_GREEN) 
                {
                    return cycleDuration - currentTime;
                }

            // �����̵Ƶ���ʱ
            case TrafficLightState::PEDESTRIAN_GREEN:
                return cycleDuration - currentTime;

            // �����źŵƴ��ں��״̬����ζ�����˴�ʱ������ͨ��
            case TrafficLightState::PEDESTRIAN_RED:
                return cycleDuration - currentTime;

            // ����״̬
            default:
                return 0;
        }
    }

    // �ж��Ƿ��������źŵ�
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
                // ����ʻ����·
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
