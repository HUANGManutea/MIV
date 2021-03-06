/*
 * HUANG Manutea, BARGAIN Orianne
 */
#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Mesh.h"
#include "RigidSphere.h"

class Simulator {

	//Mesh updated during the simulation
	Mesh* m_Mesh;
	RigidSphere* m_Manipulator;

	//Gravity constant
	static const float GRAVITY_CONSTANT;

	//Stifness constant
	static const float K;
	
	//damping constant of the springs
	static const float D;

	//number of iterations for each simulation step
	static const float nb_iterations;

	//simulation step
	static const float dt;

	//n
	static const float n;

	//dt/n
	static const float dt_on_n;

public:

	//Constructor
	Simulator() {};

	//Initialize the mesh
	inline void setMesh(Mesh* m) {m_Mesh = m;}

	//Initialize the manipulator
	inline void setManipulator(RigidSphere* m) {m_Manipulator = m;}

	//Simulation step
	void Update();

private:

	//Updates the state of the mesh before display
	void ComputeForces();

	//Integrates the state of each particle of the mesh by computing new velocities and position at time t + dt
	void Integrate(float delta_t);
	
	void ApplyVelocityDamping();
	
	void UpdateManipulator();
	
	void CutLinks();
};

#endif