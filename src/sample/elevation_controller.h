#ifndef ELEVATION_CONTROLLER_H
#define ELEVATION_CONTROLLER_H

#include <memory>

namespace sample
{
    class IElevationController
    {
        public:
            virtual ~IElevationController() = default;
            virtual int update(int target) = 0;
            virtual int elevation() const = 0;
    };

    class ElevationController : public IElevationController
    {
        public:
            // smooth ticks minimum distance to reduce height -- valley test
            // min ascent - raise to reduce the reaction to bumps
            ElevationController(int smoothTicks, int minAscent);
            int update(int target) override;
            int elevation() const override;
            
        private:
            std::unique_ptr<IElevationController> impl_;
    };
}

#endif