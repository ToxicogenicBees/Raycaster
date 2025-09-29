#pragma once

#include "../../Rendering/Color.h"
#include "PointObject.h"

class Light : public PointObject {
    private:
        Color _color = Colors::WHITE;
        double _diffusion = 1;
        double _specular = 1;

    public:
        friend class PhongShading;
        
        void setColor(const Color& color);
        void setDiffusion(double diffusion);
        void setSpecular(double specular);
};