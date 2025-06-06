#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "header.h"
#include <sstream>
#include <string>
using namespace std;

class MockReciever : public IReciever {
public:
    MOCK_METHOD(void, performTask, (), (const, override));
};

class MockCommand : public ICommand {
public:
    MOCK_METHOD(void, execute, (), (const, override));
};

TEST(ConcreteInvokerTest, SetCommandStoresCommand) {
    // Arrange
    ConcreteInvoker invoker;
    MockCommand mockCommand;
    
    // Act
    invoker.setCommand(&mockCommand);
    
    // Assert - проверяем через confirm()
    EXPECT_CALL(mockCommand, execute()).Times(1);
    invoker.confirm();
}

TEST(ConcreteInvokerTest, ConfirmExecutesStoredCommand) {
    // Arrange
    ConcreteInvoker invoker;
    MockCommand mockCommand;
    invoker.setCommand(&mockCommand);
    
    // Expect
    EXPECT_CALL(mockCommand, execute()).Times(1);
    
    // Act
    invoker.confirm();
}

TEST(ConcreteInvokerTest, SetCommandReplacesPreviousCommand) {
    // Arrange
    ConcreteInvoker invoker;
    MockCommand mockCommand1, mockCommand2;
    invoker.setCommand(&mockCommand1);
    
    // Expect - должен вызваться только второй команды
    EXPECT_CALL(mockCommand1, execute()).Times(0);
    EXPECT_CALL(mockCommand2, execute()).Times(1);
    
    // Act
    invoker.setCommand(&mockCommand2);
    invoker.confirm();
}

TEST(ConcreteInvokerTest, ConfirmCanBeCalledMultipleTimes) {
    // Arrange
    ConcreteInvoker invoker;
    MockCommand mockCommand;
    invoker.setCommand(&mockCommand);
    
    // Expect
    EXPECT_CALL(mockCommand, execute()).Times(2);
    
    // Act
    invoker.confirm();
    invoker.confirm();
}
TEST(ConcreteCommandATest, ExecuteCallsPerformTask) {
    // Arrange
    MockReciever mockReciever;
    ConcreteCommandA command(&mockReciever);

    // Ожидаем, что performTask() будет вызван ровно один раз
    EXPECT_CALL(mockReciever, performTask()).Times(1);

    // Act
    command.execute();
}

TEST(ConcreteCommandATest, ExecuteWithNullRecieverDoesNothing) {
    // Arrange
    ConcreteCommandA command(nullptr);

    // Act & Assert (не должно быть краха или вызовов)
    EXPECT_NO_THROW(command.execute());
}
TEST(ConcreteCommandBTest, ExecuteCallsPerformTask) {
    // Arrange
    MockReciever mockReciever;
    ConcreteCommandB command(&mockReciever);

    // Expect
    EXPECT_CALL(mockReciever, performTask()).Times(1);

    // Act
    command.execute();
}

TEST(ConcreteCommandBTest, ExecuteWithNullRecieverDoesNothing) {
    // Arrange
    ConcreteCommandB command(nullptr);

    // Act & Assert
    EXPECT_NO_THROW(command.execute());
}

TEST(ConcreteCommandBTest, ConstructorSetsRecieverCorrectly) {
    // Arrange
    MockReciever mockReciever;
    
    // Act
    ConcreteCommandB command(&mockReciever);
    
    // Assert
    EXPECT_CALL(mockReciever, performTask()).Times(1);
    command.execute();
}

TEST(ConcreteRecieverXTest, PerformTaskOutputsCorrectMessage) {
    // Arrange
    ConcreteRecieverX receiver;
    stringstream outputBuffer;
    
    // Перенаправляем cout в буфер
    streambuf* oldCout = cout.rdbuf(outputBuffer.rdbuf());

    // Act
    receiver.performTask();

    // Возвращаем cout обратно
    cout.rdbuf(oldCout);

    // Assert
    string output = outputBuffer.str();
    EXPECT_EQ(output, "Performing task X\n");
}

TEST(ConcreteRecieverXTest, DefaultConstructorWorks) {
    // Arrange & Act
    ConcreteRecieverX receiver;
    
    // Assert - просто проверяем, что объект создается без ошибок
    SUCCEED();
}
// Тест для проверки вывода в консоль
TEST(ConcreteRecieverYTest, PerformTaskOutputsCorrectMessage) {
    // Arrange
    ConcreteRecieverY receiver;
    stringstream outputBuffer;
    
    // Сохраняем оригинальный буфер cout
    streambuf* oldCoutBuffer = cout.rdbuf();
    
    // Перенаправляем вывод в наш буфер
    cout.rdbuf(outputBuffer.rdbuf());

    // Act
    receiver.performTask();

    // Восстанавливаем оригинальный буфер
    cout.rdbuf(oldCoutBuffer);

    // Assert
    string expectedOutput = "Performing task Y\n";
    EXPECT_EQ(outputBuffer.str(), expectedOutput);
}

// Тест конструктора по умолчанию
TEST(ConcreteRecieverYTest, DefaultConstructorCreatesValidObject) {
    // Arrange & Act
    ConcreteRecieverY receiver;
    
    // Assert
    // Если объект создан без исключений - тест пройден
    SUCCEED();
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
