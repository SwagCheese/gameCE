#pragma once

#include <c++/cstdint>
#include <c++/cstdio>
#include <keypadc.h>

#define SUBPIXEL_SCALE 256

typedef int subpixel;
#define SP(x) ((int)((x) * SUBPIXEL_SCALE))
#define PIX(x) ((int)((x) / SUBPIXEL_SCALE))

#define max(x, y) (x > y) ? x : y
#define min(x, y) (x > y) ? y : x

struct vec2i {
    int x, y;
};

struct vec2s {
    subpixel x, y;
};

enum type {
    PLAYER_SPAWN = 1,
    PLATFORM = 2,
    PLAYER
};

bool btn(uint8_t index);

class Player;

class Object {
protected:
    bool has_collision = true;
    bool solids = true;
    uint8_t sprite = 0;
    uint8_t type;
    struct vec2s vel{.x=0,.y=0};
    struct vec2i pos;
    struct {bool x; bool y;} flip{.x=false, .y=false};
    struct {int x; int y; int w; int h;} hitbox{.x=0, .y=0, .w=8, .h=8};
public:
    explicit Object(vec2i pos);
    virtual ~Object();



    virtual void update() {}
    virtual void move(vec2s distance);
    virtual void render();

    bool is_solid(vec2i position);
    Object *collide(enum type type, vec2i position);
    Player *collide_player(vec2i position);
    bool check(enum type type, vec2i position);
    bool check_player(vec2i position);
    void move_x(int amount, int start);
    void move_y(int amount);
};

class Player : public Object {
private:
    bool on_ground=false;
    uint8_t type = PLAYER;

public:
    explicit Player(vec2i pos);
    ~Player() override;

    void update() override;
    void render() override;

    void kill();
};

bool needs_save();
void save_game();

Object *init_object(enum type type, int x, int y);

void init();

Player *getPlayer();