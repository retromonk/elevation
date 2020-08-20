#include "elevation_grid_line_iterator.h"

#include <math.h>

namespace sample
{
    class ElevationGridLineIteratorImpl : public IElevationGridLineIterator
    {
    public:
        ElevationGridLineIteratorImpl(const std::pair<size_t, size_t> &start, const std::pair<size_t, size_t> &end) : start_(start), end_(end)
        {
            cur_x_ = static_cast<float>(start.first);
            cur_y_ = static_cast<float>(start.second);
            dir_x_ = static_cast<float>(end.first) - static_cast<float>(start.first);
            dir_y_ = static_cast<float>(end.second) - static_cast<float>(start.second);
            auto mag = std::sqrt(std::pow(dir_x_, 2.0) + std::pow(dir_y_, 2.0));
            dir_x_ /= mag;
            dir_y_ /= mag;
        }

        bool hasNext() const override
        {
            auto dx = static_cast<float>(end_.first) - cur_x_;
            auto dy = static_cast<float>(end_.second) - cur_y_;
            auto mag = std::sqrt(std::pow(dx, 2.0) + std::pow(dy, 2.0));
            return mag > 1.0f;
        }

        std::pair<size_t, size_t> getNext() override
        {
            if (hasNext())
            {
                cur_x_ = cur_x_ + dir_x_;
                cur_y_ = cur_y_ + dir_y_;
            }

            return {static_cast<size_t>(cur_x_), static_cast<size_t>(cur_y_)};
        }

    private:
        std::pair<size_t, size_t> start_;
        std::pair<size_t, size_t> end_;

        float cur_x_;
        float cur_y_;
        float dir_x_;
        float dir_y_;

        std::pair<float, float> computeNext() const
        {
            auto next_x_ = cur_x_ + dir_x_;
            auto next_y_ = cur_y_ + dir_y_;
            return {next_x_, next_y_};
        }
    };

    ElevationGridLineIterator::ElevationGridLineIterator(const std::pair<size_t, size_t> &start, const std::pair<size_t, size_t> &end) : impl_(std::make_unique<ElevationGridLineIteratorImpl>(start, end))
    {
    }

    bool ElevationGridLineIterator::hasNext() const
    {
        return impl_->hasNext();
    }

    std::pair<size_t, size_t> ElevationGridLineIterator::getNext()
    {
        return impl_->getNext();
    }
} // namespace sample