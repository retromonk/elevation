#ifndef ELEVATION_GRID_H
#define ELEVATION_GRID_H

#include <memory>
#include <vector>

namespace sample
{
class IElevationGrid
{
    public:
        virtual ~IElevationGrid() = default;
        virtual size_t width() const = 0;
        virtual size_t height() const = 0;
        virtual std::pair<size_t, size_t> start() const = 0;
        virtual std::pair<size_t, size_t> end() const = 0;
        virtual int getElevation(size_t col, size_t row) const = 0;
};

class ElevationGrid : public IElevationGrid
{
    public:
        ElevationGrid(const std::string& elevationMap);
        size_t width() const override;
        size_t height() const override;
        std::pair<size_t, size_t> start() const override;
        std::pair<size_t, size_t> end() const override;
        int getElevation(size_t col, size_t row) const override;

    private:
        std::unique_ptr<IElevationGrid> impl_;    
};
}

#endif