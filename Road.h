#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<random>
#include"Vehicle.h"
#include"TrafficLight.h"
class Road 
{
private:
    static const int MAX_VEHICLES=100;         // 最大车辆数
    static const int MAX_LIGHTS=10;           // 最大交通信号灯数
    static const int MAX_ENTRANCES=5;        // 最大入口数
    static const int MAX_EXITS=5;            // 最大出口数
    int length;                             // 道路长度
    int numLanes;                           // 道路车道数
    static int vehicleCount;                // 当前车辆数量
    static int lightCount;                  // 当前交通信号灯数量
    int entrances[MAX_ENTRANCES];           // 入口位置数组
    int entranceCount;                      // 入口数量
    int exits[MAX_EXITS];                   // 出口位置数组
    int exitCount;                          // 出口数量
    static Vehicle *vehicles[MAX_VEHICLES];  // 使用基类指针
    static TrafficLight trafficLights[MAX_LIGHTS]; // 交通信号灯数组，对象数组
public:
    //���캯��
    Road(int len,int num,int vc,int lc,int ec,int ex,int *entr,int *exit)
    {
        length=len;
        numLanes=num;
        vehicleCount=vc;
        lightCount=lc;
        entranceCount=ec;
        exitCount=ex;
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

    //���ӳ��������ܻ���ָ��
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

    //���ӽ�ͨ�źŵ�
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

    //获取当前交通信号灯数量
    static int getLightCount()
    {
        return lightCount;
    }
    
    //获取指定索引的交通信号灯
    static TrafficLight& getTrafficLight(int index)
    {
        if (index >= 0 && index < lightCount) {
            return trafficLights[index];
        }
        // 返回第一个交通灯作为默认值
        return trafficLights[0];
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
    //更新道路状态
    void update()
    {
        // 更新所有交通信号灯
        for(int i=0; i<lightCount; i++)
        {
            trafficLights[i].update();
        }

        // 更新所有车辆
        for(int i=0; i<vehicleCount; i++)
        {
            bool shouldStop = false;
            
            // 检查交通信号灯
            for(int j=0; j<lightCount; j++)
            {
                // 如果车辆位置超过信号灯位置且信号灯为红灯
                if(vehicles[i]->getPosition() >= trafficLights[j].getPosition() && 
                   vehicles[i]->getPosition() < trafficLights[j].getPosition() + 5 && 
                   trafficLights[j].getState() == TrafficLightState::RED)
                {
                    // 车辆停止
                    vehicles[i]->stop();
                    shouldStop = true;
                    break;
                }
            }
            
            if(!shouldStop)
            {
                // 如果没有遇到红灯，则车辆启动
                vehicles[i]->start();
                
                // 检查与其他车辆的安全距离
                bool needDecelerate = false;
                for(int j=0; j<vehicleCount; j++)
                {
                    // 排除车辆与自己的距离检查
                    if(i == j)
                    {
                        continue;
                    }
                    
                    // 如果在同一车道，且前方有车，安全距离小于5时，减速
                    if(vehicles[i]->getLane() == vehicles[j]->getLane() && 
                       vehicles[i]->getPosition() < vehicles[j]->getPosition() && 
                       vehicles[j]->getPosition() - vehicles[i]->getPosition() < 5)
                    {
                        vehicles[i]->decelerate();
                        needDecelerate = true;
                        break;
                    }
                }
                
                // 如果没有需要减速，则加速
                if(!needDecelerate){
                    vehicles[i]->accelerate();
                }
            }
            
            // 移动车辆
            vehicles[i]->move();
            
            // 检查车辆是否到达出口
            bool reachedExit = false;
            for(int j=0; j<exitCount; j++)
            {
                if(vehicles[i]->getPosition() >= exits[j])
                {
                    // 移除车辆
                    for(int k=i; k<vehicleCount-1; k++)
                    {
                        vehicles[k] = vehicles[k+1];
                    }
                    --vehicleCount;
                    --i; // 调整索引，因为当前车辆已被移除
                    reachedExit = true;
                    break;
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
            cout<<"Vehicle "<<vehicles[i]->getId()                  //车辆编号
                <<" at position "<<vehicles[i]->getPosition()        //车辆位置
                <<", lane "<<vehicles[i]->getLane()                  //车辆所在车道
                <<", speed "<<vehicles[i]->getSpeed()<<endl;         //车辆速度
        }
        
        //显示交通信号灯信息
        cout<<"Traffic Lights: "<<lightCount<<endl;
        for(int i=0;i<lightCount;i++)
        {
            //交通信号灯位置
            cout<<"Light at position "<<trafficLights[i].getPosition()  
                <<" is "; 
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

