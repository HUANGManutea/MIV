#include <iostream>

#include "AllMath.h"

#include "GUI.h"
#include "Mesh.h"
#include "Simulator.h"
//#include "haptic_client.h"

//HapticClient haptic_client;
RigidSphere manipulator;
Simulator simulator;
Mesh mesh;

using namespace std;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Simulation & Display

//draw the world in 3D using the display method of GUI
void Display() 
{
	//Start 3D rendering 
	GUI::begin3DScene();

	//Define the color used to draw the mesh
	GUI::setDrawColor(1, 1, 1);

	//draw the body of the scene
	GUI::drawMesh(mesh);

	//Draw the manipulator
	GUI::setDrawColor(0.85, 0.2, 0.2);
	manipulator.Draw();
	
	//terminate the rendering, and display the drawn scene on the main window
	GUI::end3DScene();
}

//main loop of the application (automatically called by the GUI class) 
//Composed of 2 parts : simulate the world, and display the world
void app_loop() 
{	
	//Update the simulation
	simulator.Update();
	
	//Update the haptic device
	//haptic_client.setForce();

	//Draw the world
	Display();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//Interaction

//function called when the a button has been clicked on the mouse
//x and y represent the current position of the cursor on the window
void mouseButtonClicked(int button_id, int x, int y) 
{
	if (button_id == MOUSE_LEFT_BUTTON) 
	{
		cout << "clicked : LEFT" << " - " << " - " << x << " - " << y << endl;
	}
	if (button_id == MOUSE_MIDDLE_BUTTON)
	{
		cout << "clicked : MIDDLE" << " - " << " - " << x << " - " << y << endl;	
	}
	if (button_id == MOUSE_RIGHT_BUTTON)
	{
		cout << "clicked : RIGHT" << " - " << " - " << x << " - " << y << endl;
	}
}

//Called when the mouse is moved over the window while a button is pressed
//x and y represent the current position of the cursor on the window
//you can call GUI::getMousButtonState(int) to check the state of the buttons
void mouseDragged(int x, int y) 
{
	if (GUI::getMouseButtonState(MOUSE_LEFT_BUTTON)) 
	{
		cout << "MouseDrag - left button: (" << x << "," << y << ")" << endl;
	}
}

//called when a key of the keyboard has been pressed
void keyPressed(unsigned char key) 
{
	cout << "key pressed: " << key << endl;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//Main Function

int main(int argc, char **argv) 
{
	//Initialize main global variables
	GUI::init(argc, argv);

	//Create the main window of the application. This function must be called only once !
	GUI::createWindow("MIV Project", 800, 800);
	
	//Load the mesh object
	mesh.loadFromFile("./media/meshes/cloth1.obj");
	//mesh.loadFromFile("./media/meshes/liver1.mshdat");

	//Define the shape and the position of the manipulator
	manipulator.setRadius(1.0f);
	manipulator.setPosition(Maths::Vector3(0,-0.25,0));

	//Creates and initializes the simulator which will update the mesh
	simulator.setMesh(&mesh);
	simulator.setManipulator(&manipulator);
	
	//Haptic initialization
	//haptic_client.init();
			
	//Start the application loop. This function returns when the main window is closed
	GUI::startApp(app_loop, mouseButtonClicked, mouseDragged, keyPressed);
	
	return 0;
}