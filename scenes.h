#ifndef SCENES_HEADER
#define SCENES_HEADER

#define t_deadline (0)
#define t_logo210 (20)
#define t_graffiti (32)
#define t_ocean (43.38999938964844)
#define t_starsky (48.08100128173828)
#define t_glitchcity (61.233001708984375)
#define t_watercubes (72.38500213623047)
#define t_greetings (96.68900299072266)
#define t_hydrant (120.99299621582031)
#define t_fractal (135)
#define t_voronoinet (169.60000610351562)
#define t_volclouds (194.375)
#define duration (210.16444396972656)

const double start_times[] = {
    t_deadline,
    t_logo210,
    t_graffiti,
    t_ocean,
    t_starsky,
    t_glitchcity,
    t_watercubes,
    t_greetings,
    t_hydrant,
    t_fractal,
    t_voronoinet,
    t_volclouds,
};

const char *scene_names[] = {
    "Deadline Logo",
    "Team210 Logo",
    "Hardcyber Graffiti",
    "Ocean Scene",
    "Stars, Sky & Street",
    "Glitch City",
    "Voronoi Cubes",
    "Greetings Scene",
    "Spacepigs Hydrant",
    "Fractal Scene",
    "Voronoi Net",
    "Cool Clouds",
};

const unsigned int nscenes = ARRAYSIZE(start_times);

// We need these two arrays to always have the same size - the following line will cause a compiler error if this is ever not the case
_STATIC_ASSERT(ARRAYSIZE(start_times) == ARRAYSIZE(scene_names));

#endif
