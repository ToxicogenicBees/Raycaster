#include "../../include/Objects/BaseObject.h"

uint16_t BaseObject::_cur_id = 0;

void BaseObject::_assignId() {
    _id = _cur_id++;
}

BaseObject::BaseObject(double2 pos, double2 rot) {
    _position = pos;
    _position = rot;
}

BaseObject::BaseObject() {}