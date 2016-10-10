/*
 * HUANG Manutea, BARGAIN Orianne
 */
#include "Simulator.h"
const float Simulator::GRAVITY_CONSTANT = 9.81f;
const float Simulator::K = 5000;
const float Simulator::D = 0.5f;
const float Simulator::dt = 1.0f/100.0f;
const float Simulator::n = 10;
const float Simulator::dt_on_n = dt / n;
const float Simulator::nb_iterations = 1;

void Simulator::Update()
{
	for (int i = 0; i < n; i++){
		// Define the simulation loop (the methods are not in order)
		ComputeForces();
		//damping comes after force calculation
		ApplyVelocityDamping();
		Integrate(dt_on_n);
		UpdateManipulator();
	}
}

void Simulator::ComputeForces()
{
	for (auto &p : m_Mesh->particles) // access by reference to avoid copying
	{
		//apply gravity
		p.force_accumulator = Maths::Vector3(0, -GRAVITY_CONSTANT, 0);
		//apply spring
		for (auto &pj : p.neighbors){
			Maths::Vector3 v = (p.pos - pj->pos);
			//normalize is inline so we have to apply like this
			v.normalise();
			p.force_accumulator += -v * K * (p.pos.distance(pj->pos) - p.init_pos.distance(pj->init_pos));
		}
	}

}

void Simulator::Integrate(float delta_t) 
{
	int i = 0;
	//update velocity and position
	for (auto &p : m_Mesh->particles) // access by reference to avoid copying
	{
		if (i >= 10){
			//velocity integration
			p.vel += p.force_accumulator * delta_t / p.mass;
			//pos integration
			p.pos += p.vel * delta_t;
		}
		i++;
	}
}

void Simulator::ApplyVelocityDamping()
{
	for (auto &p : m_Mesh->particles) // access by reference to avoid copying
	{
		p.force_accumulator -= D*p.vel;
	}
}

void Simulator::UpdateManipulator()
{
	if(m_Manipulator)
	{
		Maths::Vector3 manipulator_pos = m_Manipulator->getPosition();
		Maths::Real manipulator_radius = m_Manipulator->getRadius();

		for (unsigned int p = 0 ; p < m_Mesh->particles.size() ; p++) 
		{
			//repulsion of the sphere
			Maths::Vector3 m_force = Maths::Vector3(0.0f, 0.0f, 0.0f);
			

			if (m_Mesh->particles[p].pos.distance(manipulator_pos) < manipulator_radius) 
			{
				m_force = m_Mesh->particles[p].pos - manipulator_pos;
				m_force.normalise();	
				m_Mesh->particles[p].pos = manipulator_pos + m_force * manipulator_radius;		

				//impose velocity ZERO perpendicular to the sphere surface
				m_Mesh->particles[p].vel -= m_force*m_Mesh->particles[p].vel.dotProduct(m_force);		
			}
		}
	}
}

void Simulator::CutLinks() 
{
	
}