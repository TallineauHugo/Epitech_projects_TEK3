#pragma once

#include <map>
#include <vector>
#include "Hitbox.hpp"
#include "Room.hpp"
#include "Exit.hpp"
#include "PokemonFactory.hpp"
#include "Player.hpp"
#include "Items/ItemFactory.hpp"

namespace MappingDir {
        enum dir {UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3};
}

enum ContentType {DOOR, EXIT, PKMN, ITEM};

class Floor;

typedef struct contentList_s {
        ContentType type;
        Vector2d pos;
        int direction;
        Floor *floor;
        std::string pkmName;
} contentList_t;

class DungeonRoom : public Room {
public:
        DungeonRoom(std::string name, int level, OtterEngine::Engine *oe, Floor *floor);
        bool addRoom(DungeonRoom*, int, bool);
        void setIsEmpty(const bool);
        bool getIsEmpty(void) const;
        void setHasExit(const bool);
        bool getHasExit(void) const;
        bool isConnected(int);
        /* Debbug */
        void displayConnection(void);
        DungeonRoom *getRoomByDirection(int);
        void addDoor(int direction);
        void enter();
        void changeRoom();
        void clearRoom();
        void addExit();
        void addPokemon();
        void addItem();


	virtual void updateEvents(OtterEngine::Engine *oe);

	bool DeadPlayerVerification(OtterEngine::Engine *oe);
	int DeadPlayerReaction(OtterEngine::Engine *oe);
private:
	std::vector<OtterEngine::Event<DungeonRoom>> _events;
        std::vector<OtterEngine::Object*> _objList;
        OtterEngine::Engine *_oe;
        Floor *_floor;
        std::map<int, DungeonRoom*> _roomByDirection;
        std::vector<contentList_t *> _content;
        bool _isEmpty;
        bool _hasExit;
        Player *_player;
        ItemFactory itemFactory;
};
