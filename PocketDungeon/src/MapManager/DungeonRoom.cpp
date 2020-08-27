#include <iostream>
#include "DungeonRoom.hpp"
#include "Door.hpp"
#include "Player.hpp"
#include "IA.hpp"
#include "Heart.hpp"
#include "MenuManager.hpp"
#include "InvisibleWall.hpp"
#include "WindowManager.hpp"

#define NB_PKMN 22

std::string pkmnPool[NB_PKMN] = {
    "pikachu",
    "charmander",
    "squirtle",
    "bulbasaur",
    "caterpie",
    "butterfree",
    "weedle",
    "kakuna",
    "beedrill",
    "pidgey",
    "rattata",
    "spearow",
    "ekans",
    "sandshrew",
    "nidoranF",
    "nidoranM",
    "clefairy",
    "vulpix",
    "ninetales",
    "jigglypuff",
    "zubat",
    "oddish"
};

std::string translateDir(int dir) {
        if (dir == MappingDir::UP)
                return "UP";
        else if (dir == MappingDir::RIGHT)
                return "RIGHT";
        else if (dir == MappingDir::DOWN)
                return "DOWN";
        else if (dir == MappingDir::LEFT)
                return "LEFT";
        else
                return "UNKNOWN";
}

DungeonRoom::DungeonRoom(std::string name, int level, OtterEngine::Engine *oe, Floor *floor) : Room(name, level), _isEmpty(false), _hasExit(false), _oe(oe), _floor(floor)
{
        /*
        ** DEBBUG
        */
        addEvent<DungeonRoom>(_events, OtterEngine::Event<DungeonRoom>("DeadPLayer", &DungeonRoom::DeadPlayerReaction, &DungeonRoom::DeadPlayerVerification));
        std::cout << "We create a DungeonRoom level " << _level << std::endl;

        _roomByDirection.insert(std::pair<int, DungeonRoom *>(MappingDir::LEFT, nullptr));
        _roomByDirection.insert(std::pair<int, DungeonRoom *>(MappingDir::RIGHT, nullptr));
        _roomByDirection.insert(std::pair<int, DungeonRoom *>(MappingDir::UP, nullptr));
        _roomByDirection.insert(std::pair<int, DungeonRoom *>(MappingDir::DOWN, nullptr));

        int random = rand() % 3 + 1;
       for (int i = 0; i < random; i++)
                addPokemon();

        //item creation
        // int itemRandom = rand() % 10;
        // if (itemRandom == 0)
        //        addItem();

        std::vector<OtterEngine::Object *> objs = _oe->getObjs();

        for (int i = 0; i != objs.size(); i++) {
                if ((objs[i]->getName().find("Player") != std::string::npos)) {
                        _player = dynamic_cast<Player *>(objs[i]);
                        break;
                }
        }
}

bool DungeonRoom::addRoom(DungeonRoom *room, int direction, bool pairing)
{
        if (!isConnected(direction)) {
                if (pairing == true) {
                        _roomByDirection[direction] = room;
                        addDoor((direction));
                }
                if (!room->isConnected((direction + 2) % 4)) {
                        _roomByDirection[(direction + 2) % 4] = this;
                        room->addRoom(this, (direction + 2) % 4, true);
                        return true;
                }
                return false;
        }
        return false;
}

void DungeonRoom::addDoor(int direction)
{
        contentList_t *door;

        door = new contentList_t;
        door->type = ContentType::DOOR;
        door->floor = _floor;

        if (direction == MappingDir::UP) {
                door->pos = {900, 55};
                door->direction = 0;
        }
        else if (direction == MappingDir::RIGHT) {
                door->pos = {1880, 500};
                door->direction = 1;
        }
        else if (direction == MappingDir::DOWN) {
                door->pos = {1000, 1040};
                door->direction = 2;
        }
        else if (direction == MappingDir::LEFT) {
                door->pos = {40, 500};
                door->direction = 3;
        }
        else
                return;
        _content.push_back(door);
}

void DungeonRoom::addExit()
{
        contentList_t *ex;

        ex = new contentList_t;
        ex->type = ContentType::EXIT;
        ex->floor = _floor;
        double x = rand() % 1700 + 100;
        double y = rand() % 700 + 100;
        ex->pos = {x, y};
        _content.push_back(ex);
        this->setHasExit(true);
}

void DungeonRoom::addPokemon()
{
        contentList_t *ex;

        ex = new contentList_t;
        ex->type = ContentType::PKMN;
        ex->floor = _floor;
        double x = rand() % 1700 + 100;
        double y = rand() % 700 + 100;
        ex->pos = {x, y};
        int random = rand() % NB_PKMN;
        ex->pkmName = pkmnPool[random];
        _content.push_back(ex);
}

void DungeonRoom::addItem() {
        contentList_t *ex;

        ex = new contentList_t;
        ex->type = ContentType::ITEM;
        ex->floor = _floor;
        double x = rand() % 1700 + 100;
        double y = rand() % 700 + 100;
        ex->pos = {x, y};
        _content.push_back(ex);
}

void DungeonRoom::enter(void)
{
        OtterEngine::Object *obj;

        _oe->addObject(this);
        std::cout << "We enter the room: " << _name << std::endl;
        int x, y;
        sf::Vector2u w_size = WindowManager::getInstance()->getSize();
        for (x = 10; x < w_size.x - 10; x += 102)
                _oe->addObject(new InvisibleWall({(double)x, 40}, {100, 100}));
        for (y = 40; y < w_size.y - 40; y += 102)
                _oe->addObject(new InvisibleWall({(double)10, (double)y}, {100, 100}));
        for (int i = 10; i < w_size.x - 10; i += 102)
                _oe->addObject(new InvisibleWall({(double)i, (double)y}, {100, 100}));
        for (int i = 10; i < w_size.y - 80; i += 102)
                _oe->addObject(new InvisibleWall({(double)x - 60, (double)i}, {100, 100}));

        for (int i = 0; i < _content.size(); i++) {
                if (_content[i]->type == ContentType::DOOR) {
                        obj = new Door(_content[i]->pos, _content[i]->direction, _content[i]->floor);
                        obj->setName("Door");
                        _oe->addObject(obj);
                        _objList.push_back(obj);
                }
                else if (_content[i]->type == ContentType::EXIT) {
                        obj = new Exit(_content[i]->pos, _content[i]->floor->getDungeon());
                        obj->setName("Exit");
                        _oe->addObject(obj);
                        _objList.push_back(obj);
                }
                else if (_content[i]->type == ContentType::PKMN) {
                        int random = rand() % 10;
			Pokemon *pkmn;
			if (getHasExit()) {
				pkmn = PokemonFactory::getInstance()->createPokemon(_content[i]->pkmName, 10);
			}
			else
				pkmn = PokemonFactory::getInstance()->createPokemon(_content[i]->pkmName, 5);
                        _oe->addObject(pkmn);
                	pkmn->setPos(Vector2d(_content[i]->pos.x, _content[i]->pos.y));
                	pkmn->show();
                        IA *ia = new IA(_oe, _player);
                        ia->setCurrentPokemon(pkmn);
                        _objList.push_back(pkmn);
                }
                else if (_content[i]->type == ContentType::ITEM) {
                        IItems *item = itemFactory.createItem();
                        item->setPos(_content[i]->pos);
                        _oe->addObject(item);

                }
        }
}

void DungeonRoom::setIsEmpty(const bool isEmpty) {
        _isEmpty = isEmpty;
}

bool DungeonRoom::getIsEmpty(void) const {
        return _isEmpty;
}

void DungeonRoom::setHasExit(const bool hasExit) {
        _hasExit = hasExit;
}

bool DungeonRoom::getHasExit(void) const {
        return _hasExit;
}

bool DungeonRoom::isConnected(int direction)
{
        if (!_roomByDirection[direction])
                return false;
        return true;
}

DungeonRoom *DungeonRoom::getRoomByDirection(int nb) {
        return _roomByDirection[nb];
}

void DungeonRoom::clearRoom() {
        std::vector<OtterEngine::Object *> objs = _oe->getObjs();

        OtterEngine::SpritesManager *_SpriteM = OtterEngine::SpritesManager::getInstance();

        for (int i = 0; i != objs.size(); i++) {
                if (_player != objs[i] && !objs[i]->getIsPlayer()) {
                        for (int j = 0; j != _objList.size(); j++) {
                                if (objs[i] == _objList[j]) {
                                        _objList[j] = nullptr;
                                        break;
                                }
                        }
                        if (objs[i]->getName().find("PKMN") != std::string::npos)
                            dynamic_cast<Pokemon *>(objs[i])->hideHpBar();
                        //objs[i];
                        _oe->removeObjectById(_oe->getIndex(objs[i]));
                        _SpriteM->removeSprite(objs[i]->getSprite());
                }
                else {
                        std::cout << "on tej pas << " << objs[i]->getName() << std::endl;
                }
        }
        int cpt = 0;
        for (int i = 0; i != _objList.size(); i++) {
                if (_objList[i] != nullptr) {
                        _content.erase(_content.begin() + cpt);
                }
                _objList.erase(_objList.begin() + i);
                i--;
                cpt++;
        }
        _oe->removeIAs();
        //std::cout << "we still have " << std::endl;
        //for (int i = 0; i != objs.size(); i++) {
                //std::cout << objs[i]->getName() << std::endl;
        //}
        // _oe->removeObjectById(_oe->getIndex(this));
}

bool DungeonRoom::DeadPlayerVerification(OtterEngine::Engine *oe)
{
	if (_player->GetCurrentPokemon()->getCurrentHp() == 0) {
                        std::cout << "PLAYER IS DEAD" << std::endl;
	               return true;
        }
        else {
                // std::cout << "PLayer is not deead" << std::endl;
        }
        return false;
}


int DungeonRoom::DeadPlayerReaction(OtterEngine::Engine *oe)
{
        removeEvent(_events, "DeadPLayer");
        clearRoom();
        MenuManager::getInstance()->getGameOverScreenInstance(oe);
        _floor->getDungeon()->ExitDungeon();
        _player->respawn(oe);
        //_player->GetCurrentPokemon()->setPos({500, 500});
	return 0;
}

void DungeonRoom::updateEvents(OtterEngine::Engine *oe)
{
	for (std::size_t i = 0; i < _events.size(); i++) {
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}

/*
** DEBBUG FUNCTION
*/
void DungeonRoom::displayConnection(void) {
        std::cout << "For Room n°" << getName() << std::endl;
        if (getIsEmpty() || getHasExit()) {
                std::cout << "-- Information -- " << std::endl;
                std::cout << "This room ";
                if (getIsEmpty())
                        std::cout << " is empty" << std::endl;
                if (getHasExit())
                        std::cout << " has the exit" << std::endl;
                std::cout << "-------------" << std::endl;
        }
        for (int i = 0; i <= MappingDir::LEFT; i++) {
                if (isConnected(i) && _roomByDirection[i]->getName().find(this->getName()))
                        std::cout << "Connected on " << translateDir(i) << " to " << _roomByDirection[i]->getName() << std::endl;
        }
}
