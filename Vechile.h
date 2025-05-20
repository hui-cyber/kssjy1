#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<random>
class Vehicle
{
private:
    int id;                   // ���� ID
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