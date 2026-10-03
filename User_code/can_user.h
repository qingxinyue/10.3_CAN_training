//
// Created by qingx on 2026/10/3.
//

#ifndef CAN_EXPERIMENT_CAN_USER_H
#define CAN_EXPERIMENT_CAN_USER_H
#include "main.h"

extern CAN_RxHeaderTypeDef rx_header;
extern CAN_TxHeaderTypeDef tx_header;
extern uint32_t  can_tx_mailbox;
extern CAN_FilterTypeDef can_filter_config;

#endif //CAN_EXPERIMENT_CAN_USER_H
