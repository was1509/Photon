#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>
using namespace std;

double hit_sphere(const vec3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;

    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;

    auto discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return -1.0;
    }

    return (-b - sqrt(discriminant)) / (2.0 * a);
}

color ray_color(const ray& r) {
    auto t = hit_sphere(vec3(0, 0, -1), 0.5, r);

    if (t > 0.0) {
        vec3 normal = unit_vector(r.at(t) - vec3(0, 0, -1));
        return 0.5 * color(
            normal.x() + 1,
            normal.y() + 1,
            normal.z() + 1
        );
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