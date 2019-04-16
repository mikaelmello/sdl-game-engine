#ifndef GAMEDATA_H
#define GAMEDATA_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class GameData {
    public:
        enum Types {
            CameraFollower,
            Collider,
            Sound,
            Sprite,
            Text,
            TileMap,
        };
};

#endif
