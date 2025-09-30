#pragma once

#include "PointObject.h"

class Light : public PointObject {
    private:
        Color _color = Color(1, 1, 1);
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
         * @brief Sets the color of the light
         * 
         * @param r         The desired red color
         * @param g         The desired red color
         * @param b         The desired red color
         */
        void setColor(double r, double g, double b);

        /**
         * @brief Sets the diffusion of the light
         * 
         * @param diffusion The desired diffusion
         */
        void setDiffusion(double diffusion);

        /**
         * @brief Sets the specular of the light
         * 
         * @param specular  The desired specular
         */
        void setSpecular(double specular);
};