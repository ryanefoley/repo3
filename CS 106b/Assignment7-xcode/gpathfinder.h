/*
 * File: gpathfinder.h
 * -------------------
 * The gpathfinder.h file defines the interface for a set of functions
 * that help draw the necessary parts of the Pathfinder maps.  The
 * gpathfinder.h interface uses screen coordinates in which distances
 * on the screen are expressed in pixels and in which the origin in the
 * upper left corner of the window.  Several of the functions defined
 * in this package use values of type GPoint, which is simply a pair of
 * x and y coordinate values, as defined in the point.h interface.

 * Note that calls to the drawing functions in this interface are not
 * immediately reflected on the screen.  To get the changes to appear,
 * you need to call repaintPathfinderDisplay.  This design is more
 * efficient in terms of graphics processing, because it allows the
 * client to make many calls to the various drawing operations and then
 * update the display all at once.
 *
 * This interface also exports several methods for creating buttons
 * in a control strip and for responding to button and mouse clicks.
 * The general approach parallels the standard model used in modern
 * event-driven systems.  The client application creates a series of
 * buttons, each of which supplies a callback function that is
 * invoked whenever that button is clicked.  The application then
 * calls pathfinderEventLoop, which waits for events generated in
 * response to user actions.
 */

#ifndef _gpathfinder_h
#define _gpathfinder_h

#include "gtypes.h"



/*
 * Constants
 * ---------
 * A few program-wide constants concerning the graphical display.
 * All coordinate values and distances are expressed in pixels.
 */

const double NODE_RADIUS = 3.5;           /* Radius of the node circle    */
const double PAUSE_TIME = .05;            /* Controls speed of animation  */
const string ARC_COLOR = "DarkGray";      /* Normal arc color             */
const string NODE_COLOR = "Black";        /* Normal node color            */
const string HIGHLIGHT_COLOR = "Red";     /* Color of chosen path/nodes   */
const string DIM_COLOR = "Gray";          /* Color of unchosen path/nodes */
const string LABEL_FONT = "Helvetica-10"; /* Font for node labels         */

/*
 * Function: initPathfinderGraphics
 * Usage: initPathfinderGraphics();
 * --------------------------------
 * Initializes the graphics window for Pathfinder.  This call should
 * be the first statement in main.
 */

void initPathfinderGraphics();

/*
 * Function: drawPathfinderMap
 * Usage: drawPathfinderMap(mapFile);
 * ----------------------------------
 * Clears the graphics window and then draws the image contained in
 * the specified image file, which will typically live in an images
 * subdirectory of the project directory.
 */

void drawPathfinderMap(string mapFile);

/*
 * Function: drawPathfinderNode
 * Usage: drawPathfinderNode(center, color, label);
 * ------------------------------------------------
 * Draw a node circle whose center is at the coordinate position
 * specified by the first argument and that is filled in the specified
 * color.  If a third argument is provided, the function draws a label
 * to the right of the circle containing the specified text.
 */

void drawPathfinderNode(GPoint center, string color, string label = "");

/*
 * Function: drawPathfinderArc
 * Usage: drawPathfinderArc(start, end, color);
 * --------------------------------------------
 * Draws a line on the screen connecting the two specified coordinate
 * positions using the indicated color.
 */

void drawPathfinderArc(GPoint start, GPoint end, string color);

/*
 * Function: repaintPathfinderDisplay
 * Usage: repaintPathfinderDisplay();
 * ---------------------------------
 * Updates the display to reflect recent calls to drawing functions
 * such as drawPathfinderNode and drawPathfinderArc.
 */

void repaintPathfinderDisplay();

/*
 * Function: addButton
 * Usage: addButton(name, actionFn);
 *        addButton(name, actionFn, data);
 * ---------------------------------------
 * Adds a button to the window and assigns it an action function.
 * When the button is clicked, the program will invoke
 *
 *       actionFn()
 *
 * or
 *
 *       actionFn(data)
 *
 * depending on whether the data parameter is supplied.  The data
 * parameter is passed by reference, so that the action function
 * can modify the program state.
 */

void addButton(string name, void (*actionFn)());

template <typename ClientDataType>
void addButton(string name,
               void (*actionFn)(ClientDataType & data),
               ClientDataType & data);

/*
 * Function: defineClickListener
 * Usage: defineClickListener(clickFn);
 *        defineClickListener(clickFn, data);
 * ------------------------------------------
 * Designates a function that will be called whenever the user
 * clicks the mouse in the graphics window.  If a click listener
 * has been specified by the program, the event loop will invoke
 *
 *       clickFn(pt)
 *
 * or
 *
 *       clickFn(pt, data)
 *
 * depending on whether the data parameter is supplied.  In either
 * case, pt is the GPoint at which the click occurred and data
 * is a parameter of any type appropriate to the application.  The
 * data parameter is passed by reference, so that the click function
 * can modify the program state.
 */

void defineClickListener(void (*actionFn)(GPoint pt));

template <typename ClientDataType>
void defineClickListener(void (*actionFn)(GPoint pt, ClientDataType & data),
                         ClientDataType & data);

/*
 * Function: pathfinderEventLoop
 * Usage: pathfinderEventLoop();
 * -----------------------------
 * Initiates a loop that repeatedly waits for the user to click
 * on a button and calls the action function associated with that
 * button.  Moreover, if the client has registered a click listener,
 * pathfinderEventLoop will call that listener whenever the mouse is
 * clicked inside the window.
 *
 * Note that pathfinderEventLoop never returns, so programs that need
 * to exit on user command need to call the exit() function in the
 * standard libraries.
 */

void pathfinderEventLoop();

/*
 * Function: getMouseClick
 * Usage: pt = getMouseClick();
 * ----------------------------
 * Waits for the user to click somewhere on the graphics window
 * and returns the coordinate of where the click took place.
 */

GPoint getMouseClick();

/* Include the implementation of the template functions */

#include "gpathfinderimpl.cpp"

#endif
