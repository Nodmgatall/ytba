#ifndef JOB_SYSTEM_HPP
#define JOB_SYSTEM_HPP

#include "entityx/entityx.h"

// Placeholder!
struct Job {
    unsigned int job_id;
    int percentage_done;
    entityx::Entity *workshop_entity;
    entityx::Entity *worker_doing_job;
    entityx::Entity *std::vector<Job> sub_jobs;
    // no idea how to handle the creation of shit after the job is done
}

enum job_states(RUNNING, WAITING);

class JobManagerSystem : public entityx::System<JobManagerSystem> {
  public:
    void update(entityx::EntityManager &entity_manager, entityx::EventManager &event,
                entityx::TimeDelta dt) override {
        for (auto job : inactive_jobs) {
            std::vector<entityx::Entity> fitting_entities = find_fitting_idle_dwarfs(job);
            if (fitting_entities.size() > 0) {
                assign_job(find_nearest_dwarf(fitting_entities), job);
            }
        }
    }

  private:
    void add_job() {
        number_of_inactive_jobs++;
    }

    void remove_job(unsigned int job_id) {
    }

    std::vector<entityx::Entity> find_fitting_idle_dwarfs() {
    }

    entityx::Entity find_nearest_dwarf(std::vector<entityx::Entity> entity_list) {
        for (auto entity : entity_list) {
        }
    }
    void assign_job(entity_id, job) {
        set_job_active(job);
        // remove idle component
    }
    void finish_job(unsigned int job_id)

        void set_job_active() {
        number_of_inactive_jobs--;
    }
    void set_job_inactive() {
    }

    unsigned int highest_id;
    unsigned int number_of_inactive_jobs;
    std::vector<unsigned int> ids_for_reuse;
    std::vector<Job> jobs;
    std::vector<Job *> inactive_jobs;
}

// What if entity that is assigned to paused job dies?
// 1 another entity could get assigned.
// 2 half done object gets marked as trash
// 3 there is no such bull shit and each job knows its own status and any entity can resume the task
#endif
