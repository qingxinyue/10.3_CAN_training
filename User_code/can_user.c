#include "can_user.h"
//
// Created by qingx on 2026/10/3.
//
 CAN_RxHeaderTypeDef rx_header;
 CAN_TxHeaderTypeDef tx_header;
 uint32_t  can_tx_mailbox;
 // CAN_FilterTypeDef can_filter_config;
 //config初始化
CAN_FilterTypeDef can_filter_config = {
    .FilterIdHigh = 0,
    .FilterIdLow = 0,
    .FilterMaskIdHigh = 0,
    .FilterMaskIdLow = 0,
    .FilterFIFOAssignment = CAN_RX_FIFO0,
    .FilterBank = 0,
    .FilterMode = CAN_FILTERMODE_IDMASK,
    .FilterScale = CAN_FILTERSCALE_32BIT,
    .FilterActivation = ENABLE,
    .SlaveStartFilterBank = 14
};

CAN_TxHeaderTypeDef tx_header = {
    .StdId =0x200,
    .IDE = CAN_ID_STD,
    .RTR = CAN_RTR_DATA,
    .DLC = 8,
    .TransmitGlobalTime = DISABLE
};