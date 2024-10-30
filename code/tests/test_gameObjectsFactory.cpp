#include <gtest/gtest.h>
#include "GameObjectFactory.h"
#include "GoldObject.h"
#include "WeaponObject.h"
#include "ArmorObject.h"
#include "ConsumableObject.h"
#include "Sean.h"

// Test for GameObjectFactory
class GameObjectFactoryTest : public ::testing::Test {
protected:
    GameObjectFactory *factory;

    void SetUp() override {
        factory = new GameObjectFactory();
        factory->resetCounter();
    }

    void TearDown() override {
        delete factory;
    }
};

TEST_F(GameObjectFactoryTest, CreateGoldObject) {
    GameObject *obj = factory->createGameObject("paar goudstukken");
    ASSERT_NE(obj, nullptr);
    EXPECT_EQ(obj->getName(), "paar goudstukken1");
    EXPECT_EQ(obj->getType(), ObjectType::Gold);
    EXPECT_EQ(static_cast<GoldObject*>(obj)->getMin(), 1);
    EXPECT_EQ(static_cast<GoldObject*>(obj)->getMax(), 3);
    delete obj;
}

TEST_F(GameObjectFactoryTest, CreateWeaponObject) {
    GameObject *obj = factory->createGameObject("dolk");
    ASSERT_NE(obj, nullptr);
    EXPECT_EQ(obj->getName(), "dolk1");
    EXPECT_EQ(obj->getType(), ObjectType::Weapon);
    EXPECT_EQ(static_cast<WeaponObject*>(obj)->getMin(), 1);
    EXPECT_EQ(static_cast<WeaponObject*>(obj)->getMax(), 4);
    delete obj;
}

TEST_F(GameObjectFactoryTest, CreateArmorObject) {
    GameObject *obj = factory->createGameObject("harnas");
    ASSERT_NE(obj, nullptr);
    EXPECT_EQ(obj->getName(), "harnas1");
    EXPECT_EQ(obj->getType(), ObjectType::Armor);
    EXPECT_EQ(static_cast<ArmorObject*>(obj)->getArmor(), 5);
    delete obj;
}

TEST_F(GameObjectFactoryTest, CreateConsumableObject) {
    GameObject *obj = factory->createGameObject("klein levenselixer");
    ASSERT_NE(obj, nullptr);
    EXPECT_EQ(obj->getName(), "klein levenselixer1");
    EXPECT_EQ(obj->getType(), ObjectType::Consumable_Health);
    EXPECT_EQ(static_cast<ConsumableObject*>(obj)->getMin(), 1);
    EXPECT_EQ(static_cast<ConsumableObject*>(obj)->getMax(), 10);
    delete obj;
}

TEST_F(GameObjectFactoryTest, CreateRandomGameObject) {
    GameObject *obj = factory->createGameObject();
    ASSERT_NE(obj, nullptr);
    EXPECT_FALSE(obj->getName().empty());
    delete obj;
}

TEST_F(GameObjectFactoryTest, CreateGameObjectNotFound) {
    GameObject *obj = factory->createGameObject("Unknown Object");
    EXPECT_EQ(obj, nullptr);
}