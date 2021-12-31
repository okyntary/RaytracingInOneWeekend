#pragma once

#include <memory>
#include <vector>

#include "hittable.h"

using std::shared_ptr;
using std::make_shared;

class Hittable_List : public Hittable {
public:
    std::vector<shared_ptr<Hittable>> hittable_list {};

public:
    Hittable_List() {};
    Hittable_List(shared_ptr<Hittable> hittable) {add(hittable);}

    void clear() {hittable_list.clear();}
    void add(shared_ptr<Hittable> hittable) {hittable_list.push_back(hittable);}

    virtual bool hit(const Ray& r, double t_min, double t_max, Hit_Record& rec) const override;
};

bool Hittable_List::hit(const Ray& r, double t_min, double t_max, Hit_Record& rec) const {
    Hit_Record temp_rec;
    bool hit_anything{false};
    auto closest_so_far{t_max};

    for (const auto& hittable : hittable_list) {
        if (hittable->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}