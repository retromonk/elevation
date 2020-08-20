#include "elevation_grid.h"

#include <sstream>
#include <algorithm>

namespace sample
{
    class ElevationGridImpl : public IElevationGrid
    {
    public:
        ElevationGridImpl(const std::string &elevationMap)
        {
            std::stringstream in(elevationMap);
            std::string row;
            while (std::getline(in, row, ']'))
            {
                row.erase(std::remove(row.begin(), row.end(), '['), row.end());
                row.erase(std::remove(row.begin(), row.end(), ' '), row.end());
                row.erase(std::remove(row.begin(), row.end(), '\n'), row.end());
                std::stringstream rowIn(row);
                std::string val;
                size_t width = 0UL;
                while (std::getline(rowIn, val, ','))
                {
                    if (!val.empty())
                    {
                        if (val.find("(A)") != std::string::npos)
                        {
                            start_index_ = elevation_map_.size();
                            elevation_map_.emplace_back(0);
                        }
                        else if (val.find("(B)") != std::string::npos)
                        {
                            end_index_ = elevation_map_.size();
                            elevation_map_.emplace_back(0);
                        }
                        else
                        {
                            elevation_map_.emplace_back(stoi(val));
                        }

                        width++;
                    }
                }

                if (width > width_)
                {
                    width_ = width;
                }
            }
        }

        size_t width() const override
        {
            return width_;
        }

        size_t height() const override
        {
            return elevation_map_.size() > 0 ? elevation_map_.size() / width_ : 0;
        }

        std::pair<size_t, size_t> start() const
        {
            if (width_ == 0UL)
            {
                return { std::string::npos, std::string::npos };
            }

            auto row = (size_t)(start_index_ / width_);
            auto col = start_index_ % width_;
            return { row, col };
        }

        std::pair<size_t, size_t> end() const
        {
            if (width_ == 0UL)
            {
                return { std::string::npos, std::string::npos };
            }

            auto row = (size_t)(end_index_ / width_);
            auto col = end_index_ % width_;
            return { row, col };
        }

        int getElevation(size_t row, size_t col) const override
        {
            auto index = row * width_ + col;
            return elevation_map_.at(index);
        }

    private:
        std::vector<int> elevation_map_;
        size_t width_ = 0UL;
        size_t start_index_ = std::string::npos;
        size_t end_index_ = std::string::npos;
    };

    ElevationGrid::ElevationGrid(const std::string &elevationMap) : impl_(std::make_unique<ElevationGridImpl>(elevationMap))
    {
    }

    size_t ElevationGrid::width() const
    {
        return impl_->width();
    }

    size_t ElevationGrid::height() const
    {
        return impl_->height();
    }

    std::pair<size_t, size_t> ElevationGrid::start() const
    {
        return impl_->start();
    }

    std::pair<size_t, size_t> ElevationGrid::end() const
    {
        return impl_->end();
    }

    int ElevationGrid::getElevation(size_t col, size_t row) const
    {
        return impl_->getElevation(col, row);
    }
} // namespace sample