

//keystate.h


#ifndef _KEYSTATE_H
#define _KEYSTATE_H

#define KEYSTATE(vknum) ((GetAsyncKeyState(vknum) & 0x8000) ? TRUE : FALSE)

#endif