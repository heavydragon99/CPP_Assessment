#include <gtest/gtest.h>
#include "ConsumableObject.h"
#include "WeaponObject.h"
#include "GoldObject.h"
#include "ArmorObject.h"
#include "Sean.h"

// Test for ArmorObject
class ArmorObjectTest : public ::testing::Test {
protected:
    ArmorObject *armorObject;

    void SetUp() override {
        armorObject = new ArmorObject("Test Armor", "A sturdy piece of armor.", 50, ObjectType::Armor, 1);
    }

    void TearDown() override {
        delete armorObject;
    }
};

TEST_F(ArmorObjectTest, Constructor) {
    EXPECT_EQ(armorObject->getName(), "Test Armor1");
    EXPECT_EQ(armorObject->getArmor(), 50);
    EXPECT_EQ(armorObject->getType(), ObjectType::Armor);
}

TEST_F(ArmorObjectTest, CopyConstructor) {
    ArmorObject copy(*armorObject);
    EXPECT_EQ(copy.getName(), "Test Armor1");
    EXPECT_EQ(copy.getArmor(), 50);
    EXPECT_EQ(copy.getType(), ObjectType::Armor);
}

TEST_F(ArmorObjectTest, MoveConstructor) {
    ArmorObject moved(std::move(*armorObject));
    EXPECT_EQ(moved.getName(), "Test Armor1");
    EXPECT_EQ(moved.getArmor(), 50);
    EXPECT_EQ(moved.getType(), ObjectType::Armor);
    EXPECT_EQ(armorObject->getArmor(), 0); // Original object should be in a valid but unspecified state
}

TEST_F(ArmorObjectTest, CopyAssignmentOperator) {
    ArmorObject copy("Other Armor", "Another piece of armor.", 30, ObjectType::Armor, 2);
    copy = *armorObject;
    EXPECT_EQ(copy.getName(), "Test Armor1");
    EXPECT_EQ(copy.getArmor(), 50);
    EXPECT_EQ(copy.getType(), ObjectType::Armor);
}

TEST_F(ArmorObjectTest, MoveAssignmentOperator) {
    ArmorObject moved("Other Armor", "Another piece of armor.", 30, ObjectType::Armor, 2);
    moved = std::move(*armorObject);
    EXPECT_EQ(moved.getName(), "Test Armor1");
    EXPECT_EQ(moved.getArmor(), 50);
    EXPECT_EQ(moved.getType(), ObjectType::Armor);
    EXPECT_EQ(armorObject->getArmor(), 0); // Original object should be in a valid but unspecified state
}

TEST_F(ArmorObjectTest, Clone) {
    IGameObject *clone = armorObject->clone();
    EXPECT_EQ(clone->getName(), "Test Armor1");
    EXPECT_EQ(static_cast<ArmorObject*>(clone)->getArmor(), 50);
    EXPECT_EQ(static_cast<GameObject*>(clone)->getType(), ObjectType::Armor);
    delete clone;
}

TEST_F(ArmorObjectTest, PrintDescription) {
    testing::internal::CaptureStdout();
    armorObject->printDescription();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "A sturdy piece of armor.\nArmor: 50\n");
}

TEST_F(ArmorObjectTest, GetArmor) {
    EXPECT_EQ(armorObject->getArmor(), 50);
}

TEST_F(ArmorObjectTest, GetValue) {
    EXPECT_EQ(armorObject->getValue(), 50);
}

TEST_F(ArmorObjectTest, GetMin) {
    EXPECT_EQ(armorObject->getMin(), 50);
}

TEST_F(ArmorObjectTest, GetMax) {
    EXPECT_EQ(armorObject->getMax(), 50);
}

// Test for ConsumableObject
class ConsumableObjectTest : public ::testing::Test {
protected:
    ConsumableObject *consumableObject;

    void SetUp() override {
        consumableObject = new ConsumableObject("Health Potion", "Restores health.", 10, 20, ObjectType::Consumable_Health, 1);
    }

    void TearDown() override {
        delete consumableObject;
    }
};

TEST_F(ConsumableObjectTest, Constructor) {
    EXPECT_EQ(consumableObject->getName(), "Health Potion1");
    EXPECT_EQ(consumableObject->getMin(), 10);
    EXPECT_EQ(consumableObject->getMax(), 20);
    EXPECT_EQ(consumableObject->getType(), ObjectType::Consumable_Health);
}

TEST_F(ConsumableObjectTest, CopyConstructor) {
    ConsumableObject copy(*consumableObject);
    EXPECT_EQ(copy.getName(), "Health Potion1");
    EXPECT_EQ(copy.getMin(), 10);
    EXPECT_EQ(copy.getMax(), 20);
    EXPECT_EQ(copy.getType(), ObjectType::Consumable_Health);
}

TEST_F(ConsumableObjectTest, MoveConstructor) {
    ConsumableObject moved(std::move(*consumableObject));
    EXPECT_EQ(moved.getName(), "Health Potion1");
    EXPECT_EQ(moved.getMin(), 10);
    EXPECT_EQ(moved.getMax(), 20);
    EXPECT_EQ(moved.getType(), ObjectType::Consumable_Health);
    EXPECT_EQ(consumableObject->getMin(), 0); // Original object should be in a valid but unspecified state
    EXPECT_EQ(consumableObject->getMax(), 0); // Original object should be in a valid but unspecified state
}

TEST_F(ConsumableObjectTest, CopyAssignmentOperator) {
    ConsumableObject copy("Experience Potion", "Increases experience.", 5, 15, ObjectType::Consumable_Experience, 2);
    copy = *consumableObject;
    EXPECT_EQ(copy.getName(), "Health Potion1");
    EXPECT_EQ(copy.getMin(), 10);
    EXPECT_EQ(copy.getMax(), 20);
    EXPECT_EQ(copy.getType(), ObjectType::Consumable_Health);
}

TEST_F(ConsumableObjectTest, MoveAssignmentOperator) {
    ConsumableObject moved("Experience Potion", "Increases experience.", 5, 15, ObjectType::Consumable_Experience, 2);
    moved = std::move(*consumableObject);
    EXPECT_EQ(moved.getName(), "Health Potion1");
    EXPECT_EQ(moved.getMin(), 10);
    EXPECT_EQ(moved.getMax(), 20);
    EXPECT_EQ(moved.getType(), ObjectType::Consumable_Health);
    EXPECT_EQ(consumableObject->getMin(), 0); // Original object should be in a valid but unspecified state
    EXPECT_EQ(consumableObject->getMax(), 0); // Original object should be in a valid but unspecified state
}

TEST_F(ConsumableObjectTest, Clone) {
    IGameObject *clone = consumableObject->clone();
    EXPECT_EQ(clone->getName(), "Health Potion1");
    EXPECT_EQ(static_cast<ConsumableObject*>(clone)->getMin(), 10);
    EXPECT_EQ(static_cast<ConsumableObject*>(clone)->getMax(), 20);
    EXPECT_EQ(static_cast<GameObject*>(clone)->getType(), ObjectType::Consumable_Health);
    delete clone;
}

TEST_F(ConsumableObjectTest, PrintDescription) {
    testing::internal::CaptureStdout();
    consumableObject->printDescription();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Restores health.\nSterkte tussen: 10 - 20\n");
}

TEST_F(ConsumableObjectTest, GetValue) {
    int value = consumableObject->getValue();
    EXPECT_GE(value, 10);
    EXPECT_LE(value, 20);
}

TEST_F(ConsumableObjectTest, GetMin) {
    EXPECT_EQ(consumableObject->getMin(), 10);
}

TEST_F(ConsumableObjectTest, GetMax) {
    EXPECT_EQ(consumableObject->getMax(), 20);
}

// Tests for WeaponObject
class WeaponObjectTest : public ::testing::Test {
protected:
    WeaponObject *weaponObject;

    void SetUp() override {
        weaponObject = new WeaponObject("Sword", "A sharp blade.", 5, 10, ObjectType::Weapon, 1);
    }

    void TearDown() override {
        delete weaponObject;
    }
};

TEST_F(WeaponObjectTest, Constructor) {
    EXPECT_EQ(weaponObject->getName(), "Sword1");
    EXPECT_EQ(weaponObject->getMin(), 5);
    EXPECT_EQ(weaponObject->getMax(), 10);
    EXPECT_EQ(weaponObject->getType(), ObjectType::Weapon);
}

TEST_F(WeaponObjectTest, CopyConstructor) {
    WeaponObject copy(*weaponObject);
    EXPECT_EQ(copy.getName(), "Sword1");
    EXPECT_EQ(copy.getMin(), 5);
    EXPECT_EQ(copy.getMax(), 10);
    EXPECT_EQ(copy.getType(), ObjectType::Weapon);
}

TEST_F(WeaponObjectTest, MoveConstructor) {
    WeaponObject moved(std::move(*weaponObject));
    EXPECT_EQ(moved.getName(), "Sword1");
    EXPECT_EQ(moved.getMin(), 5);
    EXPECT_EQ(moved.getMax(), 10);
    EXPECT_EQ(moved.getType(), ObjectType::Weapon);
    EXPECT_EQ(weaponObject->getMin(), 0); // Original object should be in a valid but unspecified state
    EXPECT_EQ(weaponObject->getMax(), 0); // Original object should be in a valid but unspecified state
}

TEST_F(WeaponObjectTest, CopyAssignmentOperator) {
    WeaponObject copy("Axe", "A heavy axe.", 7, 12, ObjectType::Weapon, 2);
    copy = *weaponObject;
    EXPECT_EQ(copy.getName(), "Sword1");
    EXPECT_EQ(copy.getMin(), 5);
    EXPECT_EQ(copy.getMax(), 10);
    EXPECT_EQ(copy.getType(), ObjectType::Weapon);
}

TEST_F(WeaponObjectTest, MoveAssignmentOperator) {
    WeaponObject moved("Axe", "A heavy axe.", 7, 12, ObjectType::Weapon, 2);
    moved = std::move(*weaponObject);
    EXPECT_EQ(moved.getName(), "Sword1");
    EXPECT_EQ(moved.getMin(), 5);
    EXPECT_EQ(moved.getMax(), 10);
    EXPECT_EQ(moved.getType(), ObjectType::Weapon);
    EXPECT_EQ(weaponObject->getMin(), 0); // Original object should be in a valid but unspecified state
    EXPECT_EQ(weaponObject->getMax(), 0); // Original object should be in a valid but unspecified state
}

TEST_F(WeaponObjectTest, Clone) {
    IGameObject *clone = weaponObject->clone();
    EXPECT_EQ(clone->getName(), "Sword1");
    EXPECT_EQ(static_cast<WeaponObject*>(clone)->getMin(), 5);
    EXPECT_EQ(static_cast<WeaponObject*>(clone)->getMax(), 10);
    EXPECT_EQ(static_cast<GameObject*>(clone)->getType(), ObjectType::Weapon);
    delete clone;
}

TEST_F(WeaponObjectTest, PrintDescription) {
    testing::internal::CaptureStdout();
    weaponObject->printDescription();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "A sharp blade.\nSchade tussen: 5 - 10\n");
}

TEST_F(WeaponObjectTest, GetDamage) {
    int damage = weaponObject->getDamage();
    EXPECT_GE(damage, 5);
    EXPECT_LE(damage, 10);
}

TEST_F(WeaponObjectTest, GetValue) {
    int value = weaponObject->getValue();
    EXPECT_GE(value, 5);
    EXPECT_LE(value, 10);
}

// Tests for GoldObject
class GoldObjectTest : public ::testing::Test {
protected:
    GoldObject *goldObject;

    void SetUp() override {
        goldObject = new GoldObject("Gold Coins", "A pile of gold coins.", 100, 200, ObjectType::Gold, 1);
    }

    void TearDown() override {
        delete goldObject;
    }
};

TEST_F(GoldObjectTest, Constructor) {
    EXPECT_EQ(goldObject->getName(), "Gold Coins1");
    EXPECT_EQ(goldObject->getMin(), 100);
    EXPECT_EQ(goldObject->getMax(), 200);
    EXPECT_EQ(goldObject->getType(), ObjectType::Gold);
}

TEST_F(GoldObjectTest, CopyConstructor) {
    GoldObject copy(*goldObject);
    EXPECT_EQ(copy.getName(), "Gold Coins1");
    EXPECT_EQ(copy.getMin(), 100);
    EXPECT_EQ(copy.getMax(), 200);
    EXPECT_EQ(copy.getType(), ObjectType::Gold);
}

TEST_F(GoldObjectTest, MoveConstructor) {
    GoldObject moved(std::move(*goldObject));
    EXPECT_EQ(moved.getName(), "Gold Coins1");
    EXPECT_EQ(moved.getMin(), 100);
    EXPECT_EQ(moved.getMax(), 200);
    EXPECT_EQ(moved.getType(), ObjectType::Gold);
    EXPECT_EQ(goldObject->getMin(), 0); // Original object should be in a valid but unspecified state
    EXPECT_EQ(goldObject->getMax(), 0); // Original object should be in a valid but unspecified state
}

TEST_F(GoldObjectTest, CopyAssignmentOperator) {
    GoldObject copy("Silver Coins", "A pile of silver coins.", 50, 100, ObjectType::Gold, 2);
    copy = *goldObject;
    EXPECT_EQ(copy.getName(), "Gold Coins1");
    EXPECT_EQ(copy.getMin(), 100);
    EXPECT_EQ(copy.getMax(), 200);
    EXPECT_EQ(copy.getType(), ObjectType::Gold);
}

TEST_F(GoldObjectTest, MoveAssignmentOperator) {
    GoldObject moved("Silver Coins", "A pile of silver coins.", 50, 100, ObjectType::Gold, 2);
    moved = std::move(*goldObject);
    EXPECT_EQ(moved.getName(), "Gold Coins1");
    EXPECT_EQ(moved.getMin(), 100);
    EXPECT_EQ(moved.getMax(), 200);
    EXPECT_EQ(moved.getType(), ObjectType::Gold);
    EXPECT_EQ(goldObject->getMin(), 0); // Original object should be in a valid but unspecified state
    EXPECT_EQ(goldObject->getMax(), 0); // Original object should be in a valid but unspecified state
}

TEST_F(GoldObjectTest, Clone) {
    IGameObject *clone = goldObject->clone();
    EXPECT_EQ(clone->getName(), "Gold Coins1");
    EXPECT_EQ(static_cast<GoldObject*>(clone)->getMin(), 100);
    EXPECT_EQ(static_cast<GoldObject*>(clone)->getMax(), 200);
    EXPECT_EQ(static_cast<GameObject*>(clone)->getType(), ObjectType::Gold);
    delete clone;
}

TEST_F(GoldObjectTest, PrintDescription) {
    testing::internal::CaptureStdout();
    goldObject->printDescription();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "A pile of gold coins.\nBevat tussen 100 - 200 goudstukken\n");
}

TEST_F(GoldObjectTest, GetValue) {
    int value = goldObject->getValue();
    EXPECT_GE(value, 100);
    EXPECT_LE(value, 200);
}

TEST_F(GoldObjectTest, GetMin) {
    EXPECT_EQ(goldObject->getMin(), 100);
}

TEST_F(GoldObjectTest, GetMax) {
    EXPECT_EQ(goldObject->getMax(), 200);
}