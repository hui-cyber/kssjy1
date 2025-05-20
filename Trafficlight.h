#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<random>
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

    // 获取信号灯位置
    int getPosition()
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
    // 获取信号灯状态
    TrafficLightState getState()  
    {
        return state;
    }
    
    // 设置信号灯状态
    void setState(TrafficLightState newState)
    {
        state = newState;
    }
    // ��ȡ�źŵ�λ��
    // 此方法已在前面定义，这里删除重复定义

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