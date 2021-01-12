#pragma once

#include <Shared/math/vector2d.h>
#include <Shared/math/vector3d.h>

class CUserCmd
{
public:
    uint8_t pad000[4];

    // For matching server and client commands for debugging
    int commandNumber;

    // the tick the client created this command
    int tickCount;

    // Player instantaneous view angles.
    math::qAngle viewAngles;
    math::qAngle aimDirection;	// For pointing devices. 

    // Intended velocities
    //	forward velocity.
    float forwardMove;
    //  sideways velocity.
    float sideMove;
    //  upward velocity.
    float upMove;
    // Attack button states
    int buttons;
    // Impulse command issued.
    char impulse;
    // Current weapon id
    int weaponSelect;
    int weaponSubtype;

    int randomSeed;	// For shared random functions

    short mouseDx;		// mouse accum in x from create move
    short mouseDy;		// mouse accum in y from create move

    // Client only, tracks whether we've predicted this command at least once
    bool hasBeenPredicted;
};
