#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<random>
#include<math.h>
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