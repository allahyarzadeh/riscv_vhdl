/**
 * @file
 * @copyright  Copyright 2017 GNSS Sensor Ltd. All right reserved.
 * @author     Sergey Khabarov - sergeykhbr@gmail.com
 * @brief      Fast Search Engnine (FSE) black-box model.
 */

#include "api_core.h"
#include "fsev2.h"

namespace debugger {

static const uint32_t FSE2_CONTROL_ENA      = (1 << 31);  // 0=disable; 1=enable
static const uint32_t FSE2_CONTROL_ADC      = (1 << 30);  // 0=bin offset; 1=sign/magn
static const uint32_t FSE2_STATE_NXT_DOPLER = (1 << 21);
static const uint32_t FSE2_STATE_PROCESSING = (1 << 20);
static const uint32_t FSE2_STATE_SELCHAN    = (1 << 19);
static const uint32_t FSE2_STATE_WRITING    = (1 << 18);
static const uint32_t FSE2_STATE_WAIT_MS    = (1 << 17);
static const uint32_t FSE2_STATE_IDLE       = (1 << 16);

FseV2::FseV2(const char *name)  : IService(name) {
    registerInterface(static_cast<IMemoryOperation *>(this));
    registerAttribute("BaseAddress", &baseAddress_);
    registerAttribute("Length", &length_);

    baseAddress_.make_uint64(0);
    length_.make_uint64(0);

    memset(&regs_, 0, sizeof(regs_));
    regs_.hw_id = (16 << 16) | 5;   // 16 msec accum, 5=id
    for (int i = 0; i < FSE2_CHAN_MAX; i++) {
        regs_.chan[i].dopler = 1000 << 4;
    }
}

void FseV2::b_transport(Axi4TransactionType *trans) {
    uint64_t mask = (length_.to_uint64() - 1);
    uint64_t off = ((trans->addr - getBaseAddress()) & mask);
    trans->response = MemResp_Valid;
    if (trans->action == MemAction_Write) {
        memcpy(&reinterpret_cast<uint8_t *>(&regs_)[off], trans->wpayload.b8,
                trans->xsize);
    } else {
        memcpy(trans->rpayload.b8, &reinterpret_cast<uint8_t *>(&regs_)[off],
                trans->xsize);
    }
}

}  // namespace debugger
