#include <gtest/gtest.h>
#include "Enemy.h"
#include "Sean.h"

// Test fixture class for Enemy
class EnemyTest : public ::testing::Test {
protected:
    Enemy *enemy;

    void SetUp() override {
        enemy = new Enemy("Goblin", "A small green creature.", 100, 50, 5, 15, 1);
    }

    void TearDown() override {
        delete enemy;
    }
};

// Test for getName method
TEST_F(EnemyTest, GetNameAlive) {
    EXPECT_EQ(enemy->getName(), "Goblin1");
}

TEST_F(EnemyTest, GetNameDead) {
    enemy->takeDamage(100);
    EXPECT_EQ(enemy->getName(), "dode Goblin1");
}

// Test for printName method
TEST_F(EnemyTest, PrintName) {
    testing::internal::CaptureStdout();
    enemy->printName();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Goblin1\n");
}

// Test for printDescription method
TEST_F(EnemyTest, PrintDescription) {
    testing::internal::CaptureStdout();
    enemy->printDescription();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "A small green creature.\n");
}

// Test for isDead method
TEST_F(EnemyTest, IsDead) {
    EXPECT_FALSE(enemy->isDead());
    enemy->takeDamage(100);
    EXPECT_TRUE(enemy->isDead());
}

// Test for getAttack method
TEST_F(EnemyTest, GetAttack) {
    int attack = enemy->getAttack();
    EXPECT_GE(attack, 0);
    EXPECT_LE(attack, 15);
}

// Test for getHiddenObjects method
TEST_F(EnemyTest, GetHiddenObjects) {
    auto &hiddenObjects = enemy->getHiddenObjects();
    EXPECT_GE(hiddenObjects.size(), 0);
}