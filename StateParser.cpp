#include "StateParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObjectFactory.h"

bool StateParser::parseState(const char *stateFile, std::string
stateID, std::vector<GameObject*> *pObjects, std::vector<std::string>
*pTextureIDs)
{
    //create the xml
    TiXmlDocument xmlDoc;
    //load state file
    if(!xmlDoc.LoadFile(stateFile))
    {
        std::cerr<< xmlDoc.ErrorDesc() << "\n";
        return false;
    }
    //get root element
    TiXmlElement* pRoot = xmlDoc.RootElement();  //<STATES>
    //the rest of the nodes will be the root's children 

    //pre declare the states root node
    TiXmlElement* pStateRoot = 0;
    //get this states root node, assign it to pstateroot
    for(TiXmlElement* e = pRoot -> FirstChildElement(); e != NULL;
    e = e -> NextSiblingElement())
    {
        if(e -> Value() == stateID)
        {
            pStateRoot = e;
        }
    }

    //pre declare the texture root node
    TiXmlElement* pTextureRoot = 0;
    //get this states root texture node, assign it to ptextureroot
    for(TiXmlElement* e = pStateRoot -> FirstChildElement(); e != NULL;
    e = e -> NextSiblingElement())
    {
        if(e -> Value() == std::string("TEXTURES"))
        {
            pTextureRoot = e;
        }
    }
    
    //parse textures
    parseTextures(pTextureRoot, pTextureIDs);
    //pre declare the object root node
    TiXmlElement* pObjectRoot = 0;
    //get the root node, assign it to pobjectroot
    for(TiXmlElement* e = pStateRoot -> FirstChildElement(); e != NULL;
    e = e -> NextSiblingElement())
    {
        if(e -> Value() == std::string("OBJECTS"))
        {
            pObjectRoot = e;
        }
    }

    //parse the object!!
    parseObjects(pObjectRoot, pObjects);

    return true;
}

void StateParser::parseTextures(TiXmlElement* pStateRoot,
std::vector<std::string> *pTextureIDs)
{
    for(TiXmlElement* e = pStateRoot -> FirstChildElement();
    e != NULL; e = e -> NextSiblingElement())
    {
        std::string filenameAttribute = e -> Attribute("filename");
        std::string idAttribute       = e -> Attribute("ID");
        pTextureIDs -> push_back(idAttribute);

        TheTextureManager::Instance() -> load(filenameAttribute,
        idAttribute, TheGame::Instance() -> getRenderer());
    }
}

void StateParser::parseObjects(TiXmlElement *pStateRoot,
std::vector<GameObject*> *pObjects)
{
    for(TiXmlElement* e = pStateRoot -> FirstChildElement();
    e != NULL; e = e -> NextSiblingElement())
    {
        int x, y, width, height, numFrames, callbackID, animSpeed;
        std::string textureID;
        
        e -> Attribute("x", &x);
        e -> Attribute("y", &y);
        e -> Attribute("width", &width);
        e -> Attribute("height", &height);
        e -> Attribute("numFrames", &numFrames);
        e -> Attribute("callbackID", &callbackID);
        e -> Attribute("animSpeed", &animSpeed);

        textureID = e -> Attribute("textureID");

        GameObject* pGameObject = TheGameObjectFactory::Instance()
        ->create(e->Attribute("type"));

        pGameObject -> load(std::unique_ptr<LoaderParams>(new LoaderParams
        (x,y,width,height,textureID,numFrames,callbackID,animSpeed)));
        pObjects -> push_back(pGameObject);
    }
}

