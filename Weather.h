#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<random>
#include<math.h>
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