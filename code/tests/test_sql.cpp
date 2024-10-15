#include <gtest/gtest.h>
#include "SqlReader.h"
#include "Sean.h"

class SQLReaderTest : public ::testing::Test {
protected:
    SQLReader &sqlReader = SQLReader::getInstance();

    void SetUp() override {
        // Any setup code if needed
    }

    void TearDown() override {
        // Any teardown code if needed
    }
};

TEST_F(SQLReaderTest, GetLocationInfo_ValidName) {
    Sean::String name("De IJzeren Burcht");
    Sean::String description;

    bool result = sqlReader.getLocationInfo(name, description);

    EXPECT_TRUE(result);
    EXPECT_FALSE(description.empty());
}

TEST_F(SQLReaderTest, GetLocationInfo_InvalidName) {
    Sean::String name("invalid_location_name");
    Sean::String description;

    bool result = sqlReader.getLocationInfo(name, description);

    EXPECT_FALSE(result);
    EXPECT_TRUE(description.empty());
}

TEST_F(SQLReaderTest, GetRandomLocation) {
    Sean::String name;
    Sean::String description;

    bool result = sqlReader.getRandomLocation(name, description);

    EXPECT_TRUE(result);
    EXPECT_FALSE(name.empty());
    EXPECT_FALSE(description.empty());
}

TEST_F(SQLReaderTest, GetEnemyInfo_ValidName) {
    Sean::String name("Goblin");
    Sean::String description;
    int health, attackPercent, minDamage, maxDamage;

    bool result = sqlReader.getEnemyInfo(name, description, health, attackPercent, minDamage, maxDamage);

    EXPECT_TRUE(result);
    EXPECT_FALSE(description.empty());
    EXPECT_GT(health, 0);
    EXPECT_GE(attackPercent, 0);
    EXPECT_GE(minDamage, 0);
    EXPECT_GE(maxDamage, minDamage);
}

TEST_F(SQLReaderTest, GetEnemyInfo_InvalidName) {
    Sean::String name("invalid_enemy_name");
    Sean::String description;
    int health, attackPercent, minDamage, maxDamage;

    bool result = sqlReader.getEnemyInfo(name, description, health, attackPercent, minDamage, maxDamage);

    EXPECT_FALSE(result);
    EXPECT_TRUE(description.empty());
}

TEST_F(SQLReaderTest, GetRandomEnemy) {
    Sean::String name;
    Sean::String description;
    int health, attackPercent, minDamage, maxDamage;

    bool result = sqlReader.getRandomEnemy(name, description, health, attackPercent, minDamage, maxDamage);

    EXPECT_TRUE(result);
    EXPECT_FALSE(name.empty());
    EXPECT_FALSE(description.empty());
    EXPECT_GT(health, 0);
    EXPECT_GE(attackPercent, 0);
    EXPECT_GE(minDamage, 0);
    EXPECT_GE(maxDamage, minDamage);
}

TEST_F(SQLReaderTest, GetObjectInfo_ValidName) {
    Sean::String name("zacht leren wapenrusting");
    Sean::String description, type;
    int minValue, maxValue, protection;

    bool result = sqlReader.getObjectInfo(name, description, type, minValue, maxValue, protection);

    EXPECT_TRUE(result);
    EXPECT_FALSE(description.empty());
    EXPECT_FALSE(type.empty());
    EXPECT_GE(minValue, 0);
    EXPECT_GE(maxValue, minValue);
    EXPECT_GE(protection, 0);
}

TEST_F(SQLReaderTest, GetObjectInfo_InvalidName) {
    Sean::String name("invalid_object_name");
    Sean::String description, type;
    int minValue, maxValue, protection;

    bool result = sqlReader.getObjectInfo(name, description, type, minValue, maxValue, protection);

    EXPECT_FALSE(result);
    EXPECT_TRUE(description.empty());
    EXPECT_TRUE(type.empty());
}

TEST_F(SQLReaderTest, GetRandomObject) {
    Sean::String name;
    Sean::String description;
    Sean::String type;
    int minValue, maxValue, protection;

    bool result = sqlReader.getRandomObject(name, description, type, minValue, maxValue, protection);

    EXPECT_TRUE(result);
    EXPECT_FALSE(name.empty());
    EXPECT_FALSE(description.empty());
    EXPECT_FALSE(type.empty());
    EXPECT_GE(minValue, 0);
    EXPECT_GE(maxValue, minValue);
    EXPECT_GE(protection, 0);
}

TEST_F(SQLReaderTest, GetObjectAmount_ValidName) {
    Sean::String name("Bandiet");
    int minAmount, maxAmount;

    bool result = sqlReader.getObjectAmount(name, minAmount, maxAmount);

    EXPECT_TRUE(result);
    EXPECT_GE(minAmount, 0);
    EXPECT_GE(maxAmount, minAmount);
}

TEST_F(SQLReaderTest, GetObjectAmount_InvalidName) {
    Sean::String name("invalid_enemy_name");
    int minAmount, maxAmount;

    bool result = sqlReader.getObjectAmount(name, minAmount, maxAmount);

    EXPECT_FALSE(result);
}
