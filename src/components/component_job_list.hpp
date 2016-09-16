#ifndef COMPONENT_JOB_LIST_HPP
#define COMPONENT_JOB_LIST_HPP

#include "../sub_types/terrain_types.hpp"
#include "entityx/entityx.h"

struct job_list : entityx::Component<job_list> {
    job_list() {

    std::vector<Job*> job_list;
    }
#endif
