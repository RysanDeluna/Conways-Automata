//
// Created by rysan on 28/12/23.
//
#include <engine.h>

#include "../classes/Matrix.h"
#include <maths.h>


// Information regarding the cells to print them on the screen
struct graphic_cell_t
{
    std::shared_ptr<Cell> cell_ptr;
    sf::Vector2f s_pos;
    sf::Vector2ul m_pos;
    std::shared_ptr<sf::Shape> shape;
    template<typename T, typename... Targs> void setShape(Targs... params) { shape.reset(new T(params...)); }
};


// Presents the generations of cells
// --------------+------------------
// -          CONTROLS             -
// --------------+------------------
// -   SPACE     : NEXT GENERATION -
// -   N         : NEW BOARD       -
// -   R         : RESTART BOARD   -
// --------------+------------------
class SceneSimulation : public Scene {
public:
    void Load() override;
    void UnLoad() override;
    void Update(const double &dt) override;
    void Render() override;

private:
    std::vector<graphic_cell_t> list_cells;
};


