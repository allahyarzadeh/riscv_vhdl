/**
 * @file
 * @copyright  Copyright 2016 GNSS Sensor Ltd. All right reserved.
 * @author     Sergey Khabarov - sergeykhbr@gmail.com
 * @brief      Log file enable/disable.
 */

#ifndef __DEBUGGER_CMD_LOG_H__
#define __DEBUGGER_CMD_LOG_H__

#include "api_core.h"
#include "coreservices/itap.h"
#include "coreservices/isocinfo.h"
#include "coreservices/icommand.h"

namespace debugger {

class CmdLog : public ICommand  {
public:
    explicit CmdLog(ITap *tap, ISocInfo *info);

    /** ICommand */
    virtual bool isValid(AttributeType *args);
    virtual void exec(AttributeType *args, AttributeType *res);

private:
};

}  // namespace debugger

#endif  // __DEBUGGER_CMD_LOG_H__
