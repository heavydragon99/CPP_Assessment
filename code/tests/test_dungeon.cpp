#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Dungeon.h"
#include "Location.h"
#include "Enemy.h"
#include "GameObject.h"
#include "ConsumableObject.h"
#include "Sean.h"

class MockLocationFactory
{
public:
    MOCK_METHOD(Location *, createLocation, (const Sean::String &aLocation, const Sean::String &aDescription), ());
    MOCK_METHOD(Location *, createLocation, (const Sean::String &aLocation, const Sean::String &aDescription, const int aId), ());
    MOCK_METHOD(Location *, createLocation, (), ());
};

class MockEnemyFactory
{
public:
    MOCK_METHOD(Enemy *, createEnemy, (const Sean::String &aEnemyName), ());
    MOCK_METHOD(Enemy *, createEnemy, (), ());
};

class MockGameObjectFactory
{
public:
    MOCK_METHOD(GameObject *, createGameObject, (const Sean::String &aName), ());
    MOCK_METHOD(GameObject *, createGameObject, (), ());
};

class MockRandomGenerator
{
public:
    MOCK_METHOD(int, generate, (int min, int max), ());
};

class DungeonTest : public ::testing::Test
{
protected:
    Dungeon *dungeon;
    Sean::Vector<Sean::ParsedLocations> parsedLocations;
    MockLocationFactory mockLocationFactory;
    MockEnemyFactory mockEnemyFactory;
    MockGameObjectFactory mockGameObjectFactory;
    MockRandomGenerator mockRandomGenerator;

    void SetUp() override
    {
        // Setup mock data for parsedLocations
        Sean::ParsedLocations loc1;
        loc1.mName = "De IJzeren Burcht";
        loc1.mDescription = "Een fort van verroest metaal en ijzeren kettingen, gevuld met mechanische vallen en oude oorlogsmachines.";
        loc1.mId = 1;
        loc1.mEnemies.push_back("Kobold");
        loc1.mVisibleObjects.push_back("harnas");
        loc1.mHiddenObjects.push_back("kleine ervaringsdrank");
        loc1.mDirections[0].mDirection = Sean::Direction::North;
        loc1.mDirections[0].mID = 2;
        parsedLocations.push_back(loc1);

        Sean::ParsedLocations loc2;
        loc2.mName = "De Verzopen Crypte";
        loc2.mDescription = "Een oude begraafplaats ondergedompeld in een donker, modderig moeras.";
        loc2.mId = 2;
        loc2.mEnemies.push_back("Wolf");
        loc2.mVisibleObjects.push_back("zacht leren wapenrusting");
        loc2.mHiddenObjects.push_back("middelgroot levenselixer");
        parsedLocations.push_back(loc2);

        dungeon = new Dungeon(parsedLocations);
    }

    void TearDown() override
    {
        delete dungeon;
    }
};

TEST_F(DungeonTest, ConstructorWithParsedLocations)
{
    ASSERT_EQ(dungeon->getCurrentLocation().getName(), "De IJzeren Burcht1");
}

TEST_F(DungeonTest, ConstructorWithInteger)
{
    Dungeon dungeon(2);
    ASSERT_FALSE(dungeon.getCurrentLocation().getName().empty());
}

TEST_F(DungeonTest, Update)
{
    int damage = dungeon->update();
    ASSERT_GE(damage, 0);
}

TEST_F(DungeonTest, CreateGameObject)
{
    GameObject *obj = dungeon->createGameObject("harnas");
    ASSERT_NE(obj, nullptr);
    delete obj;
}

TEST_F(DungeonTest, PickUpObject)
{
    std::string objectName = dungeon->getCurrentLocation().getVisibleObjects()[0]->getName().c_str();
    GameObject *obj = dungeon->pickUpObject(objectName.c_str());
    ASSERT_NE(obj, nullptr);
    delete obj;
}

TEST_F(DungeonTest, PlaceObject)
{
    GameObject *obj = new ConsumableObject("harnas", "Description1", 1, 3, ObjectType::Gold, 1);
    dungeon->placeObject(obj);
    auto &visibleObjects = dungeon->getCurrentLocation().getVisibleObjects();
    ASSERT_EQ(visibleObjects.size(), 2);
    EXPECT_EQ(visibleObjects[1]->getName(), "harnas1");
}

TEST_F(DungeonTest, PrintShortDescription)
{
    testing::internal::CaptureStdout();
    dungeon->printShortDescription();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Je staat in de locatie: De IJzeren Burcht\n");
}

TEST_F(DungeonTest, PrintLongDescription)
{
    testing::internal::CaptureStdout();
    dungeon->printLongDescription();
    std::string output = testing::internal::GetCapturedStdout();
    std::vector<std::string> objecten;
    std::vector<std::string> vijanden;
    for(int i = 0; i < dungeon->getCurrentLocation().getVisibleObjects().size(); i++)
    {
        objecten.push_back(dungeon->getCurrentLocation().getVisibleObjects()[i]->getName().c_str());
    }
    for(int i = 0; i < dungeon->getCurrentLocation().getEnemies().size(); i++)
    {
        vijanden.push_back(dungeon->getCurrentLocation().getEnemies()[i].getName().c_str());
    }
    std::string outputString = "Je staat in de locatie: De IJzeren Burcht\nEen fort van verroest metaal en ijzeren kettingen, gevuld met mechanische vallen en oude oorlogsmachines.\nObjecten:\n";
    if (objecten.empty()) {
        outputString += "\tgeen\n";
    } else {
        for (const auto &obj : objecten) {
            outputString += "\t" + obj + "\n";
        }
    }
    outputString += "Vijanden:\n";
    if (vijanden.empty()) {
        outputString += "\tgeen\n";
    } else {
        for (const auto &vijand : vijanden) {
            outputString += "\t" + vijand + "\n";
        }
    }
    outputString += "Uitgangen: Noord \n";
    EXPECT_EQ(output, outputString);
}

TEST_F(DungeonTest, ValidLocation)
{
    EXPECT_TRUE(dungeon->validLocation(Sean::Direction::North));
}

TEST_F(DungeonTest, MoveLocation)
{
    EXPECT_TRUE(dungeon->moveLocation(Sean::Direction::North));
}

TEST_F(DungeonTest, MoveHiddenObjects)
{
    dungeon->moveHiddenObjects();
    std::string objectName = dungeon->getCurrentLocation().getVisibleObjects()[1]->getName().c_str();
    auto &visibleObjects = dungeon->getCurrentLocation().getVisibleObjects();
    ASSERT_EQ(visibleObjects.size(), 2);
    EXPECT_EQ(visibleObjects[1]->getName(), objectName.c_str());
}

TEST_F(DungeonTest, PrintObject)
{
    testing::internal::CaptureStdout();
    std::string objectName = dungeon->getCurrentLocation().getVisibleObjects()[0]->getName().c_str();
    bool found = dungeon->printObject(objectName.c_str());
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(found);
    EXPECT_NE(output.find("harnas"), std::string::npos);
}

TEST_F(DungeonTest, Teleport)
{
    dungeon->teleport(1);
    EXPECT_NE(dungeon->getCurrentLocation().getName(), "De IJzeren Burcht1");
}

TEST_F(DungeonTest, AttackEnemy)
{
    std::string enemyName = dungeon->getCurrentLocation().getEnemies()[0].getName().c_str();
    bool result = dungeon->attackEnemy(enemyName.c_str(), 10);
    EXPECT_TRUE(result);
}