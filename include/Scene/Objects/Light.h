#pragma once

#include "../../Types/Point.hpp"

class Light {
    private:
        // Position
        double3 _position = double3(0, 0, 0);

        // Rendering coefficients
        Color _color = Color(1, 1, 1);
        double _diffusion = 1;
        double _specular = 1;

    public:
        friend class PhongShading;
        /***
         * @brief Creates and places a light into the scene
         */
        Light();

        /***
         * @brief Destroys and removes the light from the scene
         */
        ~Light();

        /***
         * @brief Places the light at a desired (x, y, z) position
         * 
         * @param point The desired position
         */
        virtual void positionAt(const double3& point);

        /***
         * @brief Places the light at a desired (x, y, z) position
         * 
         * @param x    The desired x-position
         * @param y    The desired y-position
         * @param z    The desired z-position
         */
        void positionAt(double x, double y, double z);

        /***
         * @brief Translates the light by a desired (x, y, z) distance
         * 
         * @param dp   The desired position change
         */
        virtual void translate(const double3& dp);

        /***
         * @brief Translates the light by a desired (x, y, z) distance
         * 
         * @param dx   The desired x-position change
         * @param dy   The desired y-position change
         * @param dz   The desired z-position change
         */
        void translate(double dx, double dy, double dz);
        
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