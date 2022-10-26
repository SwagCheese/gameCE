#include "game.h"
#include <TINYSTL/vector.h>
#include <sys/lcd.h>
#include <graphx.h>

bool needs_save() {
    return true; // TODO
}

int approach(int val, int target, int amount) {
    return val > target
           ? max(val - amount, target)
           : min(val + amount, target);
}

tinystl::vector<Object*> objects;
Player *player = nullptr;

uint8_t key_left = 0;
uint8_t key_right = 1;
uint8_t key_up = 2;
uint8_t key_down = 3;
uint8_t key_jump = 4;

bool btn(uint8_t index) {
    kb_lkey_t keys[5] = {kb_KeyLeft, kb_KeyRight, kb_KeyUp, kb_KeyDown, kb_Key2nd};
    if(index > 4) return false;
    return kb_IsDown(keys[index]);
}

// TODO: fill out
Object *init_object(type type, vec2i pos) {
    switch(type) {
        case PLAYER_SPAWN:
//            return new PlayerSpawn(x, y);
        case PLAYER:
            return new Player(pos);
        case PLATFORM:
//            return new Platform(x, y);
        default:
            return nullptr;
    }
}

void init() {
    player = new Player(vec2i{0, 0});
}

void save_game() {

}

/*
 * Object Functions
 */

Object::Object(vec2i pos) {
    this->pos = pos;
    objects.push_back(this);
}

Object::~Object() {
    for (auto i = objects.begin(); i < objects.end(); ++i) {
        if (*i == this) {
            objects.erase(i);
            return;
        }
    }
}

void Object::move(vec2s distance) {
    this->pos.x+=PIX(distance.x);
    this->pos.y+=PIX(distance.y);
}

void Object::render() {

}

bool Object::is_solid(vec2i position) {
    return false;
}

Player *Object::collide_player(vec2i position) {
    return nullptr;
}

Object *Object::collide(enum type type, vec2i position) {
    return nullptr;
}

bool Object::check(enum type type, vec2i position) {
    return false;
}

bool Object::check_player(vec2i position) {
    return false;
}

void Object::move_x(int amount, int start) {

}

void Object::move_y(int amount) {

}

/*
 * Player Functions
 */

Player::Player(vec2i pos) : Object(pos) {
    player = this;
}

Player::~Player() {
    player = nullptr;
}

void Player::update() {
    int input = btn(key_right) ? 1 : (btn(key_left) ? -1 : 0);

    // fell off the screen
    if (pos.y > 240) {
        kill();
    }

    if (pos.y >= 232) {
        pos.y = 232;
        vel.y = 0;
    } else if (pos.y < 0) {
        pos.y = 0;
        vel.y = 0;
    }

    subpixel terminal_vel = SP(4);
    subpixel gravity = SP(0.42);

    if(abs(vel.y) <= SP(0.3)) {
        gravity /= 2;
    }

    if(not on_ground) {
        vel.y = approach(vel.y, terminal_vel, gravity);
    }

    if (pos.x > 312) {
        vel.x = 0;
        pos.x = 312;
    } else if (pos.x < 0) {
        vel.x = 0;
        pos.x = 0;
    }

    on_ground = pos.y >= 230; // is_solid(vec2i{0, 1});
    if (btn(key_jump) && on_ground) {
        vel.y = SP(-4);
    }

    if (input == 1 && pos.x < 320 && vel.x < SP(10)) { // ignore this warning
        vel.x+=50;
    } else if (input == -1 && pos.x > 0 && vel.x > -SP(10)) {
        vel.x-=50;
    } else {
        vel.x -= (vel.x > 0) ? 25 : -25;
    }

    move(vel);
}

void Player::render() {
    gfx_FillRectangle(pos.x, pos.y, hitbox.w, hitbox.h);
}

void Player::kill() {
    // play death animation, respawn, etc
    pos = {.x=0,.y=0};
    vel = {.x=0,.y=0};
    on_ground = false;
}

Player *getPlayer() {
    return player;
}