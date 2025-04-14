//
// Created by Wiktor on 13.04.2025.
//

#ifndef FOX_H
#define FOX_H
#include "Animal.h"


class Fox final : public Animal {
private:
    [[nodiscard]] bool isFieldSafe(int x, int y) const;
public:
    Fox(Position position, World *world);
    ~Fox() override;

    void makeMove() override;

    [[nodiscard]] std::unique_ptr<Animal> makeChild() const override;

    void draw() override;
};



#endif //FOX_H
