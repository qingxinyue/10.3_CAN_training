//
// Created by qingx on 2026/10/3.
//

#ifndef CAN_EXPERIMENT_MOTOR_HPP
#define CAN_EXPERIMENT_MOTOR_HPP
#include "main.h"

class Motor
{
public:
    explicit Motor(float ratio);

    void canRxMsgCallback(const uint8_t rx_data[8]);

    float angle() const;
    float speedRpm() const;
    float currentAmps() const;
    float temperature() const;
    bool hasFeedBack() const;

    void setTxCurrent(float amperes,uint8_t motor_id);
    uint8_t* getTxData();

private:
    const float ratio_;

    float ecd_angle_ =0;
    float speedRpm_ =0;
    float currentAmps_ =0;
    float tempC_ =0;

    float angle_ =0;
    float last_ecd_ =0;
    bool received_ =false;

    uint8_t tx_data_[8]={};

    //to-do
    static constexpr uint16_t kEncoderRange =8192;

};
Motor::Motor(float ratio):ratio_(ratio){}

inline void Motor::canRxMsgCallback(const uint8_t rx_data[8])
{
    uint16_t angle_raw = (static_cast<uint16_t>(rx_data[0]) << 8) | static_cast<uint16_t>(rx_data[1]);
    ecd_angle_ = static_cast<float>(angle_raw) / kEncoderRange* 360.0f;
    uint16_t raw_speedRpm_ = (static_cast<uint16_t>(rx_data[2]) << 8) | static_cast<uint16_t>(rx_data[3]);
    speedRpm_ = static_cast<float>(raw_speedRpm_);
    uint16_t raw_currentAmps_ = (static_cast<uint16_t>(rx_data[4]) << 8) | static_cast<uint16_t>(rx_data[5]);
    currentAmps_ = static_cast<float>(raw_currentAmps_);
    tempC_ = static_cast<float>(rx_data[6]);

    if (!received_)
    {
        received_ = true;
        last_ecd_ = ecd_angle_;
        return;
    }

}

inline void Motor::setTxCurrent(float amperes, uint8_t motor_id)
{
    if (motor_id < 1 ||motor_id > 4) return;
    // tx_data_[0] =static_cast<uint16_t>(amperes)>>8;
    // tx_data_[1] =static_cast<uint16_t>(amperes)&0xFF;
    const int16_t raw=static_cast<int16_t>(amperes*kEncoderRange);
    const uint16_t raw_speed=static_cast<uint16_t>(raw);

    const unsigned offset =2*(motor_id-1);
    tx_data_[offset] = static_cast<uint8_t>(raw_speed >> 8);
    tx_data_[offset+1] = static_cast<uint8_t>(raw_speed & 0xFF);

}

inline uint8_t* Motor::getTxData()
{
    return tx_data_;
}
#endif //CAN_EXPERIMENT_MOTOR_HPP
