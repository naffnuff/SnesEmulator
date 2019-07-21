#pragma once

#include <vector>

enum Layer
{
    BackgroundLayer1 = 0,
    BackgroundLayer2 = 1,
    BackgroundLayer3 = 2,
    BackgroundLayer4 = 3,
    ObjectLayer = 4,
    BackdropLayer = 5
};

struct ModeEntry
{
    Layer layer;
    int priority;
};

static const std::vector<ModeEntry> mode1 =
{
    { ObjectLayer, 3 },
    { BackgroundLayer1, 1 },
    { BackgroundLayer2, 1 },
    { ObjectLayer, 2 },
    { BackgroundLayer1, 0 },
    { BackgroundLayer2, 0 },
    { ObjectLayer, 1 },
    { BackgroundLayer3, 1 },
    { ObjectLayer, 0 },
    { BackgroundLayer3, 0 }
};

static const std::vector<ModeEntry> mode1e =
{
    { BackgroundLayer3, 1 },
    { ObjectLayer, 3 },
    { BackgroundLayer1, 1 },
    { BackgroundLayer2, 1 },
    { ObjectLayer, 2 },
    { BackgroundLayer1, 0 },
    { BackgroundLayer2, 0 },
    { ObjectLayer, 1 },
    { ObjectLayer, 0 },
    { BackgroundLayer3, 0 }
};