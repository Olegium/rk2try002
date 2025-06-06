class ICommand
{
public:
    virtual ~ICommand() {}
    virtual void execute() const = 0;
};

class IInvoker
{
public:
    virtual void setCommand(ICommand *command) = 0;
    virtual void confirm() = 0;
};

class IReciever
{
public:
    virtual ~IReciever() {}
    virtual void performTask() const = 0;
};

class ConcreteCommandA : public ICommand
{
public:
    ConcreteCommandA(IReciever * reciever);
    virtual void execute() const override;

private:
    IReciever *m_reciever;
};

class ConcreteCommandB : public ICommand
{
public:
    ConcreteCommandB(IReciever * reciever);
    virtual void execute() const override;

private:
    IReciever *m_reciever;
};

class ConcreteRecieverX : public IReciever
{
public:
    ConcreteRecieverX() = default;
    virtual void performTask() const override;
};

class ConcreteRecieverY : public IReciever
{
public:
    ConcreteRecieverY() = default;
    virtual void performTask() const override;
};

class ConcreteInvoker : public IInvoker
{
public:
    ConcreteInvoker() = default;

    void setCommand(ICommand *command) override;
    void confirm() override;

private:
    ICommand *m_command;
};
