#include <iostream>
#include <vector>

#include "CGL/vector2D.h"

#include "mass.h"
#include "rope.h"
#include "spring.h"

namespace CGL {
	Rope::Rope(Vector2D start, Vector2D end, int num_nodes, float node_mass, float k, vector<int> pinned_nodes) {
		// TODO (Part 1): Create a rope starting at `start`, ending at `end`, and containing `num_nodes` nodes.

		//        Comment-in this part when you implement the constructor
		//        for (auto &i : pinned_nodes) {
		//            masses[i]->pinned = true;
		//        }
		Vector2D interval = (end - start) / num_nodes;
		for (unsigned i(0); i < num_nodes; i++) {
			masses.emplace_back(new Mass(start + i * interval, node_mass, false));
			masses[i]->forces = Vector2D(0, 0);
		}

		for (auto& i : pinned_nodes) {
			masses[i]->pinned = true;
		}

		for (unsigned i(0); i < num_nodes - 1; i++) {
			springs.emplace_back(new Spring(masses[i], masses[i + 1], k));
		}
	}

	void Rope::simulateEuler(float delta_t, Vector2D gravity) {
		for (auto& s : springs) {
			// TODO (Part 2): Use Hooke's law to calculate the force on a node
			Vector2D forceDir = s->m2->position - s->m1->position;
			Vector2D force = s->k * (forceDir) / forceDir.norm() * (forceDir.norm() - s->rest_length);
			s->m1->forces += force;
			s->m2->forces -= force;
		}

		for (auto& m : masses) {
			if (!m->pinned) {
				// TODO (Part 2): Add the force due to gravity, then compute the new velocity and position

				Vector2D a = m->forces / m->mass + gravity;
				// TODO (Part 2): Add global damping
				float kd = 0.005f;
				a = (m->forces - kd * m->velocity) / m->mass + gravity;

				//explicit method
				//m->position = m->start_position + m->velocity * delta_t;
				//m->velocity = m->velocity + a * delta_t;

				//semi-implicit method
				m->velocity = m->velocity + a * delta_t;
				m->position = m->start_position + m->velocity * delta_t;


				m->last_position = m->start_position;
				m->start_position = m->position;
			}

			// Reset all forces on each mass
			m->forces = Vector2D(0, 0);
		}
	}

	void Rope::simulateVerlet(float delta_t, Vector2D gravity) {
		for (auto& s : springs) {
			// TODO (Part 3): Simulate one timestep of the rope using explicit Verlet （solving constraints)
			Vector2D forceDir = s->m2->position - s->m1->position;
			Vector2D force = s->k * (forceDir) / forceDir.norm() * (forceDir.norm() - s->rest_length);
			s->m1->forces += force;
			s->m2->forces -= force;
		}

		for (auto& m : masses) {
			if (!m->pinned) {
				Vector2D temp_position = m->position;
				Vector2D a = m->forces / m->mass + gravity;

				// TODO (Part 3.1): Set the new position of the rope mass
				double damp = 0.00005;
				m->position = m->start_position + (1 - damp) * (m->start_position - m->last_position) + a * delta_t *
					delta_t;
				m->last_position = m->start_position;
				m->start_position = m->position;

				// TODO (Part 4): Add global Verlet damping
			}
			m->forces = Vector2D(0, 0);
		}
	}
}
