#pragma once

#include "../../Rendering/Reflectance.h"
#include "../../Point.hpp"
#include <string>
#include <vector>

using double3 = Point<double>;

class BaseObject {
    private:
        static uint16_t _cur_id;    // The current max ID
        
        const std::string _TYPE;    // Object type
        const uint16_t _ID;         // Object UUID

        Reflectance _ref;           // Object reflectance coefficients
        double3 _rot;               // Rotation in radians
        double3 _pos;               // Position in units

    public:
        static std::vector<BaseObject*> objects;    // List of all created objects

        BaseObject(const std::string& type, const double3& pos, const double3& rot, const Reflectance& ref);
        BaseObject(const std::string& type, const double3& pos, const Reflectance& ref);
        BaseObject(const std::string& type, const Reflectance& ref);
        BaseObject(const std::string& type, const double3& pos);
        BaseObject(const std::string& type);

        void setReflectance(const Reflectance& ref);
        void setPosition(const double3& pos);
        void setRotation(const double3& rot);

        const Reflectance& reflectance() const { return _ref; }
        const std::string& type() const { return _TYPE; }
        const double3& position() const { return _pos; }
        const double3& rotation() const { return _rot; }
        uint16_t id() const { return _ID; }
};