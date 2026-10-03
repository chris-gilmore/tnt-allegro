#include "common.h"
#include <allegro5/allegro5.h>

u8 FUN_001050_getControllerErrNo(SuperThread *superThd, u8 cont_no) {
  return (cont_no != 0) && (al_get_joystick(cont_no) == NULL);
}
