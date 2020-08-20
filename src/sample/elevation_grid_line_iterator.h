#ifndef ELEVATION_GRID_LINE_ITERATOR_H
#define ELEVATION_GRID_LINE_ITERATOR_H

#include <memory>

namespace sample
{
    class IElevationGridLineIterator
    {
    public:
        virtual ~IElevationGridLineIterator() = default;
        virtual bool hasNext() const = 0;
        virtual std::pair<size_t, size_t> getNext() = 0;
    };

    class ElevationGridLineIterator : public IElevationGridLineIterator
    {
    public:
        ElevationGridLineIterator(const std::pair<size_t, size_t> &start,
                                  const std::pair<size_t, size_t> &end);
        bool hasNext() const override;
        std::pair<size_t, size_t> getNext() override;

    private:
        std::unique_ptr<IElevationGridLineIterator> impl_;
    };
} // namespace sample

#endif