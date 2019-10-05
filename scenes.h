#ifndef SCENES_HEADER
#define SCENES_HEADER

#define t_deadline_logo (0)
#define t_team210_logo (20)
#define t_grafitti_logo (32)
#define t_ocean_logo (42)
#define t_stars_sky_street_logo (53)
#define t_voronoi_cubes_logo (73)
#define t_glitch_city_logo (93)
#define t_greetings_logo (103)
#define t_spacepigs_logo (133)
#define t_fractal_logo (143)
#define t_voronoi_net (173)
// duration is currently defined in config.h

const double start_times[] = {
    t_deadline_logo,
    t_team210_logo,
    t_grafitti_logo,
    t_ocean_logo,
    t_stars_sky_street_logo,
    t_voronoi_cubes_logo,
    t_glitch_city_logo,
    t_greetings_logo,
    t_spacepigs_logo,
    t_fractal_logo,
    t_voronoi_net
};

const char *scene_names[] = {
    "Deadline Logo",
    "Team210 Logo",
    "Hardcyber Graffiti",
    "Ocean Scene",
    "Stars, Sky & Street",
    "Voronoi Cubes",
    "Glitch City",
    "Greetings Scene",
    "Spacepigs Hydrant",
    "Fractal Scene",
    "Voronoi Net"
};

const unsigned int nscenes = ARRAYSIZE(start_times);

// We need these two arrays to always have the same size - the following line will cause a compiler error if this is ever not the case
_STATIC_ASSERT(ARRAYSIZE(start_times) == ARRAYSIZE(scene_names));

#endif
