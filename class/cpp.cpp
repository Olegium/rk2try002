#include <iostream>
#include "header.h"
ConcreteCommandA::ConcreteCommandA(IReciever *reciever) : m_reciever(reciever){}

void ConcreteCommandA::execute() const
{
    if (m_reciever)
    {
        m_reciever->performTask();
    }
}

ConcreteCommandB::ConcreteCommandB(IReciever *reciever) : m_reciever(reciever){}

void ConcreteCommandB::execute() const
{
    if (m_reciever)
    {
        m_reciever->performTask();
    }
}
void ConcreteRecieverX::performTask() const
{
    std::cout << "Performing task X" << std::endl;
}

void ConcreteRecieverY::performTask() const
{
    std::cout << "Performing task Y" << std::endl;
}

void ConcreteInvoker::setCommand(ICommand *command)
{
    m_command = command;
}

void ConcreteInvoker::confirm()
{
    if (m_command)
    {
        m_command->execute();
    }
}
