#include "elevation_controller.h"

namespace sample
{
    class ElevationControllerImpl : public IElevationController
    {
    public:
        int update(int target) override
        {
            target_ = target;
            return target_;
        }

        int elevation() const override
        {
            return target_;
        }

    private:
        int target_ = -1;
    };

    class ElevationSmoothDescentController : public IElevationController
    {
    public:
        ElevationSmoothDescentController(int smoothTicks, std::unique_ptr<IElevationController> controller) : smooth_ticks_(smoothTicks), controller_(std::move(controller))
        {
        }

        int update(int target) override
        {
            target = controller_->update(target);
            if (target < last_target_)
            {
                ++tick_count_;
            }
            else
            {
                tick_count_ = 0;
            }
            
            target = tick_count_ > smooth_ticks_ || target > last_target_ ? target : last_target_;
            last_target_ = target;
            return last_target_;            
        }

        int elevation() const override
        {
            return last_target_;
        }

    private:
        int smooth_ticks_;
        std::unique_ptr<IElevationController> controller_;
        int last_target_ = -1;
        int tick_count_ = 0;
    };

    class ElevationSmoothAscentController : public IElevationController
    {
    public:
        ElevationSmoothAscentController(int minAscentThreshold, std::unique_ptr<IElevationController> controller) : min_ascent_threshold_(minAscentThreshold), controller_(std::move(controller))
        {
        }

        int update(int target) override
        {
            target = controller_->update(target);
            auto delta = target - last_target_;
            if (delta < 0 || delta > min_ascent_threshold_)
            {
                last_target_ = target;
            }
            
            return last_target_;            
        }

        int elevation() const override
        {
            return last_target_;
        }

    private:
        int min_ascent_threshold_;
        std::unique_ptr<IElevationController> controller_;
        int last_target_ = -1;
    };

    ElevationController::ElevationController(int smoothTicks, int minAscent) 
    {
        impl_ = std::make_unique<ElevationControllerImpl>();
        impl_ = std::make_unique<ElevationSmoothDescentController>(smoothTicks, std::move(impl_));
        impl_ = std::make_unique<ElevationSmoothAscentController>(minAscent, std::move(impl_));
    }

    int ElevationController::update(int target)
    {
        return impl_->update(target);
    }

    int ElevationController::elevation() const
    {
        return impl_->elevation();
    }
} // namespace sample