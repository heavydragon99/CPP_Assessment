#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Player.h"
#include "IGameObject.h"
#include <memory>

// Mock class for IGameObject
class MockGameObject : public IGameObject
{
public:
    MockGameObject() = default;
    MockGameObject(const MockGameObject &other) : IGameObject(other)
    {
        // Define the copy constructor
    }
    MOCK_METHOD(IGameObject *, clone, (), (const, override));
    MOCK_METHOD(Sean::String, getName, (), (const, override));
    MOCK_METHOD(void, printName, (), (const, override));
    MOCK_METHOD(void, printDescription, (), (const, override));
    MOCK_METHOD(bool, isWeapon, (), (const, override));
    MOCK_METHOD(bool, isArmor, (), (const, override));
    MOCK_METHOD(bool, isConsumableHealth, (), (const, override));
    MOCK_METHOD(bool, isConsumableExperience, (), (const, override));
    MOCK_METHOD(bool, isConsumableTeleport, (), (const, override));
    MOCK_METHOD(bool, isMoney, (), (const, override));
    MOCK_METHOD(int, getValue, (), (const, override));
    MOCK_METHOD(int, getMin, (), (const, override));
    MOCK_METHOD(int, getMax, (), (const, override));
};

// Test fixture class for Player
class PlayerTest : public ::testing::Test
{
protected:
    Player *player;
    std::streambuf *orig_cin;
    std::istringstream input;

    void SetUp() override
    {
        // Redirect std::cin to simulate user input
        orig_cin = std::cin.rdbuf();
        input.str("TestPlayer\n");
        std::cin.rdbuf(input.rdbuf());

        testing::internal::CaptureStdout();

        player = new Player();

        std::string output = testing::internal::GetCapturedStdout();
    }

    void TearDown() override
    {
        delete player;

        // Restore std::cin
        std::cin.rdbuf(orig_cin);
    }
};

// Test for printDescription method
TEST_F(PlayerTest, PrintDescription)
{
    testing::internal::CaptureStdout();
    player->printDescription();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Naam: "), std::string::npos);
    EXPECT_NE(output.find("Levenspunten: "), std::string::npos);
    EXPECT_NE(output.find("Aanvalskans: "), std::string::npos);
    EXPECT_NE(output.find("Goud: "), std::string::npos);
    EXPECT_NE(output.find("Uitgeruste wapen: "), std::string::npos);
    EXPECT_NE(output.find("Uitgeruste pantser: "), std::string::npos);
    EXPECT_NE(output.find("Inventaris: "), std::string::npos);
    EXPECT_NE(output.find("Godmode: "), std::string::npos);
}

// Test for equipObject method
TEST_F(PlayerTest, EquipObject)
{
    auto mockObject = std::make_unique<MockGameObject>();
    EXPECT_CALL(*mockObject, getName()).WillRepeatedly(::testing::Return("Sword"));
    EXPECT_CALL(*mockObject, isWeapon()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(*mockObject, isMoney()).WillRepeatedly(::testing::Return(false));
    player->addObject(std::move(mockObject));
    auto previousItem = player->equipObject("Sword");
    EXPECT_EQ(previousItem, nullptr);
}

// Test for removeEquippedItem method
TEST_F(PlayerTest, RemoveEquippedItem)
{
    auto mockObject = std::make_unique<MockGameObject>();
    EXPECT_CALL(*mockObject, getName()).WillRepeatedly(::testing::Return("Sword"));
    EXPECT_CALL(*mockObject, isWeapon()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(*mockObject, isMoney()).WillRepeatedly(::testing::Return(false));
    player->addObject(std::move(mockObject));
    player->equipObject("Sword");
    player->removeEquippedItem(player->getInventory().front().get());
    EXPECT_EQ(player->getInventory().size(), 0);
}

// Test for addHealth method
TEST_F(PlayerTest, AddHealth)
{
    player->addHealth(10);
    EXPECT_EQ(player->getHealth(), 30);
    player->addHealth(-40);
    EXPECT_EQ(player->getHealth(), 0);
}

// Test for addExperience method
TEST_F(PlayerTest, AddExperience)
{
    player->addExperience(10);
    EXPECT_EQ(player->getAttackPercentage(), 50);
}

// Test for addObject method
TEST_F(PlayerTest, AddObject)
{
    auto mockObject = std::make_unique<MockGameObject>();
    EXPECT_CALL(*mockObject, isMoney()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(*mockObject, getValue()).WillRepeatedly(::testing::Return(50));
    player->addObject(std::move(mockObject));
    EXPECT_EQ(player->getGold(), 50);
}

// Test for printObject method
TEST_F(PlayerTest, PrintObject)
{
    auto mockObject = std::make_unique<MockGameObject>();
    EXPECT_CALL(*mockObject, getName()).WillRepeatedly(::testing::Return("Sword"));
    EXPECT_CALL(*mockObject, isMoney()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(*mockObject, printName()).Times(1);
    EXPECT_CALL(*mockObject, printDescription()).Times(1);
    player->addObject(std::move(mockObject));
    EXPECT_TRUE(player->printObject("Sword"));
}

// Test for dropObject method
TEST_F(PlayerTest, DropObject)
{
    auto mockObject = std::make_unique<MockGameObject>();
    EXPECT_CALL(*mockObject, getName()).WillRepeatedly(::testing::Return("Sword"));
    EXPECT_CALL(*mockObject, isMoney()).WillRepeatedly(::testing::Return(false));
    player->addObject(std::move(mockObject));
    auto droppedItem = player->dropObject("Sword");
    EXPECT_NE(droppedItem, nullptr);
    EXPECT_EQ(player->getInventory().size(), 0);
}

// Test for toggleGodMode method
TEST_F(PlayerTest, ToggleGodMode)
{
    player->toggleGodMode();
    player->addHealth(-20);
    EXPECT_EQ(player->getHealth(), 20);
    player->toggleGodMode();
    player->addHealth(-20);
    EXPECT_TRUE(player->isDead());
}

// Test for getInventory method
TEST_F(PlayerTest, GetInventory)
{
    auto &inventory = player->getInventory();
    EXPECT_EQ(inventory.size(), 0);
}

// Test for getHealth method
TEST_F(PlayerTest, GetHealth)
{
    EXPECT_EQ(player->getHealth(), 20);
}

// Test for getAttackPercentage method
TEST_F(PlayerTest, GetAttackPercentage)
{
    EXPECT_EQ(player->getAttackPercentage(), 40);
}

// Test for getAttackDamage method
TEST_F(PlayerTest, GetAttackDamage)
{
    auto mockObject = std::make_unique<MockGameObject>();
    EXPECT_CALL(*mockObject, getName()).WillRepeatedly(::testing::Return("Sword"));
    EXPECT_CALL(*mockObject, isWeapon()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(*mockObject, getValue()).WillRepeatedly(::testing::Return(10));
    EXPECT_CALL(*mockObject, isMoney()).WillRepeatedly(::testing::Return(false));
    player->addObject(std::move(mockObject));
    player->equipObject("Sword");
    int attackDamage = player->getAttackDamage();
    EXPECT_GE(attackDamage, 0);
    EXPECT_LE(attackDamage, 10);
}

// Test for isDead method
TEST_F(PlayerTest, IsDead)
{
    EXPECT_FALSE(player->isDead());
    player->addHealth(-20);
    EXPECT_TRUE(player->isDead());
}

// Test for getGold method
TEST_F(PlayerTest, GetGold)
{
    EXPECT_EQ(player->getGold(), 0);
}

// Test for getName method
TEST_F(PlayerTest, GetName)
{
    EXPECT_EQ(player->getName(), "TestPlayer");
}

// Test for equipping and removing weapon
TEST_F(PlayerTest, EquipAndRemoveWeapon)
{
    auto mockWeapon = std::make_unique<MockGameObject>();
    auto mockWeapon2 = std::make_unique<MockGameObject>();
    EXPECT_CALL(*mockWeapon, getName()).WillRepeatedly(::testing::Return("Sword"));
    EXPECT_CALL(*mockWeapon, isWeapon()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(*mockWeapon, isMoney()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(*mockWeapon, clone()).WillRepeatedly(::testing::Return(new MockGameObject(*mockWeapon)));
    EXPECT_CALL(*mockWeapon2, getName()).WillRepeatedly(::testing::Return("Axe"));
    EXPECT_CALL(*mockWeapon2, isWeapon()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(*mockWeapon2, isMoney()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(*mockWeapon2, clone()).WillRepeatedly(::testing::Return(new MockGameObject(*mockWeapon2)));
    player->addObject(std::move(mockWeapon));
    player->addObject(std::move(mockWeapon2));
    auto previousItem = player->equipObject("Sword");
    EXPECT_EQ(previousItem, nullptr);
    EXPECT_EQ(player->getInventory().size(), 2);
    EXPECT_EQ(player->equipObject("Sword"), nullptr);
    auto previousItem2 = player->equipObject("Axe");
    EXPECT_NE(previousItem2, nullptr);
    EXPECT_EQ(player->getInventory().size(), 1);
}

// Test for equipping and removing armor
TEST_F(PlayerTest, EquipAndRemoveArmor)
{
    auto mockArmor = std::make_unique<MockGameObject>();
    auto mockArmor2 = std::make_unique<MockGameObject>();

    EXPECT_CALL(*mockArmor, getName()).WillRepeatedly(::testing::Return("Shield"));
    EXPECT_CALL(*mockArmor, isArmor()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(*mockArmor, isMoney()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(*mockArmor, isWeapon()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(*mockArmor, clone()).WillRepeatedly(::testing::Return(new MockGameObject(*mockArmor)));

    EXPECT_CALL(*mockArmor2, getName()).WillRepeatedly(::testing::Return("Helmet"));
    EXPECT_CALL(*mockArmor2, isArmor()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(*mockArmor2, isMoney()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(*mockArmor2, isWeapon()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(*mockArmor2, clone()).WillRepeatedly(::testing::Return(new MockGameObject(*mockArmor2)));

    player->addObject(std::move(mockArmor));
    player->addObject(std::move(mockArmor2));
    auto previousItem = player->equipObject("Shield");
    EXPECT_EQ(previousItem, nullptr);
    EXPECT_EQ(player->getInventory().size(), 2);
    EXPECT_EQ(player->equipObject("Shield"), nullptr);
    auto previousItem2 = player->equipObject("Helmet");
    EXPECT_NE(previousItem2, nullptr);
    EXPECT_EQ(player->getInventory().size(), 1);
}