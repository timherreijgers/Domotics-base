#include <utils/logger.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

std::string expectedMessage;
bool gotMessage = false;

void callback(const char * msg)
{
    gotMessage = strcmp(msg, expectedMessage.c_str()) == 0;
}

class LoggerTest : public ::testing::Test
{
    void SetUp() override
    {
        gotMessage = false;
    }
};

TEST_F(LoggerTest, TestTrace)
{
    expectedMessage = "[TRACE] Test message";
    Logger::setLoggerCallback(callback);
    Logger::trace("Test message");

    ASSERT_TRUE(gotMessage);
}

TEST_F(LoggerTest, TestDebug)
{
    expectedMessage = "[DEBUG] Test message";
    Logger::setLoggerCallback(callback);
    Logger::debug("Test message");

    ASSERT_TRUE(gotMessage);
}

TEST_F(LoggerTest, TestInfo)
{
    expectedMessage = "[INFO]  Test message";
    Logger::setLoggerCallback(callback);
    Logger::info("Test message");

    ASSERT_TRUE(gotMessage);
}

TEST_F(LoggerTest, TestWarning)
{
    expectedMessage = "[WARN]  Test message";
    Logger::setLoggerCallback(callback);
    Logger::warning("Test message");

    ASSERT_TRUE(gotMessage);
}

TEST_F(LoggerTest, TestError)
{
    expectedMessage = "[ERROR] Test message";
    Logger::setLoggerCallback(callback);
    Logger::error("Test message");

    ASSERT_TRUE(gotMessage);
}
