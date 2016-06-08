#include "commandfactory.h"
#include "commandsimpl.h"
#include <QDebug>

CommandFactory::CommandFactory(CPU *cpu, Memory *memory)
{
    this->impl = cpu;
    this->mMemory = memory;

    addImpl(01, new FactoryItem<CommandImplIn>());
    addImpl(02, new FactoryItem<CommandImplOut>());

    addImpl(06, new FactoryItem<CommandImplPush>());
    addImpl(07, new FactoryItem<CommandImplPop>());

    addImpl(8, new FactoryItem<CommandImplRet>());
    addImpl(19, new FactoryItem<CommandImplCall>());

    addImpl(10, new FactoryItem<CommandImplJmp>());
    addImpl(11, new FactoryItem<CommandImplJz>());
    addImpl(12, new FactoryItem<CommandImplJnz>());
    addImpl(13, new FactoryItem<CommandImplJs>());
    addImpl(14, new FactoryItem<CommandImplJns>());
    addImpl(15, new FactoryItem<CommandImplJo>());
    addImpl(16, new FactoryItem<CommandImplJno>());
    addImpl(17, new FactoryItem<CommandImplJrnz>());

    addImpl(21, new FactoryItem<CommandImplRead>());
    addImpl(22, new FactoryItem<CommandImplWrite>());
    addImpl(23, new FactoryItem<CommandImplAdd>());
    addImpl(24, new FactoryItem<CommandImplSub>());
    addImpl(25, new FactoryItem<CommandImplMul>());
    addImpl(26, new FactoryItem<CommandImplDiv>());

    addImpl(31, new FactoryItem<CommandImplReadRegister>());
    addImpl(32, new FactoryItem<CommandImplWriteRegister>());
    addImpl(33, new FactoryItem<CommandImplAddRegister>());
    addImpl(34, new FactoryItem<CommandImplSubRegister>());
    addImpl(35, new FactoryItem<CommandImplMulRegister>());
    addImpl(36, new FactoryItem<CommandImplDivRegister>());
}

void CommandFactory::addImpl(int code, FactoryItemInterface *impl)
{
    mCommands.insert(code, impl);
}

AbstactCommand *CommandFactory::createCommand(int code)
{
    FactoryItemInterface *cmd = mCommands.value(code, NULL);
    if(cmd) {
        return cmd->create(this->impl, this->mMemory);
    }
    return NULL;
}
