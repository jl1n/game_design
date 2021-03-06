#ifndef FISH_H
#define FISH_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <memory>
#include <string>
#include "Knot.h"
#include "Bubble.h"

class Fish:public sf::Drawable,public sf::Transformable 
{
    public:
        Fish();
        Fish(const Fish&)=delete;

        Fish& operator=(const Fish&)=delete;

        void addKnot(const Knot& knot);
        Knot getKnot(int i) const;
        void setTexture(const std::shared_ptr<sf::Texture>& texture);
        const std::shared_ptr<sf::Texture>& getTexture() const;
        void setTextureAreas(const std::shared_ptr<std::map<std::string,sf::IntRect>>& areas);
        const std::shared_ptr<std::vector<Knot>> getKnots() const;

        const std::shared_ptr<std::map<std::string,sf::IntRect>>& getTextureAreas() const;
        void setHeadDistance(float headDist);
        float getHeadDistance() const;

        void swimTo(const sf::Vector2f& dest);

        virtual void update(float deltaTime);
        virtual void attacked()=0;

    protected:
        virtual void updateShape()=0;
        std::vector<Knot> _knots;
        std::shared_ptr<sf::Texture> _texture;
        std::shared_ptr<std::map<std::string,sf::IntRect>> _textureAreas;
        bool _hasTexture;
        float _headDist;
        std::vector<Bubble> _bubbles;
        virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;
};
#endif
