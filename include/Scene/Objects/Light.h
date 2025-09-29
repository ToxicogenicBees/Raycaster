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
        
        /**
         * @brief Sets the color of the light
         * 
         * @param color     The desired color
         */
        void setColor(const Color& color);

        /**
         * @brief Sets the diffusion of the object
         * 
         * @param diffusion The desired diffusion
         */
        void setDiffusion(double diffusion);

        /**
         * @brief Sets the specular of the object
         * 
         * @param specular  The desired specular
         */
        void setSpecular(double specular);
};