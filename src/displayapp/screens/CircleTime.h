#pragma once

#include <lvgl/lvgl.h>
#include <cstdint>
#include "displayapp/screens/Screen.h"
#include "components/motor/MotorController.h"

namespace Pinetime {
  namespace Components {
    class LittleVgl;
  }
  namespace Applications {
    namespace Screens {

      class CircleTime : public Screen {
      public:
        CircleTime(DisplayApp* app, Controllers::MotorController& motor);

        ~CircleTime() override;

        bool OnTouchEvent(TouchEvents event) override;

        bool OnTouchEvent(uint16_t x, uint16_t y) override;

      private:
        enum class Quadrant
        {
            INVALID = -1,
            NE = 0,
            NORTHEAST = NE,
            SE = 1,
            SOUTHEAST = SE,
            SW = 2,
            SOUTHWEST = SW,
            NW = 3,
            NORTHWEST = NW,
            Maximum,
        };
        struct Point
        {
            uint16_t radius = 0;
            uint16_t angle = 0;
        };

        lv_obj_t *point_label;
        Quadrant start = Quadrant::INVALID;
        Controllers::MotorController& motor;
        const uint16_t width = LV_HOR_RES;
        const uint16_t height = LV_VER_RES;
      };
    }
  }
}
