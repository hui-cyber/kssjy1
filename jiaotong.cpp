#include<iostream>
using namespace std;
#include<string>
#include<random>
#include<math.h>
#define MAX_VEHICLES 100;         // �������
#define MAX_LIGHTS 10;           // ���ͨ�źŵ���
#define MAX_ENTRANCES 5;        // ��������
#define MAX_EXITS 5;            // ��������

//��������״��ö������
enum class WeatherCondition 
{
    //����
    CLEAR,
    //���� 
    RAINY,
    //ѩ��   
    SNOWY,
    //����
    FOGGY,
    //���� 
    STORMY
};

class Vehicle
{
protected:
    int id;                   // ���� ID
    int speed;                // �����ٶ�
    int position;             // ����λ��
    int maxSpeed;             // ��������ٶ�
    int acceleration;         // �������ٶ�
    bool isStopped;           // �����Ƿ�ֹͣ
    string direction;    // ������ʻ����
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
        isStopped=true||false;
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
        isStopped=true||false;
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
        isStopped=true||false;
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
    static double ALARM_ACC=2.0;      // ����ģʽ����ϵ��
    static double NORMAL_ACC=1.5;     // ��ͨģʽ����ϵ��

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
    
    // ����ͨ���߼�
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

    // ��д�ƶ�����
    void move() override {
        handleTrafficLights();
        executeMovement();
        maintainPriority();
    }
};

enum class TrafficLightState 
{
    GREEN,               // �̵�
    YELLOW,              // �Ƶ� 
    RED,                 // ���
    PEDESTRIAN_GREEN,    // �����̵�
    PEDESTRIAN_RED       // �����źŵƴ��ں��״̬����ζ�����˴�ʱ������ͨ��
};

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
    // ���캯��
    TrafficLight()
    {
        position=0; 
        state=TrafficLightState::RED;     // ��ʼ״̬Ϊ���
        cycleDuration=0;           
        currentTime=0; 
        yellowDuration=0; 
        hasPedestrianSignal=false;        // �Ƿ��������ź�
    } 

    TrafficLight(int pos, int duration, int yellowDur = 3, bool hasPed = false)
    {
        position=pos; 
        state=TrafficLightState::RED;     // ��ʼ״̬Ϊ���
        cycleDuration=duration;           
        currentTime=0; 
        yellowDuration=yellowDur; 
        hasPedestrianSignal=hasPed;        // �Ƿ��������ź�
    }

    // ��ȡ�źŵ�λ��
    int getgetPosition()
    {
        return position;
    }

    //��ȡ�źŵ�����
    int getCycleDuration()
    {
        return cycleDuration;
    }

    // ��ȡ�ƵƳ���ʱ��
    int getYellowDuration()
    {
        return yellowDuration;
    }

    // �����źŵ�״̬
    void update() 
    {
        // ÿ�ε��� update ����ʱ����ǰʱ��� 1��ģ��ʱ������
        currentTime++;
        switch (state)
        {
            // ״̬Ϊ�̵�
            case TrafficLightState::GREEN:
                // ����Ƿ�ﵽ�̵Ƴ���ʱ���ĩβ����ȥ�ƵƳ���ʱ�䣩
                if (currentTime >= cycleDuration - yellowDuration) 
                {
                    //�źŵ�״̬Ϊ�Ƶ�
                    state = TrafficLightState::YELLOW;
                    currentTime = 0;
                }
                break;

            // ״̬Ϊ�Ƶ�
            case TrafficLightState::YELLOW:
                // ����Ƿ�ﵽ�ƵƳ���ʱ���ĩβ
                if (currentTime >= yellowDuration) 
                {   
                    //�źŵ�״̬Ϊ���    
                    state = TrafficLightState::RED;
                    //����Ƿ��������źŵ�
                    if (hasPedestrianSignal) 
                    {
                        // �����źŵƱ���
                        state = TrafficLightState::PEDESTRIAN_GREEN;
                    }
                    currentTime = 0;
                }
                break;

            //״̬Ϊ���
            case TrafficLightState::RED:
                // ����Ƿ��������źŵ��������źŵ�״̬Ϊ�̵�
                if (hasPedestrianSignal && state == TrafficLightState::PEDESTRIAN_GREEN) 
                {
                    // ����Ƿ�ﵽ�����̵Ƴ���ʱ���ĩβ
                    if (currentTime >= cycleDuration) 
                    {
                        // ����ﵽĩβ���������źŵ�״̬��Ϊ���
                        state = TrafficLightState::PEDESTRIAN_RED;
                        currentTime = 0;
                    }
                }

                else 
                {
                    // ���û�������źŵƻ��������źŵƲ����̵�
                    // ����Ƿ�ﵽ��Ƴ���ʱ���ĩβ
                    if (currentTime >= cycleDuration) 
                    {
                        state = TrafficLightState::GREEN;
                        currentTime = 0;
                    }
                }
                break;

            // ��ǰ�����źŵ�״̬Ϊ�̵�
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
                return yellowDuration - currentTime;

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
    int length;                             //��·����
    int numLanes;                           //��·������
    int vehicleCount;                       // ��ǰ��������
    int lightCount;                         // ��ǰ��ͨ�źŵ�����
    int entrances[MAX_ENTRANCES];           // ���λ������
    int entranceCount;                      // �������
    int exits[MAX_EXITS];                   // ����λ������
    int exitCount;                          // ��������
    Vehicle *vehicles[MAX_VEHICLES];          //ʹ�û���ָ��
    TrafficLight trafficLights[MAX_LIGHTS];   //��ͨ�źŵ����飬��������
    WeatherCondition currentWeather;
    int weatherIntensity;
public:
    //���캯��
    Road(int len,int num,int vc,int lc,int ec,int ex,int *entr,int *exit,int we):currentWeather(CLEAR)
    {
        length=len;
        numLanes=num;
        vehicleCount=vc;
        lightCount=lc;
        entranceCount=ec;
        exitCount=ex;
        weatherIntensity=we;
        //ȷ�����������������������Ҳ�������Ԥ�����������
        for(int i=0;i<entranceCount&&i<MAX_ENTRANCES;i++)
        {
            entrances[i]=entr[i];
        }
        //ȷ������������ĳ����������Ҳ�������Ԥ�����������
        for(int i=0;i<exitCount&&i<MAX_EXITS;i++)
        {
            exits[i]=exit[i];
        }
    }

    //��ӳ��������ܻ���ָ��
    bool addVehicle(Vehicle* obj)
    {
        //��ǰ��·�ϵĳ��������������ж�������������MAX_VEHICLE��||����Ҫ����ĳ�����Ŵ��ڵ��ڵ�·��Χ
        if(vehicleCount>=MAX_VEHICLES||obj->getLane()>=numLanes)
        {
            return false;
        }

        //�����³���,�Ѵ���Ķ���obj���Ƶ�vehicles����
        else
        {
            //�洢ָ��
            vehicles[vehicleCount++]=obj;
            return true;
        }
    }

    //��ӽ�ͨ�źŵ�
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

    //��ȡ��·����
    int getLength()
    {
        return length;
    }

    //��ȡ��·������
    int getNumLanes()
    {
        return numLanes;
    }

    //��ȡ��ǰ��������
    int getVehicleCount()
    {
        return vehicleCount;
    }

    //��ȡ��ǰ��ͨ�źŵ�����
    int getLightCount()
    {
        return lightCount;
    }

    //��ȡ���λ������
    int* getEntrances()
    {
        return entrances;
    }

    //��ȡ�������
    int getEntranceCount()
    {
        return entranceCount;
    }

    //��ȡ����λ������
    int* getExits()
    {
        return exits;
    }

    //��ȡ��������
    int getExitCount()
    {
        return exitCount;
    }

    //���µ�·״̬
    void update()
    {
        //�������н�ͨ�źŵ�
        for(int i=0;i<lightCount;i++)
        {
            trafficLights[i].update();
        }

        //�������г���
        for(int i=0;i<vehicleCount;i++)
        {
            for(int j=0;j<lightCount;j++)
            {
                //���������źŵ�λ�ò����źŵ�Ϊ���
                if(vehicles[i]->getPosition()>=trafficLights[j].getPosition()&&trafficLights[j].getState()==TrafficLightState::RED)
                {
                    //����ֹͣ
                    vehicles[i]->stop();
                    break;
                }
                else
                {
                    //����������ǰ��
                    vehicles[i]->start();
                }
            }

            //�ܿ��ϰ�
            for(int j=0;j<vehicleCount;j++)
            {
                //���⳵�����Լ����о�����
                if(i==j)
                {
                    continue;
                }
                //��������ͬһ��������ǰ���жϣ���ȫ����С��5ʱ��������
                if(vehicles[i]->getLane() == vehicles[j]->getLane() &&vehicles[i]->getPosition() < vehicles[j]->getPosition() &&vehicles[j]->getPosition() - vehicles[i]->getPosition() < 5)
                {
                    //��ִ�м���
                    vehicles[i]->decelerate();
                    break;
                }

                //�ƶ�����
                vehicles[i]->accelerate();
                vehicles[i]->move();

                //��鳵���Ƿ񵽴����
                for(int j=0;j<exitCount;j++)
                {
                    if(vehicles[i]->getPosition()>=exits[j])
                    {
                        //�Ƴ�����
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
        //��ʾ��·��Ϣ
        cout<<"Road Status:"<<endl;               
        cout<<"Length:"<<length;                 //��·����
        cout<<",Lanes:"<<numLanes<<endl;         //��·������
        cout<<"Vehicles:"<<vehicleCount<<endl;   //��ǰ��������

        //��ʾ������Ϣ
        for(int i=0;i<vehicleCount;i++)
        {
            cout<<"Vehicle"<<vehicles[i].getId()                  //�������
                <<"at position"<<vehicles[i].getPosition()        //����λ��
                <<",lane"<<vehicles[i].getLane()                  //�������ڳ���
                <<",speed"<<vehicles[i].getSpeed()<<endl;         //�����ٶ�
        }
        
        //��ʾ��ͨ�źŵ���Ϣ
        cout<<"Traffic Lights:"<<lightCount<<endl;
        for(int i=0;i<lightCount;i++)
        {
            //��ͨ�źŵ�λ��
            cout<<"Light at position"<<trafficLights[i].getPosition()  
                <<"is"; 
            //��ͨ�źŵ�״̬
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

//��������״��ö������
enum class WeatherCondition 
{
    //����
    CLEAR,
    //���� 
    RAINY,
    //ѩ��   
    SNOWY,
    //����
    FOGGY,
    //���� 
    STORMY
};

//����������
class Weather 
{
private:
    WeatherCondition currentCondition;      // ��ǰ����״��
    int intensity;                          // ����ǿ��
    double visibility;                      // �ܼ���   
    double friction;                        // Ħ��ϵ��
    int timeStep;                           // ʱ�䲽������

    // ʹ��ȷ�����㷨��������
    void updateWeatherBasedOnTime() 
    {
        // ʹ��ʱ�䲽����α�����
        int pseudoRandom = (timeStep * 1103515245 + 12345) % 32768;

        // ����α�����ѡ����������
        int conditionIndex = pseudoRandom % 5;
        currentCondition = static_cast<WeatherCondition>(conditionIndex);
        
        // ��������ǿ�ȣ�����ʱ�䲽�ĸ��Ӻ�����
        intensity = ((pseudoRandom / 5) % 100);
        
        // �����������͵���ǿ�ȷ�Χ
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
    
     // �����������ͺ�ǿ�ȸ�����ز���
    void updateWeatherParameters() 
    {
        switch (currentCondition) 
        {
            //����
            case WeatherCondition::CLEAR:
                visibility = 1.0;
                friction = 1.0;
                break;
            //����
            case WeatherCondition::RAINY:
                visibility = 1.0 - (intensity / 200.0);
                friction = 0.9 - (intensity / 1000.0);
                break;
            //ѩ��
            case WeatherCondition::SNOWY:
                visibility = 1.0 - (intensity / 150.0);
                friction = 0.8 - (intensity / 200.0);
                break;
            //����
            case WeatherCondition::FOGGY:
                visibility = 0.8 - (intensity / 250.0);
                friction = 0.95;
                break;
            //����
            case WeatherCondition::STORMY:
                visibility = 0.6 - (intensity / 300.0);
                friction = 0.75 - (intensity / 400.0);
                break;
        }
    }
public:
    // ���캯��
    Weather() : timeStep(0) 
    {
        // ʹ��ȷ�����㷨��ʼ������
        updateWeatherBasedOnTime();
    }
    
    void update() 
    {
        timeStep++;
        // ÿ20��ʱ�䲽����һ��������Լ5%���ʱ仯��
        if (timeStep % 20 == 0) 
        {
            updateWeatherBasedOnTime();
        }
    }

    // ��ȡ����״̬����
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

    // ��ȡ����ǿ��
    int getIntensity() 
    {
        return intensity;
    }
    
    // ��ȡ�ܼ���ϵ��
    double getVisibilityFactor() 
    {
        return visibility;
    }
    
    // ��ȡ·��Ħ��ϵ��
    double getFrictionFactor() 
    {
        return friction;
    }
};