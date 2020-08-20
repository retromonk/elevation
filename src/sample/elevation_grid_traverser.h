#ifndef ELEVATION_GRID_TRAVERSER_H
#define ELEVATION_GRID_TRAVERSER_H

#include "elevation_grid.h"
#include "elevation_grid_line_iterator.h"
#include "elevation_controller.h"

#include <string>
#include <vector>

namespace sample
{
    class ElevationGridTraverser
    {
        public:
            template<class GridType, class ControllerType , class IteratorType>
            std::vector<int> traverseGridRoute(const std::string& in, int smoothTicks, int minAscent) 
            {
                GridType grid(in);
                ControllerType controller(smoothTicks, minAscent);
                IteratorType lineIterator(grid.start(), grid.end());

                std::vector<int> results;
                auto lastEntry = grid.start();
                while(lineIterator.hasNext())
                {
                    auto next = lineIterator.getNext();
                    if (next != lastEntry && next != grid.end())
                    {
                        auto targetElevation = grid.getElevation(next.first, next.second);
                        auto smoothElevation = controller.update(targetElevation);  
                        results.emplace_back(smoothElevation);
                    }  

                    lastEntry = next;
                }

                return results;
            };
    };
}

#endif