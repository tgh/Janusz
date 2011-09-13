/**
 * Author: Tyler Hayes, (C) 2009
 * 
 * This is a demo for a program in which a cinematographer
 * can manipulate an indoor scene with subjects and lighting
 * as a previsualization of a shot for a film.
 */

#include <iostream>
#include <GL/glut.h>            //for OpenGL and GLUT (openGL Utility Toolkit)
#include <GL/gl.h>
#include <cstdlib>
#include <cmath>                //for sin, cos, etc.

#define PI        3.14159
#define PRESSED   1             //for mouse button pressed state
#define RELEASED  0             //for mouse button released state


//----------------------------------------------------------------------------
//--                          GLOBAL VARIABLES                              --
//----------------------------------------------------------------------------

//display list id's
GLuint head_list_id;            //display list id of heads
GLuint body_list_id;            //display list id of bodies
GLuint light_head_id;           //display list id of the head of a light stand
GLuint light_base_id;           //display list id of the base of a light stand

//mouse variables
int diff_x;                     //difference in x position from last position
int diff_y;                     //difference in y position from last position
int last_x;                     //the last x position of mouse
int last_y;                     //the last y position of mouse
int left_button;                //state of left mouse button
int mid_button;                 //state of middle mouse button
int right_button;               //state of right mouse button

//light 1 object variables
GLfloat light1_x      =  8.0f;  //x coord for light 1 object placement
GLfloat light1_z      = -5.0f;  //z coord for light 1 object placement
GLfloat light1_red    =  1.0f;  //red brightness for light 1
GLfloat light1_green  =  1.0f;  //green brightness for light 1
GLfloat light1_blue   =  1.0f;  //blue brightness for light 1
GLfloat light1_height =  5.0f;  //height of the light stand pole for light 1

//light 2 object variables
GLfloat light2_x      = -8.0f;  //see comments for light 1
GLfloat light2_z      = -5.0f;
GLfloat light2_red    =  1.0f;
GLfloat light2_green  =  1.0f;
GLfloat light2_blue   =  1.0f;
GLfloat light2_height =  5.0f;

//light 3 object variables
GLfloat light3_x      =  1.0f;  //see comments for light 1
GLfloat light3_z      =  5.0f;
GLfloat light3_red    =  1.0f;
GLfloat light3_green  =  1.0f;
GLfloat light3_blue   =  1.0f;
GLfloat light3_height =  5.0f;

//camera position variables
GLfloat camera_x      =  0.0f;  //x coord for camera position
GLfloat camera_y      =  0.0f;  //y coord for camera position
GLfloat camera_z      =  0.0f;  //z coord for camera position
GLfloat camera_pitch  =  0.0f;  //camera tilt angle
GLfloat camera_yaw    =  0.0f;  //camera pan angle
GLfloat camera_roll   =  0.0f;  //camera dutch angle

//person 1 position/orientation variables
GLfloat person1_x     =  2.5f;  //x coord for person 1 position
GLfloat person1_z     =  2.5f;  //z coord for person 1 position
GLfloat person1_xrot  =  0.0f;  //rotation angle about the feet and x-axis
GLfloat person1_yrot  = 45.0f;  //spin angle for person 1
GLfloat person1_zrot  =  0.0f;  //rotation angle about the feet and z-axis

//person 2 position/orientation variables
GLfloat person2_x     = -2.5f;  //see comments for person 1
GLfloat person2_z     = -2.5f;
GLfloat person2_xrot  =  0.0f;
GLfloat person2_yrot  = 45.0f;
GLfloat person2_zrot  =  0.0f;

//person 3 position/orientation variables
GLfloat person3_x     =  0.0f;  //see comments for person 1
GLfloat person3_z     =  0.0f;
GLfloat person3_xrot  =  0.0f;
GLfloat person3_yrot  =  0.0f;
GLfloat person3_zrot  =  0.0f;

//person 4 position/orientation variables
GLfloat person4_x     =  0.0f;  //see comments for person 1
GLfloat person4_z     =  0.0f;
GLfloat person4_xrot  =  0.0f;
GLfloat person4_yrot  =  0.0f;
GLfloat person4_zrot  =  0.0f;

//user control variables
bool camera_control   =  true;  //flag for user control over the camera
bool light1_control   = false;  //flag for user control over light #1
bool light2_control   = false;  //flag for user control over light #2
bool light3_control   = false;  //flag for user control over light #3
bool person1_control  = false;  //flag for user control over person #1
bool person2_control  = false;  //flag for user control over person #2
bool person3_control  = false;  //flag for user control over person #3
bool person4_control  = false;  //flag for user control over person #4
bool draw_light1      =  true;  //flag for whether or not to draw light #1
bool draw_light2      = false;  //flag for whether or not to draw light #2
bool draw_light3      = false;  //flag for whether or not to draw light #3
bool draw_person1     =  true;  //flag for whether or not to draw person 1
bool draw_person2     =  true;  //flag for whether or not to draw person 2
bool draw_person3     = false;  //flag for whether or not to draw person 3
bool draw_person4     = false;  //flag for whether or not to draw person 4
bool draw_grid        =  true;  //flag for whether or not to draw the grid lines
bool red              = false;  //flag for control over light's red brightness
bool green            = false;  //flag for control over light's green brightness
bool blue             = false;  //flag for control over light's blue brightness


//perspective angle (acts as focal length of lens (wide angle - telescopic)
GLfloat pers_angle    = 35.0f;

/**
 * window variables:  these are needed for calling window resize
 * function when the user changes the angle of perspective with the
 * '+' and '-' keys.  When this program is in fullscreen mode, these
 * variables wont change.
 */
int win_width;    //application window width (in pixels)
int win_height;   //application window height (in pixels)


//----------------------------------------------------------------------------
//--                      FUNCTION DECLARATIONS                             --
//----------------------------------------------------------------------------

//initialization, window setup, and enabling
void setup(int * argc, char ** argv);
//handles keyboard user interface
void key_handler(unsigned char key, int x, int y);
//handles when the window is resized
void window_resize(int width, int height);
//draws the scene
void draw();
//creates display list for heads
void head();
//creates display list for bodies
void body();
//creates display list for the head of a light stand
void light_head();
//creates display list for the base of a light stand
void light_base();
//faces the given light object towards the origin
void light_angle(GLfloat &x, GLfloat &z);
//places the given light object just behind the actual light source
void light_position(GLfloat &x, GLfloat &z);
//handles mouse clicks
void mouse_buttons(int button, int state, int x, int y);
//handles mouse movement when button(s) pressed
void mouse_motion(int x, int y);
//movement of a person based on mouse (helper for mouse_motion())
void person_mouse_control(GLfloat &x, GLfloat &z, GLfloat &x_rot,
                          GLfloat &y_rot, GLfloat &z_rot);
//movement of a light based on mouse (helper for mouse_motion())
void light_mouse_control(GLfloat &x, GLfloat &z, GLfloat &height);


//============================================================================
//==                                MAIN                                    ==
//============================================================================

int main (int argc, char ** argv)
{
   //perform all setup and initialization
   setup(&argc, argv);
   //tell OpenGL to use draw() to draw to the screen
   glutDisplayFunc(draw);
   //tell OpenGL to use key_handler() to handle keyboard interaction
   glutKeyboardFunc(key_handler);
   //tell OpenGL to use window_resize() to handle changes in the application
   // window size
   glutReshapeFunc(window_resize);
   //tell OpenGL to use mouse_buttons() for handling mouse button interaction           
   glutMouseFunc(mouse_buttons);
   //tell OpenGL to use mouse_motion() for handling mouse movement
   glutMotionFunc(mouse_motion);
   //loop main() until user hits <esc> to hard exit program or closes window
   glutMainLoop();
}


//----------------------------------------------------------------------------

/**
 * setup()
 *
 * Initializes GLUT, enabling, display lists, and the window.  Takes the
 * command-line arguments as its arguments.
 */
void setup(int * argc, char ** argv)
{
   //intialize GLUT
   glutInit(argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

   //set whe width and height of the window
   glutInitWindowSize(889, 500);
   //set the position of the window
   glutInitWindowPosition(150, 100);
   //set the title for the window
   glutCreateWindow("Janusz");

   /*
    * To set to FULLSCREEN mode, uncomment the next two function calls,
    * and comment out the previous 3 function calls
    */
   //set fullscreen mode
   /*glutGameModeString("1024x768:32@75");*/ /* fullscreen settings:
                                              * 1024x768 pixels,
                                              * 32 bits per pixel
                                              * at video refresh rate of 75Hz */
   //set GLUT to fullscreen using the settings in the line above
   //glutEnterGameMode();

   //enable depth comparisons & depth buffer updating
   glEnable(GL_DEPTH_TEST);    
   //make it possible to see the color of objects  
   glEnable(GL_COLOR_MATERIAL);
   //enable use of openGL lighting
   glEnable(GL_LIGHTING);
   //allow openGL to automatically normalize normal vectors
   glEnable(GL_NORMALIZE);
   //turn on smooth shading (openGL uses Gouraud shading)
   glShadeModel(GL_SMOOTH);

   //create a display list for the head of person
   head();
   //create a display list for the body of a person
   body();
   //create a display list for the top of a light stand
   light_head();
   //create a display list for the base of a light stand
   light_base();
}


//----------------------------------------------------------------------------

/**
 * key_handler()
 *
 * Handles what happens when a user hits a specific key.
 */
void key_handler(unsigned char key, int x, int y)
{
   switch (key) {
      //<esc>: exit program when escape key is hit
      case 27:
         //reset the screen (get out of fullscreen mode)
         //glutLeaveGameMode();
         exit(0);

      //switch user control to camera
      case 'c': case 'C':
         if (!camera_control) {
            camera_control = true;
            light1_control = false;
            light2_control = false;
            light3_control = false;
            person1_control = false;
            person2_control = false;
            person3_control = false;
            person4_control = false;
            red = false;
            green = false;
            blue = false;
         }
         break;

      //switch user control to person 1 object
      case '1':
         if (!person1_control) {
            camera_control = false;
            light1_control = false;
            light2_control = false;
            light3_control = false;
            person1_control = true;
            person2_control = false;
            person3_control = false;
            person4_control = false;
         }
         break;

      //switch user control to person 2 object
      case '2':
         if (!person2_control) {
            camera_control = false;
            light1_control = false;
            light2_control = false;
            light3_control = false;
            person1_control = false;
            person2_control = true;
            person3_control = false;
            person4_control = false;
         }
         break;

      //switch user control to person 3 object
      case '3':
         if (!person3_control) {
            camera_control = false;
            light1_control = false;
            light2_control = false;
            light3_control = false;
            person1_control = false;
            person2_control = false;
            person3_control = true;
            person4_control = false;
         }
         break;

      //switch user control to person 4 object
      case '4':
         if (!person4_control) {
            camera_control = false;
            light1_control = false;
            light2_control = false;
            light3_control = false;
            person1_control = false;
            person2_control = false;
            person3_control = false;
            person4_control = true;
         }
         break;

      //switch user control to light #1 object
      case '6':
         if (!light1_control) {
            camera_control = false;
            light1_control = true;
            light2_control = false;
            light3_control = false;
            person1_control = false;
            person2_control = false;
            person3_control = false;
            person4_control = false;
         }
         break;

      //switch user control to light #2 object
      case '7':
         if (!light2_control) {
            camera_control = false;
            light1_control = false;
            light2_control = true;
            light3_control = false;
            person1_control = false;
            person2_control = false;
            person3_control = false;
            person4_control = false;
         }
         break;

      //switch user control to light #3 object
      case '8':
         if (!light3_control) {
            camera_control = false;
            light1_control = false;
            light2_control = false;
            light3_control = true;
            person1_control = false;
            person2_control = false;
            person3_control = false;
            person4_control = false;
         }
         break;

      //camera dolly forward
      case 'w': case 'W':
         camera_x -= float(sin(camera_yaw / 180 * PI));
         camera_z += float(cos(camera_yaw / 180 * PI));
         camera_y += float(sin(camera_pitch / 180 * PI));
         break;

      //camera dolly back
      case 's': case 'S':
         camera_x += float(sin(camera_yaw / 180 * PI));
         camera_z -= float(cos(camera_yaw / 180 * PI));
         camera_y -= float(sin(camera_pitch / 180 * PI));
         break;

      //camera dolly left
      case 'a': case 'A':
         camera_x += float(cos(camera_yaw / 180 * PI)) * 0.2;
         camera_z += float(sin(camera_yaw / 180 * PI)) * 0.2;
         break;

      //camera dolly right
      case 'd': case 'D':
         camera_x -= float(cos(camera_yaw / 180 * PI)) * 0.2;
         camera_z -= float(sin(camera_yaw / 180 * PI)) * 0.2;
         break;

      //raise camera
      case 'q': case 'Q':
         camera_y -= float(cos(camera_roll / 180 * PI)) * 0.2;
         break;

      //lower camera
      case 'z': case 'Z':
         camera_y += float(cos(camera_roll / 180 * PI)) * 0.2;
         break;

      //zoom in (when in camera control) or increase brightness (when in light
      // control)
      case '+': case '=':
         //camera zoom in
         if (camera_control) {
            //lens angle has a minimum of 1.0
            if (pers_angle >= 2.0) {
               pers_angle -= 1.0;
               //call window_resize() in order for change in perspective to
               // take effect
               window_resize(win_width, win_height);
            }
         }
         //increase color brightness of light 1
         else if (light1_control) {
            if (red) {
               if (light1_red >= 0.0 && light1_red <= 0.9) {
                  light1_red += 0.1;
               }
            }
            else if (green) {
               if (light1_green >= 0.0 && light1_green <= 0.9) {
                  light1_green += 0.1;
               }
            }
            else if (blue) {
               if (light1_blue >= 0.0 && light1_blue <= 0.9) {
                  light1_blue += 0.1;
               }
            }
         }
         //increase color brightness of light 2
         else if (light2_control) {
            if (red) {
               if (light2_red >= 0.0 && light2_red <= 0.9) {
                  light2_red += 0.1;
               }
            }
            else if (green) {
               if (light2_green >= 0.0 && light2_green <= 0.9) {
                  light2_green += 0.1;
               }
            }
            else if (blue) {
               if (light2_blue >= 0.0 && light2_blue <= 0.9) {
                  light2_blue += 0.1;
               }
            }
         }
         //increase color brightness of light 3
         else if (light3_control) {
            if (red) {
               if (light3_red >= 0.0 && light3_red <= 0.9) {
                  light3_red += 0.1;
               }
            }
            else if (green) {
               if (light3_green >= 0.0 && light3_green <= 0.9) {
                  light3_green += 0.1;
               }
            }
            else if (blue) {
               if (light3_blue >= 0.0 && light3_blue <= 0.9) {
                  light3_blue += 0.1;
               }
            }
         }
         break;

      //zoom out (when in camera control) or decrease brightness (when in light
      // control)
      case '-': case '_':
         //camera zoom out    
         if (camera_control) {
            //lens angle has a maximum of 89.0
            if (pers_angle <= 88.0) {
               pers_angle += 1.0;
               //call window_resize() in order for change in perspective to
               // take effect
               window_resize(win_width, win_height);
            }
         }
         //decrease color brightness of light 1
         else if (light1_control) {
            if (red) {
               if (light1_red >= 0.1 && light1_red <= 1.0) {
                  light1_red -= 0.1;
               }
            }
            else if (green) {
               if (light1_green >= 0.1 && light1_green <= 1.0) {
                  light1_green -= 0.1;
               }
            }
            else if (blue) {
               if (light1_blue >= 0.1 && light1_blue <= 1.0) {
                  light1_blue -= 0.1;
               }
            }
         }
         //decrease color brightness of light 2
         else if (light2_control) {
            if (red) {
               if (light2_red >= 0.1 && light2_red <= 1.0)
                  light2_red -= 0.1;
            }
            else if (green) {
               if (light2_green >= 0.1 && light2_green <= 1.0)
                  light2_green -= 0.1;
            }
            else if (blue) {
               if (light2_blue >= 0.1 && light2_blue <= 1.0)
                  light2_blue -= 0.1;
            }
         }
         //decrease color brightness of light 3
         else if (light3_control) {
            if (red) {
               if (light3_red >= 0.1 && light3_red <= 1.0) {
                  light3_red -= 0.1;
               }
            }
            else if (green) {
               if (light3_green >= 0.1 && light3_green <= 1.0) {
                  light3_green -= 0.1;
               }
            }
            else if (blue) {
               if (light3_blue >= 0.1 && light3_blue <= 1.0) {
                  light3_blue -= 0.1;
               }
            }
         }
         break;

      //set the currently controlled object's draw flag (for on/off)
      case 'o': case 'O':
         if (light1_control && !draw_light1) {
            draw_light1 = true;
         }
         else if (light1_control && draw_light1) {
            draw_light1 = false;
            glDisable(GL_LIGHT0);
         }
         else if (light2_control && !draw_light2) {
            draw_light2 = true;
         }
         else if (light2_control && draw_light2) {
            draw_light2 = false;
            glDisable(GL_LIGHT1);
         }
         else if (light3_control && !draw_light3) {
            draw_light3 = true;
         }
         else if (light3_control && draw_light3) {
            draw_light3 = false;
            glDisable(GL_LIGHT2);
         }
         else if (person1_control && !draw_person1) {
            draw_person1 = true;
         }
         else if (person1_control && draw_person1) {
            draw_person1 = false;
         }
         else if (person2_control && !draw_person2) {
            draw_person2 = true;
         }
         else if (person2_control && draw_person2) {
            draw_person2 = false;
         }
         else if (person3_control && !draw_person3) {
            draw_person3 = true;
         }
         else if (person3_control && draw_person3) {
            draw_person3 = false;
         }
         else if (person4_control && !draw_person4) {
            draw_person4 = true;
         }
         else if (person4_control && draw_person4) {
            draw_person4 = false;
         }
         break;

      //set the flag for drawing the grid lines
      case 'l': case 'L':
         if (draw_grid) {
            draw_grid = false;
         }
         else {
            draw_grid = true;
         }
         break;

      //give control to the current light's red brightness (for +/-)
      case 'r': case 'R':
         if (!red) {
            camera_control = false;
            red = true;
            green = false;
            blue = false;
         }
         break;

      //give control to the current light's green brightness (for +/-)
      case 'g': case 'G':
         if (!green) {
            camera_control = false;
            red = false;
            green = true;
            blue = false;
         }
         break;

      //give control to the current light's blue brightness (for +/-)
      case 'b': case 'B':
         if (!blue) {
            camera_control = false;
            red = false;
            green = false;
            blue = true;
         }
         break;
   }

   //mark the current window as needing to be redisplayed
   glutPostRedisplay();
}


//----------------------------------------------------------------------------

/**
 * window_resize()
 *
 * Handles when the user resizes the application window. When this program
 * is in fullscreen mode, this function is mostly called when the user
 * adjusts the camera perspective angle with the +/- keys while under camera
 * control.
 */
void window_resize(int width, int height)
{
   //ensure that divide by zero wont happen in gluPerspective() call below
   if (height == 0) {
      height = 1;
   }
   //these are set and wont ever change, but are needed when window_resize() is
   // called due to a change in camera perspective
   win_width = width;
   win_height = height;

   //set the viewport
   glViewport (0, 0, width, height);
   //switch to projection perspective  
   glMatrixMode (GL_PROJECTION);
   //replace the current matrix with the identity matrix (i.e. clear or reset
   // the current matrix)
   glLoadIdentity ();
   //set view volume (camera focal length, viewing aspect ratio, and view depth)
   gluPerspective (pers_angle, (GLfloat)width / (GLfloat)height, 1.0, 500.0);
}


//----------------------------------------------------------------------------

/**
 * draw()
 *
 * Draw to the screen.
 */
void draw()
{
   //set background color to black
   glClearColor(0.0, 0.0, 0.0, 0.0);
   //clear info from last draw
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //switch to the drawing perspective
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   //rotate and translate the scene to simulate camera movement
   glRotatef(camera_pitch, 1.0, 0.0, 0.0);
   glRotatef(camera_yaw, 0.0, 1.0, 0.0);
   glRotatef(camera_roll, 0.0, 0.0, 1.0);
   glTranslatef(camera_x, camera_y, camera_z);

   //initiate camera position and angle
   gluLookAt (0.0, 5.0, -35.0,   //camera position
              0.0, 5.0, 0.0,     //look-at point
              0.0, 1.0, 0.0);    //up direction

   //draw light #1 and its light stand object
   if (draw_light1) {
      //turn on light #1
      glEnable(GL_LIGHT0);

      //draw light #1 effect
      GLfloat diff_light[] = {light1_red, light1_green, light1_blue, 1.0};
      GLfloat l_position[] = {light1_x,
                              1 + light1_height + 2*sinf(PI/18),
                              light1_z,
                              1.0f};
      glLightfv (GL_LIGHT0, GL_DIFFUSE, diff_light);
      glLightfv (GL_LIGHT0, GL_POSITION, l_position);

      //draw light #1 stand base and head
      glPushMatrix();
         light_position(light1_x, light1_z);
         light_angle(light1_x, light1_z);
         glCallList(light_base_id);
         glPushMatrix();
            glTranslatef(0.0, light1_height, 0.0);
            glCallList(light_head_id);
         glPopMatrix();
      glPopMatrix();

      //light #1 stand pole
      glPushMatrix();
         light_position(light1_x, light1_z);
         glTranslatef(0.0f, light1_height + 2*sinf(PI/18), 0.0);
         glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
         glColor3f(0.2, 0.2, 0.2);
         GLUquadricObj * light_stand;
         light_stand = gluNewQuadric();
         gluQuadricDrawStyle(light_stand, GLU_FILL);
         gluCylinder(light_stand, 0.05f, 0.05f, light1_height, 8, 8);
         glEnd();
      glPopMatrix();
   }

   //draw light #2 and its light stand object
   if (draw_light2) {
      //turn on light #2
      glEnable(GL_LIGHT1);
	   
      //draw light #2 effect
      GLfloat diff_light[] = {light2_red, light2_green, light2_blue, 1.0};
      GLfloat l_position[] = {light2_x,
                              1 + light2_height + 2*sinf(PI/18),
                              light2_z,
                              1.0f};
      glLightfv (GL_LIGHT1, GL_DIFFUSE, diff_light);
      glLightfv (GL_LIGHT1, GL_POSITION, l_position);

      //draw light #2 stand base and head
      glPushMatrix();
         light_position(light2_x, light2_z);
         light_angle(light2_x, light2_z);
         glCallList(light_base_id);
         glPushMatrix();
            glTranslatef(0.0, light2_height, 0.0);
            glCallList(light_head_id);
         glPopMatrix();
      glPopMatrix();
      
      //light #2 stand pole
      glPushMatrix();
         light_position(light2_x, light2_z);
         glTranslatef(0.0f, light2_height + 2*sinf(PI/18), 0.0);
         glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
         glColor3f(0.2, 0.2, 0.2);
         GLUquadricObj * light_stand;
         light_stand = gluNewQuadric();
         gluQuadricDrawStyle(light_stand, GLU_FILL);
         gluCylinder(light_stand, 0.05f, 0.05f, light2_height, 8, 8);
         glEnd();
      glPopMatrix();
   }

   //draw light #3 and its light stand object
   if (draw_light3) {
      //turn on light #3
      glEnable(GL_LIGHT2);

      //draw light #3 effect
      GLfloat diff_light[] = {light3_red, light3_green, light3_blue, 1.0};
      GLfloat l_position[] = {light3_x, 6.0 + 2*sinf(PI/18), light3_z, 1.0f};
      glLightfv (GL_LIGHT2, GL_DIFFUSE, diff_light);
      glLightfv (GL_LIGHT2, GL_POSITION, l_position);

      //draw light #3 stand base and head
      glPushMatrix();
         light_position(light3_x, light3_z);
         light_angle(light3_x, light3_z);
         glCallList(light_base_id);
         glPushMatrix();
            glTranslatef(0.0, light3_height, 0.0);
            glCallList(light_head_id);
         glPopMatrix();
      glPopMatrix();

      //light #3 stand pole
      glPushMatrix();
         light_position(light3_x, light3_z);
         glTranslatef(0.0f, light3_height + 2*sinf(PI/18), 0.0);
         glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
         glColor3f(0.2, 0.2, 0.2);
         GLUquadricObj * light_stand;
         light_stand = gluNewQuadric();
         gluQuadricDrawStyle(light_stand, GLU_FILL);
         gluCylinder(light_stand, 0.05f, 0.05f, light3_height, 8, 8);
         glEnd();
      glPopMatrix();
   }

   //draw the grid lines
   if (draw_grid) {
      glBegin (GL_LINES);
      glColor3f(0.5f, 0.5f, 0.5f);
      for (int i = -10; i <= 10; ++i) {
         //floor
         glVertex3f(i, 0, -10);
         glVertex3f(i, 0, 10);
         glVertex3f(10, 0, i);
         glVertex3f(-10, 0, i);
         //back wall
         glVertex3f(i, 0, 10);
         glVertex3f(i, 10, 10);
         //left wall
         glVertex3f(10, 0, i);
         glVertex3f(10, 10, i);
         //right wall
         glVertex3f(-10, 0, i);
         glVertex3f(-10, 10, i);
      }
      for (int i = 0; i <= 10; ++i) {
         //back wall
         glVertex3f(10, i, 10);
         glVertex3f(-10, i, 10);
         //left wall
         glVertex3f(10, i, -10);
         glVertex3f(10, i, 10);
         //right wall
         glVertex3f(-10, i, -10);
         glVertex3f(-10, i, 10);
      }
      glEnd(); //GL_LINES for grid
   }

   //DRAW PERSON 1 (GREEN)
   if (draw_person1) {
      glPushMatrix();
         //set the postition and orientation of person 1
         glTranslatef(person1_x, 0.0f, person1_z);
         glRotatef(person1_xrot, 1.0f, 0.0f, 0.0f);
         glRotatef(person1_zrot, 0.0f, 0.0f, 1.0f);
         glRotatef(person1_yrot, 0.0f, 1.0f, 0.0f);
         glScalef(0.7f, 0.7f, 0.55f);
   	     //head for person 1
         glPushMatrix();
            glColor3f(1.0f, .9f, .6f);
            glCallList(head_list_id); //call the head display list
         glPopMatrix();
         //body for person 1
         glPushMatrix();
            glColor3f(0.0f, 0.8f, 0.0f);
            glCallList(body_list_id);	//call the body display list
         glPopMatrix();
      glPopMatrix();
   }

   //DRAW PERSON 2 (RED)
   if (draw_person2) {
      glPushMatrix();
         //set the postition and orientation of person 2
         glTranslatef(person2_x, 0.0f, person2_z);
         glRotatef(person2_xrot, 1.0f, 0.0f, 0.0f);
         glRotatef(person2_zrot, 0.0f, 0.0f, 1.0f);
         glRotatef(person2_yrot, 0.0f, 1.0f, 0.0f);
         glScalef(0.8f, 0.8f, 0.65f);
         //head for person 2
         glPushMatrix();
            glColor3f(0.9f, 0.7f, 0.6f);
            glCallList(head_list_id);
         glPopMatrix();
         //body for person 2
         glPushMatrix();
            glColor3f(0.7f, 0.0f, 0.1f);
            glCallList(body_list_id);
         glPopMatrix();
      glPopMatrix();
   }

   //DRAW PERSON 3 (BLUE)
   if (draw_person3) {
      glPushMatrix();
         //set the postition and orientation of person 3
         glTranslatef(person3_x, 0.0f, person3_z);
         glRotatef(person3_xrot, 1.0f, 0.0f, 0.0f);
         glRotatef(person3_zrot, 0.0f, 0.0f, 1.0f);
         glRotatef(person3_yrot, 0.0f, 1.0f, 0.0f);
         glScalef(0.7f, 0.65f, 0.6f);
         //head for person 3
         glPushMatrix();
            glColor3f(0.9f, 0.9f, 0.8f);
            glCallList(head_list_id);
         glPopMatrix();
         //body for person 3
         glPushMatrix();
            glColor3f(0.1f, 0.0f, 0.9f);
            glCallList(body_list_id);
         glPopMatrix();
      glPopMatrix();
   }

   //DRAW PERSON 4 (YELLOW)
   if (draw_person4) {
      glPushMatrix();
         //set the postition and orientation of person 4
         glTranslatef(person4_x, 0.0f, person4_z);
         glRotatef(person4_xrot, 1.0f, 0.0f, 0.0f);
         glRotatef(person4_zrot, 0.0f, 0.0f, 1.0f);
         glRotatef(person4_yrot, 0.0f, 1.0f, 0.0f);
         glScalef(0.75f, 0.85f, 0.65f);
         //head for person 4
         glPushMatrix();
            glColor3f(0.5f, 0.5f, 0.2f);
            glCallList(head_list_id);
         glPopMatrix();
         //body for person 4
         glPushMatrix();
            glColor3f(0.9f, 0.9f, 0.0f);
            glCallList(body_list_id);
         glPopMatrix();
      glPopMatrix();
   }

   //swap the current window with the buffered window
   glutSwapBuffers();
}


//----------------------------------------------------------------------------

/**
 * head()
 *
 * Creates a display list for the head of a person.
 */
void head()
{
   //generate a list for a head and get its id
   head_list_id = glGenLists(1);
   //compile the new display list
   glNewList(head_list_id, GL_COMPILE);

   glPushMatrix();
      glTranslatef(0.0f, 6.05f, 0.0f);
      //create a basic head with a sphere
      glutSolidSphere(.80f, 25, 25);
   glPopMatrix();

   glEndList();
}


//----------------------------------------------------------------------------

/**
 * body()
 *
 * Creates a display list for the body of a person.
 */
void body()
{
   GLfloat fan_angle;   //angle for a triangle fan
   int sections = 40;   //number of triangles in a triangle fan

   //generate a display list for a body
   body_list_id = glGenLists(1);
   //compile the new display list
   glNewList(body_list_id, GL_COMPILE);

   glPushMatrix();
      glTranslatef(0.0f, 5.05f, 0.0f);
      glRotatef(90, 1.0, 0.0, 0.0);

      //create a torso with a cylinder
      glPushMatrix();
         GLUquadricObj * torso;
         torso = gluNewQuadric();
         gluQuadricDrawStyle(torso, GLU_FILL);
         gluCylinder(torso, 1.0f, 1.0f, 2.25f, 25, 25);
      glPopMatrix();

      //triangle fan for top of body
      glPushMatrix();
         glRotatef(180.0, 0.0, 1.0, 0.0);
         glBegin(GL_TRIANGLE_FAN);
         glNormal3f(0.0f, 0.0f, 1.0f);
         glVertex3f(0.0f, 0.0f, 0.0f);
         for(int i = 0; i <= sections; ++i) {
            fan_angle = (GLfloat) i * 2 * PI / sections;
            glVertex3f(cosf(fan_angle), sinf(fan_angle), 0.0f);
         }
         glEnd();
      glPopMatrix();

      //triangle fan for bottom of torso
      glPushMatrix();
         glTranslatef(0.0, 0.0, 2.25);
         glBegin(GL_TRIANGLE_FAN);
         glNormal3f(0.0f, 0.0f, 1.0f);
         glVertex3f(0.0f, 0.0f, 0.0f);
         for(int i = 0; i <= sections; ++i) {
            fan_angle = (GLfloat) i * 2 * PI / sections;
            glVertex3f(cosf(fan_angle), sinf(fan_angle), 0.0f);
         }
         glEnd();
      glPopMatrix();

      //arm 1
      glPushMatrix();
         glTranslatef(1.25f, 0.0f, 0.0f);
         GLUquadricObj * arm1;
         arm1 = gluNewQuadric();
         gluQuadricDrawStyle(arm1, GLU_FILL);
         gluCylinder(arm1, 0.25f, 0.25f, 2.5f, 12, 12);
      glPopMatrix();

      //triangle fan for top of arm 1
      glPushMatrix();
         glTranslatef(1.25, 0.0, 0.0);
         glRotatef(180.0, 0.0, 1.0, 0.0);
         glBegin(GL_TRIANGLE_FAN);
         glNormal3f(0.0f, 0.0f, 1.0f);
         glVertex3f(0.0f, 0.0f, 0.0f);
         sections = 12;
         for(int i = 0; i <= sections; ++i) {
            fan_angle = (GLfloat) i * 2 * PI / sections;
            glVertex3f(0.25*cosf(fan_angle), 0.25*sinf(fan_angle), 0.0f);
         }
         glEnd();
      glPopMatrix();

      //triangle fan for bottom of arm 1
      glPushMatrix();
         glTranslatef(1.25, 0.0, 2.5);
         glBegin(GL_TRIANGLE_FAN);
         glNormal3f(0.0f, 0.0f, 1.0f);
         glVertex3f(0.0f, 0.0f, 0.0f);
         sections = 12;
         for(int i = 0; i <= sections; ++i) {
            fan_angle = (GLfloat) i * 2 * PI / sections;
            glVertex3f(0.25*cosf(fan_angle), 0.25*sinf(fan_angle), 0.0f);
         }
         glEnd();
      glPopMatrix();

      //arm 2
      glPushMatrix();
         glTranslatef(-1.25f, 0.0f, 0.0f);
         GLUquadricObj * arm2;
         arm2 = gluNewQuadric();
         gluQuadricDrawStyle(arm2, GLU_FILL);
         gluCylinder(arm2, 0.25f, 0.25f, 2.5f, 12, 12);
      glPopMatrix();

      //triangle fan for top of arm 2
      glPushMatrix();
         glTranslatef(-1.25, 0.0, 0.0);
         glRotatef(180.0, 0.0, 1.0, 0.0);
         glBegin(GL_TRIANGLE_FAN);
         glNormal3f(0.0f, 0.0f, 1.0f);
         glVertex3f(0.0f, 0.0f, 0.0f);
         sections = 12;
         for(int i = 0; i <= sections; ++i) {
            fan_angle = (GLfloat) i * 2 * PI / sections;
            glVertex3f(0.25*cosf(fan_angle), 0.25*sinf(fan_angle), 0.0f);
         }
         glEnd();
      glPopMatrix();

      //triangle fan for bottom of arm 2
      glPushMatrix();
         glTranslatef(-1.25, 0.0, 2.5);
         glBegin(GL_TRIANGLE_FAN);
         glNormal3f(0.0f, 0.0f, 1.0f);
         glVertex3f(0.0f, 0.0f, 0.0f);
         sections = 12;
         for(int i = 0; i <= sections; ++i) {
            fan_angle = (GLfloat) i * 2 * PI / sections;
            glVertex3f(0.25*cosf(fan_angle), 0.25*sinf(fan_angle), 0.0f);
         }
         glEnd();
      glPopMatrix();

      //leg 1
      glPushMatrix();
         glTranslatef(0.5f, 0.0f, 2.25f);
         GLUquadricObj * leg1;
         leg1 = gluNewQuadric();
         gluQuadricDrawStyle(leg1, GLU_FILL);
         gluCylinder(leg1, 0.5f, 0.2f, 2.8f, 12, 12);
      glPopMatrix();

      //triangle fan for bottom of leg 1
      glPushMatrix();
         glTranslatef(0.5, 0.0, 5.05);
         glBegin(GL_TRIANGLE_FAN);
         glNormal3f(0.0f, 0.0f, 1.0f);
         glVertex3f(0.0f, 0.0f, 0.0f);
         sections = 12;
         for(int i = 0; i <= sections; ++i) {
            fan_angle = (GLfloat) i * 2 * PI / sections;
            glVertex3f(0.2*cosf(fan_angle), 0.2*sinf(fan_angle), 0.0f);
         }
         glEnd();
      glPopMatrix();

      //leg 2
      glPushMatrix();
         glTranslatef(-0.5f, 0.0f, 2.25f);
         GLUquadricObj * leg2;
         leg2 = gluNewQuadric();
         gluQuadricDrawStyle(leg2, GLU_FILL);
         gluCylinder(leg2, 0.5f, 0.2f, 2.8f, 12, 12);
      glPopMatrix();

      //triangle fan for bottom of leg 2
      glPushMatrix();
         glTranslatef(-0.5, 0.0, 5.05);
         glBegin(GL_TRIANGLE_FAN);
         glNormal3f(0.0f, 0.0f, 1.0f);
         glVertex3f(0.0f, 0.0f, 0.0f);
         sections = 12;
         for(int i = 0; i <= sections; ++i) {
            fan_angle = (GLfloat) i * 2 * PI / sections;
            glVertex3f(0.2*cosf(fan_angle), 0.2*sinf(fan_angle), 0.0f);
         }
         glEnd();
      glPopMatrix();

   glPopMatrix();

   glEndList();
}


//----------------------------------------------------------------------------

/**
 * light_head()
 *
 * Creates a display list for the head of a light stand (where the light is).
 */
void light_head()
{
   //generate a display list for a light head and get its id
   light_head_id = glGenLists(1);
   //compile the new display list
   glNewList(light_head_id, GL_COMPILE);
   
   //place the origin at the very bottom center of the light stand
   glPushMatrix();
      glTranslatef(0.0f, 1.0 + 2*sinf(PI/18), -0.125);

      //light head cylinder
      glPushMatrix();
         glColor3f(0.1, 0.1, 0.1);
         GLUquadricObj * light_head;
         light_head = gluNewQuadric();
         gluQuadricDrawStyle(light_head, GLU_FILL);
         gluCylinder(light_head, 1.0f, 1.0f, 0.25f, 30, 30);
      glPopMatrix();

      /*
      //normal reference for triangle fan (a line to show where the light is
      // pointing)
      glPushMatrix();
         glBegin(GL_LINES);
         glColor3f(1.0, 1.0, 0.0);
         glVertex3f(0.0, 0.0, 0.125);
         glVertex3f(0.0, 0.0, 3.0);
         glEnd();
      glPopMatrix();
      */

      //triangle fan for light face
      glPushMatrix();
         glTranslatef(0.0f, 0.0f, 0.125f);
         glBegin(GL_TRIANGLE_FAN);
         glColor3f(1.0f, 1.0f, 1.0f);
         GLfloat fan_angle;
         int sections = 40;
         glNormal3f(0.0f, 0.0f, 1.0f);
         glVertex3f(0.0f, 0.0f, 0.0f);
         for(int i = 0; i <= sections; ++i) {
            fan_angle = (GLfloat) i * 2 * PI / sections;
            glVertex3f(0.99*cosf(fan_angle), 0.99*sinf(fan_angle), 0.0f);
         }
         glEnd();
      glPopMatrix();

   glPopMatrix();

   glEndList();
}


//----------------------------------------------------------------------------

/**
 * light_base()
 *
 * Creates a display list for the base of a light stand.
 */
void light_base ()
{
   //generate a display list for a light stand base and get its id
   light_base_id = glGenLists(1);
   //compile the new display list
   glNewList(light_base_id, GL_COMPILE);

   //place the origin at the very bottom center of the light stand
   glPushMatrix();
      glTranslatef(0.0f, 6.0 + 2*sinf(PI/18), 0.0);

      //light stand leg 1
      glPushMatrix();
         glTranslatef(0.0f, -6.0f, 0.0f);
         glRotatef(120.0f, 0.0f, 1.0f, 0.0f);
         glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
         glColor3f(0.2, 0.2, 0.2);
         GLUquadricObj * light_leg1;
         light_leg1 = gluNewQuadric();
         gluQuadricDrawStyle(light_leg1, GLU_FILL);
         gluCylinder(light_leg1, 0.05f, 0.05f, 1.5f, 8, 8);
         glEnd();
      glPopMatrix();

      //light stand leg 2
      glPushMatrix();
         glTranslatef(0.0f, -6.0f, 0.0f);
         glRotatef(-120.0f, 0.0f, 1.0f, 0.0f);
         glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
         glColor3f(0.2, 0.2, 0.2);
         GLUquadricObj * light_leg2;
         light_leg2 = gluNewQuadric();
         gluQuadricDrawStyle(light_leg2, GLU_FILL);
         gluCylinder(light_leg2, 0.05f, 0.05f, 1.5f, 8, 8);
         glEnd();
      glPopMatrix();

      //light stand leg 3
      glPushMatrix();
         glTranslatef(0.0f, -6.0f, 0.0f);
         glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
         glColor3f(0.2, 0.2, 0.2);
         GLUquadricObj * light_leg3;
         light_leg3 = gluNewQuadric();
         gluQuadricDrawStyle(light_leg3, GLU_FILL);
         gluCylinder(light_leg3, 0.05f, 0.05f, 1.5f, 8, 8);
         glEnd();
      glPopMatrix();

   glPopMatrix();

   glEndList();
}


//----------------------------------------------------------------------------

/**
 * light_angle()
 *
 * Rotates the respective light stand object to always face the origin no matter
 * where it is placed in the scene.
 */
void light_angle(GLfloat &x, GLfloat &z) 
{
   //if light is placed at origin, the rotation equation would divide by zero
   if (x != 0 || z != 0) {
      if (x > 0) {
         glRotatef(-90 - (asinf(z/(sqrtf(powf(x, 2)
                  + powf(z, 2)))) * 180/PI), 0.0, 1.0, 0.0);
      }
      else if (x < 0) {
         glRotatef(90 + (asinf(z/(sqrtf(powf(x, 2)
                   + powf(z, 2)))) * 180/PI), 0.0, 1.0, 0.0);
      }
      else if (x == 0 && z > 0) {
         glRotatef(0.0, 0.0, 1.0, 0.0);
      }
      else if (x == 0 && z < 0) {
         glRotatef(180.0, 0.0, 1.0, 0.0);
      }
      else if (z == 0 && x > 0) {
         glRotatef(-90.0, 0.0, 1.0, 0.0);
      }
      else if (z == 0 && x < 0) {
         glRotatef(90.0, 0.0, 1.0, 0.0);
      }
   }
}


//----------------------------------------------------------------------------

/**
 * light_position()
 *
 * Places the respective light stand object just behind the position of the
 * real diffuse light depending on where the light is placed.
 */
void light_position(GLfloat &x, GLfloat &z)
{
   if (x < 0 && z > 0) {
      glTranslatef(x - 0.25, 0.0, z + 0.25);
   }
   else if (x < 0 && z < 0) {
      glTranslatef(x - 0.25, 0.0, z - 0.25);
   }
   else if (x > 0 && z > 0) {
      glTranslatef(x + 0.25, 0.0, z + 0.25);
   }
   else if (x > 0 && z < 0) {
      glTranslatef(x + 0.25, 0.0, z - 0.25);
   }
   else if (x < 0 && z == 0) {
      glTranslatef(x - 0.25, 0.0, z);
   }
   else if (x > 0 && z < 0) {
      glTranslatef(x + 0.25, 0.0, z);
   }
   else if (x == 0 && z < 0) {
      glTranslatef(x, 0.0, z - 0.25);
   }
   else if (x == 0 && z > 0) {
      glTranslatef(x, 0.0, z + 0.25);
   }
}


//----------------------------------------------------------------------------

/**
 * mouse_buttons()
 *
 * Sets the appropriate flags when the mouse buttons are pressed/released.
 */
void mouse_buttons(int button, int state, int x, int y)
{
   //set the last x-position of mouse to current x-position
   last_x = x;
   //set the last y-position of mouse to current y-position
   last_y = y;

   //button pressed
   if (state == GLUT_DOWN) {
      switch(button) {
         case GLUT_LEFT_BUTTON:
            left_button = PRESSED;
            break;
         case GLUT_MIDDLE_BUTTON:
            mid_button = PRESSED;
            break;
         case GLUT_RIGHT_BUTTON:
            right_button = PRESSED;
            break;
      }
   }
   //button released
   else {
      switch(button) {
         case GLUT_LEFT_BUTTON:
            left_button = RELEASED;
            break;
         case GLUT_MIDDLE_BUTTON:
            mid_button = RELEASED;
            break;
         case GLUT_RIGHT_BUTTON:
            right_button = RELEASED;
            break;
      }
   }
}


//----------------------------------------------------------------------------

/**
 * mouse_motion()
 *
 * Determines what happens when the mouse moves during specific situations.
 */
void mouse_motion(int x, int y)
{
   //calculate the difference between current x- and y-positions and the last
   diff_x = x - last_x;
   diff_y = y - last_y;
   //set the last x- and y-position of mouse to current x- and y-positions
   last_x = x;
   last_y = y;

   //in camera control mode
   if (camera_control) {
      //mouse tilts and pans the camera when the LEFT button is pressed
      if (left_button == PRESSED) {
         camera_pitch += (float) diff_y/4;
         camera_yaw += (float) diff_x/4;
         if (camera_pitch > 360) {
            camera_pitch -= 360;
         }
         if (camera_yaw > 360) {
            camera_yaw -= 360;
         }
      }
      if (right_button == PRESSED) {
         //do nothing
      }
      if (mid_button == PRESSED) {
         //do nothing
      }
   }

   //in light #1 control mode
   else if (light1_control) {
      light_mouse_control(light1_x, light1_z, light1_height);
   }

   //in light #2 control mode
   else if (light2_control) {
      light_mouse_control(light2_x, light2_z, light2_height);
   }

   //in light #3 control mode
   else if (light3_control) {
      light_mouse_control(light3_x, light3_z, light3_height);
   }

   //in person #1 control mode
   else if (person1_control) {
      person_mouse_control(person1_x, person1_z, person1_xrot,
                           person1_yrot, person1_zrot);
   }

   //in person #2 control mode
   else if (person2_control) {
      person_mouse_control(person2_x, person2_z, person2_xrot,
                           person2_yrot, person2_zrot);
   }

   //in person #3 control mode
   else if (person3_control) {
      person_mouse_control(person3_x, person3_z, person3_xrot,
                           person3_yrot, person3_zrot);
   }

   //in person #4 control mode
   else if (person4_control) {
      person_mouse_control(person4_x, person4_z, person4_xrot,
                           person4_yrot, person4_zrot);
   }

   glutPostRedisplay();
}


//----------------------------------------------------------------------------

/**
 * light_mouse_control()
 *
 * Adjusts the given light's respective variables for orientation and/or
 * position.
 */
void light_mouse_control(GLfloat &x, GLfloat &z, GLfloat &height)
{
   //mouse changes light position when LEFT button is pressed
   if (left_button == PRESSED) {
      x -= 0.04 * diff_x;
      z -= 0.04 * diff_y;
   }
   //mouse changes light height when RIGHT button is pressed
   if (right_button == PRESSED) {
      height += -0.05 * diff_y;
      if (height >= 20.0) {
         height = 20.0;
      }
      else if (height <= 0.1) {
         height = 0.1;
      }
   }
   if (mid_button == PRESSED) {
      //do nothing
   }
}


//----------------------------------------------------------------------------

/**
 * person_mouse_control()
 *
 * Adjusts the given person's respective variables for orientation and/or
 * position.
 */
void person_mouse_control(GLfloat &x, GLfloat &z, GLfloat &x_rot,
                          GLfloat &y_rot, GLfloat &z_rot)
{
   //mouse changes person position when LEFT button pressed
   if (left_button == PRESSED) {
      x -= 0.025 * diff_x;
      z -= 0.025 * diff_y;
   }
   //mouse rotates person (along y-axis) when RIGHT button pressed
   if (right_button == PRESSED) {
      y_rot += 0.3 * diff_x;
      if (y_rot > 360) {
         y_rot -= 360;
      }
   }
   //mouse rotates person (along x- and z-axis) when MIDDLE button pressed
   if (mid_button == PRESSED) {
      z_rot += 0.3 * diff_x;
      if (z_rot > 360) {
         z_rot -= 360;
      }
      x_rot -= 0.3 * diff_y;
      if (x_rot < 0) {
         x_rot += 360;
      }
   }
}
