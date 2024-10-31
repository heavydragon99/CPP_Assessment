#include <gtest/gtest.h>
#include "Location.h"
#include "ConsumableObject.h"
#include "Enemy.h"
#include "Sean.h"

class LocationTest : public ::testing::Test {
protected:
    Location *location;
    Location *northLocation;
    Location *eastLocation;
    Location *southLocation;
    Location *westLocation;

    void SetUp() override {
        location = new Location("Main Room", "This is the main room.", 1);
        northLocation = new Location("North Room", "This is the north room.", 2);
        eastLocation = new Location("East Room", "This is the east room.", 3);
        southLocation = new Location("South Room", "This is the south room.", 4);
        westLocation = new Location("West Room", "This is the west room.", 5);
    }

    void TearDown() override {
        delete location;
        delete northLocation;
        delete eastLocation;
        delete southLocation;
        delete westLocation;
    }
};

TEST_F(LocationTest, PrintExits_NoExits) {
    testing::internal::CaptureStdout();
    location->printExits();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Uitgangen: \n");
}

TEST_F(LocationTest, PrintExits_NorthExit) {
    location->setExit(Sean::Direction::North, northLocation);
    testing::internal::CaptureStdout();
    location->printExits();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Uitgangen: noord \n");
}

TEST_F(LocationTest, PrintExits_EastExit) {
    location->setExit(Sean::Direction::East, eastLocation);
    testing::internal::CaptureStdout();
    location->printExits();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Uitgangen: oost \n");
}

TEST_F(LocationTest, PrintExits_SouthExit) {
    location->setExit(Sean::Direction::South, southLocation);
    testing::internal::CaptureStdout();
    location->printExits();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Uitgangen: zuid \n");
}

TEST_F(LocationTest, PrintExits_WestExit) {
    location->setExit(Sean::Direction::West, westLocation);
    testing::internal::CaptureStdout();
    location->printExits();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Uitgangen: west \n");
}

TEST_F(LocationTest, PrintExits_MultipleExits) {
    location->setExit(Sean::Direction::North, northLocation);
    location->setExit(Sean::Direction::East, eastLocation);
    testing::internal::CaptureStdout();
    location->printExits();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Uitgangen: noord oost \n");
}

TEST_F(LocationTest, AddVisibleObject) {
    ConsumableObject *obj = new ConsumableObject("Object", "Description1", 10, 20, ObjectType::Consumable_Health, 1);
    location->addVisibleObject(obj);
    auto &visibleObjects = location->getVisibleObjects();
    ASSERT_EQ(visibleObjects.size(), 1);
    EXPECT_EQ(visibleObjects[0]->getName(), "Object1");
}

TEST_F(LocationTest, AddHiddenObject) {
    ConsumableObject *obj = new ConsumableObject("Object", "Description2", 5, 15, ObjectType::Consumable_Experience, 2);
    location->addHiddenObject(obj);
    auto &hiddenObjects = location->getHiddenObjects();
    ASSERT_EQ(hiddenObjects.size(), 1);
    EXPECT_EQ(hiddenObjects[0]->getName(), "Object2");
}

TEST_F(LocationTest, AddEnemy) {
    Enemy enemy("Enemy", "Description1", 100, 50, 10, 20, 1);
    location->addEnemy(enemy);
    auto &enemies = location->getEnemies();
    ASSERT_EQ(enemies.size(), 1);
    EXPECT_EQ(enemies[0].getName(), "Enemy1");
}

TEST_F(LocationTest, RemoveEnemy) {
    Enemy enemy("Enemy", "Description2", 100, 50, 10, 20, 2);
    location->addEnemy(enemy);
    location->removeEnemy("Enemy2");
    auto &enemies = location->getEnemies();
    EXPECT_EQ(enemies.size(), 0);
}

TEST_F(LocationTest, GetEnemies) {
    Enemy enemy("Enemy", "Description3", 100, 50, 10, 20, 3);
    location->addEnemy(enemy);
    Sean::Vector<Enemy> &enemies = location->getEnemies();
    ASSERT_EQ(enemies.size(), 1);
    EXPECT_EQ(enemies[0].getName(), "Enemy3");
}

TEST_F(LocationTest, SetAndGetExit) {
    location->setExit(Sean::Direction::North, northLocation);
    EXPECT_EQ(location->getExit(Sean::Direction::North), northLocation);
}

TEST_F(LocationTest, PrintDescriptionShort) {
    testing::internal::CaptureStdout();
    location->printDescriptionShort();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Je staat in de locatie: Main Room\n");
}

TEST_F(LocationTest, PrintDescriptionLong) {
    testing::internal::CaptureStdout();
    location->printDescriptionLong();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Je staat in de locatie: Main Room\nThis is the main room.\nObjecten:\n\tgeen\nVijanden:\n\tgeen\n");
}

TEST_F(LocationTest, MoveHiddenObjects) {
    ConsumableObject *obj = new ConsumableObject("Object", "Description3", 10, 20, ObjectType::Consumable_Health, 3);
    location->addHiddenObject(obj);
    location->moveHiddenObjects();
    auto &visibleObjects = location->getVisibleObjects();
    ASSERT_EQ(visibleObjects.size(), 1);
    EXPECT_EQ(visibleObjects[0]->getName(), "Object3");
    auto &hiddenObjects = location->getHiddenObjects();
    EXPECT_EQ(hiddenObjects.size(), 0);
}

TEST_F(LocationTest, PickUpObject) {
    ConsumableObject *obj = new ConsumableObject("Object", "Description4", 5, 15, ObjectType::Consumable_Experience, 4);
    location->addVisibleObject(obj);
    GameObject *pickedUpObj = location->pickUpObject("Object4");
    EXPECT_EQ(pickedUpObj, obj);
    auto &visibleObjects = location->getVisibleObjects();
    EXPECT_EQ(visibleObjects.size(), 0);
    delete obj;
}

TEST_F(LocationTest, PrintObject) {
    ConsumableObject *obj = new ConsumableObject("Object", "Description5", 1, 10, ObjectType::Consumable_Teleport, 5);
    location->addVisibleObject(obj);
    testing::internal::CaptureStdout();
    bool found = location->printObject("Object5");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(found);
    EXPECT_NE(output.find("Object5"), std::string::npos);
}