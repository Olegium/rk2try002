#include "header.h"
int main()
{
    ICommand *commandA = new ConcreteCommandA(new ConcreteRecieverX());
    ICommand *commandB = new ConcreteCommandA(new ConcreteRecieverY());

    IInvoker *invoker = new ConcreteInvoker();
    invoker->setCommand(commandA);
    invoker->confirm();

    invoker->setCommand(commandB);
    invoker->confirm();

    return 0;
}
