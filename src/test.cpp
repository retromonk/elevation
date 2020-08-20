#include "sample/elevation_grid_traverser.h"

#include <iostream>

#define IS_TRUE(x) { if (!x) std::cout << "\t" << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; }

void ElevationController_No_Smoothing()
{
    std::cout << "Test: " << __FUNCTION__ << std::endl;
    sample::ElevationController elevationController(0, 0);
    IS_TRUE((elevationController.update(2) == 2));
    IS_TRUE((elevationController.update(1) == 1));
}

void ElevationController_Smoothing_Two()
{
    std::cout << "Test: " << __FUNCTION__ << std::endl;
    sample::ElevationController elevationController(2, 0);
    IS_TRUE((elevationController.update(2) == 2));
    IS_TRUE((elevationController.update(1) == 2));
    IS_TRUE((elevationController.update(1) == 2));
}

void ElevationController_Always_Increases()
{
    std::cout << "Test: " << __FUNCTION__ << std::endl;
    sample::ElevationController elevationController(100, 0);
    IS_TRUE((elevationController.update(10) == 10));
    IS_TRUE((elevationController.update(20) == 20));
    IS_TRUE((elevationController.update(30) == 30));
}

void ElevationController_Hop_Bumps()
{
    std::cout << "Test: " << __FUNCTION__ << std::endl;
    sample::ElevationController elevationController(100, 1);
    IS_TRUE((elevationController.update(10) == 10));
    IS_TRUE((elevationController.update(11) == 10));
}

void ElevationGrid_Width_Height()
{
    const char* test = R"(
        [
            [1, 2, 3], 
            [4, 5, 6], 
            [7, 8, 9],
            [10, 11, 12]
        ]
    )";

    std::cout << "Test: " << __FUNCTION__ << std::endl;
    sample::ElevationGrid elevationGrid(test);
    IS_TRUE((elevationGrid.width() == 3));
    IS_TRUE((elevationGrid.height() == 4));
}

void ElevationGrid_Row_Index_Value()
{
    const char* test = R"(
        [
            [1, 2, 3], 
            [4, 5, 6], 
            [7, 8, 9],
            [10, 11, 12]
        ]
    )";

    std::cout << "Test: " << __FUNCTION__ << std::endl;
    sample::ElevationGrid elevationGrid(test);
    IS_TRUE((elevationGrid.getElevation(0, 0) == 1));
    IS_TRUE((elevationGrid.getElevation(3, 2) == 12));
}

void ElevationGrid_Finds_Trajectory()
{
    const char* test = R"(
        [
            [1, 2, 3], 
            [4, (A), 6], 
            [7, 8, 9],
            [10, 11, (B)]
        ]
    )";

    std::cout << "Test: " << __FUNCTION__ << std::endl;
    sample::ElevationGrid elevationGrid(test);
    auto start = elevationGrid.start();
    IS_TRUE((start.first == 1 && start.second == 1));
    auto end = elevationGrid.end();
    IS_TRUE((end.first == 3 && end.second == 2));
}

void ElevationGridLineIterator_Test()
{
    std::cout << "Test: " << __FUNCTION__ << std::endl;
    sample::ElevationGridLineIterator elevationGridLineIterator({ 0, 0 }, { 5, 25 });
    std::vector<std::pair<size_t, size_t>> result;
    while (elevationGridLineIterator.hasNext())
    {
        auto next = elevationGridLineIterator.getNext();
        if (result.size() == 0UL || result.back() != next)
        {
            result.emplace_back(next);
        }
    }

    IS_TRUE((result.size() == 25));
}

void ElevationTraverserTest()
{
    const std::string test = R"(
        [
            [1, 2, 3], 
            [4, (A), 6], 
            [7, 8, 9],
            [10, 11, (B)]
        ]
    )";

    std::cout << "Test: " << __FUNCTION__ << std::endl;
    sample::ElevationGridTraverser traverser;
    auto results = traverser.traverseGridRoute<
        sample::ElevationGrid, 
        sample::ElevationController, 
        sample::ElevationGridLineIterator>(test, 0, 0);

    IS_TRUE((results.size() == 1));
    IS_TRUE((results.size() > 0 && results.at(0) == 8));
}

int main(int, char**)
{
    std::cout << "Starting Tests" << std::endl;
    ElevationController_No_Smoothing();
    ElevationController_Smoothing_Two();
    ElevationController_Always_Increases();
    ElevationController_Hop_Bumps();
    ElevationGrid_Width_Height();
    ElevationGrid_Row_Index_Value();
    ElevationGrid_Finds_Trajectory();
    ElevationGridLineIterator_Test();
    ElevationTraverserTest();
    std::cout << "Tests Finished" << std::endl;
    return 0;
}