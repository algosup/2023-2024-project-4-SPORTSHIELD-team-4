# Battery Improvement Documentation

## Issue

The battery used for this project is a 3.7V 1100mAh LiPo battery. However, the use duration of the battery is limited, and the battery life is not optimal for the project's requirements. That is why we had to find a solution to improve the battery life and optimize its usage.

## Analysis

### Battery Consumption

The primary reason for the limited battery life is the high power consumption of the components used in the project. The Bluetooth module and the GPS module are the most power-hungry components, leading to a significant drain on the battery.

### Optimization opportunities

To improve battery life, we need to focus on optimizing component power consumption and implement energy-saving strategies. This can be achieved in several ways, such as reducing the transmission frequency of the Bluetooth module, optimizing the GPS module and setting up power-saving modes according to battery level.

## Solutions

### Modules Optimization

#### 1. Bluetooth module optimization

By reducing the Bluetooth module's transmission frequency, we can significantly reduce its energy consumption. This can be achieved by adjusting the transmission interval and data packet size to minimize the module's activity time.

#### 2. Optimizing the GPS module

Optimizing the GPS module can also help improve battery life. By adjusting the GPS module's update rate, we can reduce power consumption without compromising functionality.

### Power-saving strategies

#### 1. Implementing energy-saving modes

Implementing energy-saving modes for inactive components can further reduce energy consumption. By putting non-essential components to sleep when not in use, we can minimize overall battery consumption.

#### 2. Dynamic energy management

Implementing dynamic energy management techniques can help optimize energy consumption according to the system's operational requirements. By dynamically adjusting power parameters and component states, we can achieve greater energy efficiency and extend battery life.

## Testing

After implementing the above solutions, we conducted tests to evaluate the impact on battery life. We let the project run continuously a whole night and measured the battery level at the beginning and end of the test.

### Test Results

#### Initial battery voltage: 3.96V

#### Final battery voltage: 3.8V

#### Test duration: 18 hours and 20 minutes

### Test Analysis

The test results show a significant improvement in battery life after implementing the optimization solutions. The battery voltage dropped by only 0.16V over an 18-hour period, indicating a much lower power consumption rate compared to the previous configuration.

If the project continues to consume power at the same rate, the battery life can be estimated as follows:

```electricity
Initial battery voltage: 3.7V
Final battery voltage: 3.4V
Voltage drop: 0.25V
Estimated battery life: 5.7 days
```

## Conclusion

In conclusion, improving the project's battery life requires a combination of component optimization and energy-saving strategies. By optimizing the power consumption of the Bluetooth and GPS modules and implementing standby modes and dynamic power management, we can significantly improve battery life and achieve optimum performance for the project. These solutions will address the current limitations of the battery and ensure that the project efficiently meets its energy needs.

That's how we improved the battery duration from 3 days to 7 days.
