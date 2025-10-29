#include "pch.h"
#include "Scene.h"


Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::AddTile(Tiles* _tile)
{
    mTiles.push_back(_tile);
}

void Scene::EraseTile(Tiles* _tile)
{
    if (!_tile)
        return;

    mTiles.erase(std::remove(mTiles.begin(), mTiles.end(), _tile));
    delete _tile;
}

void Scene::AddBonus(Bonus* _bonus)
{
    mBonus.push_back(_bonus);
}

void Scene::EraseBonus(Bonus* _bonus)
{
    mBonus.erase(std::remove(mBonus.begin(), mBonus.end(), _bonus));
    delete _bonus;
}

std::vector<Geometry*> Scene::GetGeometries()
{
    std::vector<Geometry*> allGeometries;

   
    for (Tiles* tile : mTiles)
    {
        std::vector<Geometry*> tileGeometries = tile->GetGeometries();
        for (Geometry* geo : tileGeometries)
        {
            allGeometries.push_back(geo);
        }
    }
    
    std::vector<Geometry*> characterGeometries = mCharacter->GetGeometries();
    for (Geometry* geo : characterGeometries)
    {
        allGeometries.push_back(geo);
    }
    
    for (Bonus* bonus : mBonus)
    {
        std::vector<Geometry*> bonusGeometries = bonus->GetGeometries();
        for (Geometry* geo : bonusGeometries)
        {
            allGeometries.push_back(geo);
        }
    }


    return allGeometries;
}

void Scene::EraseText(Text* _text)
{
    mTexts.erase(std::remove(mTexts.begin(), mTexts.end(), _text));
    delete _text;
}

void Scene::EraseBonusBar(Text* _text)
{
    mBonusBar.erase(std::remove(mBonusBar.begin(), mBonusBar.end(), _text));
    delete _text;
}

void Scene::AddText(Text* _text)
{
    mTexts.push_back(_text);
}

void Scene::AddTextBar(Text* _text)
{
    mBonusBar.push_back(_text);
}

std::vector<Text*> Scene::GetTexts()
{
    std::vector<Text*> allTexts;


    for (Text* text : mTexts)
    {
        allTexts.push_back(text);
    }

    for (Text* text : mBonusBar)
    {
        allTexts.push_back(text);
    }

    return allTexts;
}


