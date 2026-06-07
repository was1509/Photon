#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>
using namespace std;

bool hit_sphere(const vec3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;

    auto a = r.direction().x() * r.direction().x()
           + r.direction().y() * r.direction().y()
           + r.direction().z() * r.direction().z();

    auto b = 2.0 * (
        oc.x() * r.direction().x() +
        oc.y() * r.direction().y() +
        oc.z() * r.direction().z()
    );

    auto c = oc.x() * oc.x() + oc.y() * oc.y() + oc.z() * oc.z()
           - radius * radius;

    auto discriminant = b * b - 4 * a * c;

    return discriminant >= 0;
}

color ray_color(const ray& r) {
    if (hit_sphere(vec3(0, 0, -1), 0.5, r)) {
        return color(1, 0, 0);
    }

    return color(0.5, 0.7, 1.0);
}

int main() {
    int image_width = 256;
    int image_height = 256;

    double viewport_height = 2.0;
    double viewport_width = 2.0;
    double focal_length = 1.0;

    vec3 origin(0, 0, 0);
    vec3 horizontal(viewport_width, 0, 0);
    vec3 vertical(0, viewport_height, 0);
    vec3 lower_left_corner =
        origin - 0.5 * horizontal - 0.5 * vertical - vec3(0, 0, focal_length);

    cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; j--) {
        cerr << "\rScanlines remaining: " << j << ' ' << flush;

        for (int i = 0; i < image_width; i++) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);

            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            color pixel_color = ray_color(r);

            write_color(cout, pixel_color);
        }
    }

    cerr << "\rDone.                 \n";
}