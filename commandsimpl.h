#ifndef COMMANDSIMPL_H
#define COMMANDSIMPL_H

#include "cpu.h"
#include "abstactcommand.h"

class CommandImplAdd : public AbstactCommand
{

public:

    CommandImplAdd(CPU *cpu) {
        setCpu(cpu);
    }

    bool execute(QString strArg, QString addrType) override {
        bool isDigit;
        int intArg = strArg.toInt(&isDigit);
        int resulAdd;
        QString acc = mCpu->getACC();
        QString operand;
        if(!isDigit){//проверка на то что strArg у нас регистр(R0/R1...) или число.
            if(addrType == ""){//адресация в регистре (взято из методы)
                operand = mCpu->getRegisterValue(strArg.at(1).digitValue());
                resulAdd = mCpu->convertRegToInt(acc) + mCpu->convertRegToInt(operand);
            }else if(addrType == "@"){
                QString addressOperand = mCpu->getRegisterValue(strArg.at(1).digitValue());
                operand = mCpu->memory->get(addressOperand.toInt());
                resulAdd = mCpu->convertRegToInt(acc) + mCpu->convertRegToInt(operand);
            }else if(addrType == "-@"){
                QString addressOperand = mCpu->getRegisterValue(strArg.at(1).digitValue());
                operand = mCpu->memory->get(addressOperand.toInt() - 1);
                resulAdd = mCpu->convertRegToInt(acc) + mCpu->convertRegToInt(operand);
                mCpu->setRegisterValue(strArg.at(1).digitValue(), mCpu->convertIntToReg(addressOperand.toInt() - 1));
            }else if(addrType == "@+"){
                QString addressOperand = mCpu->getRegisterValue(strArg.at(1).digitValue());
                operand = mCpu->memory->get(addressOperand.toInt());
                resulAdd = mCpu->convertRegToInt(acc) + mCpu->convertRegToInt(operand);
                mCpu->setRegisterValue(strArg.at(1).digitValue(), mCpu->convertIntToReg(addressOperand.toInt() + 1));
            }else{
                throw "Execute CommandImplAdd bad addrType register";
                return false;
            }
            mCpu->setACC(mCpu->convertIntToReg(resulAdd));
            //Тут искуственно вызывать update для граф части ?
            return true;
        }

        if(addrType == "" || addrType == "["){      //костыль на If else.   '[' адресация, потом поговорим
            operand = mCpu->memory->get(intArg);
            resulAdd = mCpu->convertRegToInt(acc) + mCpu->convertRegToInt(operand);
        }else if(addrType == "@"){
            QString addressOperand = mCpu->memory->get(intArg);
            operand = mCpu->memory->get(addressOperand.toInt());
            resulAdd = mCpu->convertRegToInt(acc) + mCpu->convertRegToInt(operand);
        }else if(addrType == "#"){
            resulAdd = mCpu->convertRegToInt(acc) + mCpu->convertRegToInt(strArg);
        }else{
            throw "Execute CommandImplAdd bad addrType";
            return false;
        }

        mCpu->setACC(mCpu->convertIntToReg(resulAdd));
        //Тут искуственно вызывать update для граф части ?
        return true;
    }

};



class CommandImplSub : public AbstactCommand
{

public:

    CommandImplSub(CPU *cpu) {
        setCpu(cpu);
    }

    bool execute(QString strArg, QString addrType) override {

        return true;
    }

};


class CommandImplMul : public AbstactCommand
{

public:

    CommandImplMul(CPU *cpu) {
        setCpu(cpu);
    }

    bool execute(QString strArg, QString addrType) override {

        return true;
    }

};


class CommandImplDiv : public AbstactCommand
{

public:

    CommandImplDiv(CPU *cpu) {
        setCpu(cpu);
    }

    bool execute(QString strArg, QString addrType) override {

        return true;
    }

};



#endif // COMMANDSIMPL_H
