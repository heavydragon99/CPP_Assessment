#include <gtest/gtest.h>
#include "XmlReader.h"
#include "Sean.h"
#include "tinyxml2.h"

#define XMLPATH "/home/sean/school_stuff/leerjaar_4/minor/cpp/assessment-cplus-24-25-heavydragon99/xml/kasteelruine.xml"

class XmlReaderTest : public ::testing::Test {
protected:
    XmlReader *xmlReader;

    void SetUp() override {
        xmlReader = new XmlReader(XMLPATH);
    }

    void TearDown() override {
        delete xmlReader;
    }
};

TEST_F(XmlReaderTest, LoadFile_Success) {
    EXPECT_NO_THROW(XmlReader(XMLPATH));
}

TEST_F(XmlReaderTest, LoadFile_Failure) {
    EXPECT_THROW(XmlReader("invalid_path.xml"), std::runtime_error);
}

TEST_F(XmlReaderTest, RootElementExists) {
    tinyxml2::XMLDocument doc;
    doc.LoadFile(XMLPATH);
    tinyxml2::XMLElement *root = doc.FirstChildElement("locaties");
    ASSERT_NE(root, nullptr);
}

TEST_F(XmlReaderTest, ParseLocations) {
    const auto &locations = xmlReader->getLocations();
    ASSERT_EQ(locations.size(), 14);

    EXPECT_EQ(locations[0].mId, 1);
    EXPECT_EQ(locations[0].mName, "Kasteelpoort");
    EXPECT_EQ(locations[0].mDescription, "Je staat voor de poort van de ruine van een kasteel. De poorten staan open en het valhek is omhoog.");
    EXPECT_EQ(locations[0].mDirections[0].mDirection, Sean::Direction::North);
    EXPECT_EQ(locations[0].mDirections[0].mID, 2);
    EXPECT_EQ(locations[0].mHiddenObjects.size(), 1);
    EXPECT_EQ(locations[0].mHiddenObjects[0], "klein levenselixer");
}

TEST_F(XmlReaderTest, ParseEnemies) {
    const auto &locations = xmlReader->getLocations();
    EXPECT_EQ(locations[1].mEnemies.size(), 2);
    EXPECT_EQ(locations[1].mEnemies[0], "Grote Rat");
    EXPECT_EQ(locations[1].mEnemies[1], "Grote Rat");
}

TEST_F(XmlReaderTest, ParseVisibleObjects) {
    const auto &locations = xmlReader->getLocations();
    EXPECT_EQ(locations[4].mVisibleObjects.size(), 2);
    EXPECT_EQ(locations[4].mVisibleObjects[0], "malienkolder");
    EXPECT_EQ(locations[4].mVisibleObjects[1], "langzwaard");
}

TEST_F(XmlReaderTest, ParseHiddenObjects) {
    const auto &locations = xmlReader->getLocations();
    EXPECT_EQ(locations[4].mHiddenObjects.size(), 1);
    EXPECT_EQ(locations[4].mHiddenObjects[0], "zak met goudstukken");
}

TEST_F(XmlReaderTest, ParseDescription) {
    const auto &locations = xmlReader->getLocations();
    EXPECT_EQ(locations[4].mDescription, "Deze stenen toren staat nog overeind, ook al is de houten trap naar boven weggerot.");
}