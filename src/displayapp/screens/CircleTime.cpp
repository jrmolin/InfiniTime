#include "displayapp/screens/CircleTime.h"
#include "displayapp/DisplayApp.h"
#include "displayapp/LittleVgl.h"

#include <algorithm> // std::fill

using namespace Pinetime::Applications::Screens;

CircleTime::CircleTime(Pinetime::Applications::DisplayApp* app,
                       Pinetime::Controllers::MotorController& motor)
  : Screen(app), motor {motor} {
      point_label = lv_label_create(lv_scr_act(), nullptr);
      lv_label_set_text_static(point_label, "move the dot");
      lv_label_set_align(point_label, LV_LABEL_ALIGN_CENTER);
      lv_obj_align(point_label, lv_scr_act(), LV_ALIGN_CENTER, 0, 0);
}

CircleTime::~CircleTime() {
  lv_obj_clean(lv_scr_act());
}

bool CircleTime::OnTouchEvent(Pinetime::Applications::TouchEvents event) {
  switch (event) {
    case Pinetime::Applications::TouchEvents::LongTap:
      motor.RunForDuration(35);
      return true;
    default:
      return true;
  }
  return true;
}

bool CircleTime::OnTouchEvent(uint16_t x, uint16_t y) {
    //  0  |  1
    //  2  |  3
    // if x is greater than halfway over, this will be nonzero
    uint16_t quad = x / (width >> 1) + 2 * (y / (height >> 1));

    constexpr static char quads[][4] = {"NW", "NE", "SW", "SE"};
    lv_label_set_text_fmt(point_label, "%s\n(%02i, %02i)",
                          quads[quad % 4], x, y);

  return true;
}
