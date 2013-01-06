/*
 * File: gpathfinder.cpp
 * ---------------------
 * The gpathfinder.cpp file implements a set of functions that help draw the
 * necessary parts of the Pathfinder maps.
 */

#include <iostream>
#include <string>
#include "graphics.h"
#include "gevents.h"
#include "gpathfinder.h"
#include "point.h"
#include "vector.h"
using namespace std;

/* Constants */

const int WINDOW_WIDTH = 655;
const int WINDOW_HEIGHT = 400;
const int CONTROL_STRIP_HEIGHT = 40;
const string CONTROL_STRIP = "#E5E5E5";
const string STANDARD_BACKGROUND = "#CCCCCC";
const string STANDARD_HIGHLIGHT = "White";
const string STANDARD_INNERSHADE = "#BCB7B7";
const string STANDARD_OUTERSHADE = "#6C6D6D";
const string ACTIVATED_BACKGROUND = "#FF4C4C";
const string ACTIVATED_BORDER = "#FF2020";
const string ACTIVATED_INNERSHADE = "#FF3333";
const string ACTIVATED_TEXT = "White";
const string BUTTON_FONT = "Helvetica-Bold-12";
const double MIN_BUTTON_WIDTH = 70;
const double BUTTON_HEIGHT = 20;
const double BUTTON_MARGIN = 4;
const double BUTTON_SEP = 6;
const double BUTTON_LABEL_DY = 10;

/* Structure for button data */

struct Button {
   string name;
   double x, y, width, height;
   bool highlighted;
   ButtonCallbackBase *callback;
};

/* Global data */

static Vector<Button> buttons;
static ClickCallbackBase *clickHook = NULL;

/* Prototypes */

void drawCircle(double x, double y, double r);
void fillCircle(double x, double y, double r);
   
void drawButton(Button & button);
void drawNormalButton(Button & button);
void drawHighlightedButton(Button & button);
void drawBackground(Button & button);
void drawOutline(Button & button);
void drawOuterShade(Button & button);
void drawInnerShade(Button & button);
void drawHighlight(Button & button);
void drawButtonText(Button & button);
double computeNextButtonX();
double computeButtonWidth(string name);
int findButtonIndex(double x, double y);
bool isInsideButton(Button & button, double x, double y);

/* Exported functions */

void initPathfinderGraphics() {
   initGraphics(WINDOW_WIDTH, WINDOW_HEIGHT + CONTROL_STRIP_HEIGHT);
   setColor(CONTROL_STRIP);
   fillRect(0, WINDOW_HEIGHT, WINDOW_WIDTH, CONTROL_STRIP_HEIGHT);
   setColor("Black");
   setWindowTitle("Pathfinder");
}

void drawPathfinderMap(string mapFile) {
   setColor("White");
   fillRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
   setColor("Black");
   if (mapFile != "") drawImage(mapFile, 0, 0);
}

void drawPathfinderNode(GPoint center, string color, string label) {
   setColor(color);
   fillCircle(center.getX(), center.getY(), NODE_RADIUS);
   if (!label.empty()) {
      setFont(LABEL_FONT);
      drawString(label, center.getX() + NODE_RADIUS + 2,
                        center.getY() + 5);
   }
}

void drawPathfinderArc(GPoint start, GPoint end, string color) {
   setColor(color);
   drawLine(start.getX(), start.getY(), end.getX(), end.getY());
}

/*
 * Implementation notes: repaintPathfinderDisplay
 * ----------------------------------------------
 * This function simply forwards the repaint request to the StanfordCPPLib
 * graphics library.  It is included in this package only to ensure that
 * clients don't need to import any functions from the graphics.h interface.
 */

void repaintPathfinderDisplay() {
   repaint();
}

/*
 * Implementation notes: addButton
 * -------------------------------
 * This function creates a button and adds it to the vector of buttons
 * at the next available position in the control strip.  Most of the
 * complexity involved in the addButton function occurs in the
 * template version of the function, which appears in the file
 * gpathfinderimpl.cpp.
 */

void addButton(string name, void (*actionFn)()) {
   addButton(name, new ButtonCallbackBase(actionFn));
}

void addButton(string name, ButtonCallbackBase *callback) {
   Button button;
   button.name = name;
   button.x = computeNextButtonX();
   button.y = WINDOW_HEIGHT + (CONTROL_STRIP_HEIGHT - BUTTON_HEIGHT) / 2;
   button.width = computeButtonWidth(name);
   button.height = BUTTON_HEIGHT;
   button.highlighted = false;
   button.callback = callback;
   buttons.add(button);
   drawButton(button);
   repaint();
}

/*
 * Implementation notes: defineClickListener
 * -----------------------------------------
 * This function designates a listener for mouse clicks in the window.
 * Most of the complexity involved in the defineClickListener function
 * occurs in the template version of the function, which appears in the
 * file gpathfinderimpl.cpp.
 */

void defineClickListener(void (*clickFn)(GPoint pt)) {
   defineClickListener(new ClickCallbackBase(clickFn));
}

void defineClickListener(ClickCallbackBase *callback) {
   clickHook = callback;
}

/*
 * Implementation notes: pathfinderEventLoop
 * -----------------------------------------
 * Even though the code for this function is long, its operation is
 * reasonably straightforward.  As soons as the mouse goes down, this
 * function monitors its position, waiting for the mouse to enter or
 * leave the area covered by a button object.  Entering a button
 * highlights it on the screen; leaving the button region removes the
 * highlight.  When the mouse button comes up, the code checks to see
 * whether the release is in a button and, if so, invokes its action
 * function.  If not, the code checks to see if the client has defined
 * a click action, in which case it calls the click function.
 */

void pathfinderEventLoop() {
   while (true) {
      GMouseEvent e;
      waitForEvent(e);
      if (e.getEventType() == MOUSE_CLICKED) {
         int index = findButtonIndex(e.getX(), e.getY());
         if (index == -1) {
            GPoint pt = GPoint(e.getX(), e.getY());
            if (pt.getY() < WINDOW_HEIGHT && clickHook != NULL) {
               clickHook->apply(pt);
               repaint();
            }
         } else {
            buttons[index].callback->apply();
            repaint();
	 }
      }
   }
}

/*
 * Implementation notes: getMouseClick
 * -----------------------------------
 * getMouseClick waits for the mouse button to go down and then up again,
 * at which point the function returns the mouse position at the time of
 * release.
 */

GPoint getMouseClick() {
   while (true) {
      GMouseEvent e;
      waitForEvent(e);
      if (e.getEventType() == MOUSE_CLICKED) {
      	 return GPoint(e.getX(), e.getY());
      }
   }
   return GPoint();
}

/* Helper functions */

/*
 * Implementation notes: drawCircle, fillCircle
 * --------------------------------------------
 * These functions are useful tools that draw an outlined and a filled
 * circle, respectively.  If you are extending the Pathfinder assignment,
 * you might well want to export these methods through the gpathfinder.h
 * interface.
 */

void drawCircle(double x, double y, double r) {
   drawOval(x - r, y - r, 2 * r, 2 * r);
}

void fillCircle(double x, double y, double r) {
   fillOval(x - r, y - r, 2 * r, 2 * r);
}

/*
 * Implementation notes: drawButton and its subsidiary functions
 * -------------------------------------------------------------
 * The following set of functions draw a button in the control strip.
 * The decomposition of the drawing operation ensures that the
 * complexity of the drawing code is manageable at every level.
 */

void drawButton(Button & button) {
   saveGraphicsState();
   if (button.highlighted) {
      drawHighlightedButton(button);
   } else {
      drawNormalButton(button);
   }
   restoreGraphicsState();
}

void drawNormalButton(Button & button) {
   setColor(STANDARD_BACKGROUND);
   drawBackground(button);
   setColor(STANDARD_OUTERSHADE);
   drawOuterShade(button);
   setColor(STANDARD_INNERSHADE);
   drawInnerShade(button);
   setColor(STANDARD_HIGHLIGHT);
   drawHighlight(button);
   setColor("Black");
   drawOutline(button);
   drawButtonText(button);
}

void drawHighlightedButton(Button & button) {
   setColor(ACTIVATED_BACKGROUND);
   drawBackground(button);
   setColor(ACTIVATED_INNERSHADE);
   drawInnerShade(button);
   setColor(ACTIVATED_BORDER);
   drawOutline(button);
   setColor(ACTIVATED_TEXT);
   drawButtonText(button);
}

void drawBackground(Button & button) {
   fillRect(button.x + 1, button.y + 1, button.width - 2, button.height - 2);
}

void drawOutline(Button & button) {
   double x = button.x;
   double y = button.y;
   double w = button.width;
   double h = button.height;
   drawLine(x, y + h - 2, x, y + 3);
   drawLine(x, y + 3, x + 2, y + 1);
   drawLine(x + 2, y + 1, x + w - 3, y + 1);
   drawLine(x + w - 3, y + 1, x + w - 1, y + 3);
   drawLine(x + w - 1, y + 3, x + w - 1, y + h - 2);
   drawLine(x + w - 1, y + h - 2, x + w - 3, y + h);
   drawLine(x + w - 3, y + h, x + 2, y + h);
   drawLine(x + 2, y + h, x, y + h - 2);
}

void drawOuterShade(Button & button) {
   double x = button.x;
   double y = button.y;
   double w = button.width;
   double h = button.height;
   drawLine(x + 2, y + 2, x + w - 3, y + 2);
   drawLine(x + w - 3, y + 2, x + w - 3, y + 3);
   drawLine(x + w - 3, y + 3, x + w - 2, y + 3);
   drawLine(x + w - 2, y + 3, x + w - 2, y + h - 2);
}

void drawInnerShade(Button & button) {
   double x = button.x;
   double y = button.y;
   double w = button.width;
   double h = button.height;
   drawLine(x + 2, y + 3, x + w - 4, y + 3);
   drawLine(x + w - 4, y + 3, x + w - 4, y + 4);
   drawLine(x + w - 4, y + 4, x + w - 3, y + 4);
   drawLine(x + w - 3, y + 4, x + w - 3, y + h - 2);
}

void drawHighlight(Button & button) {
   double x = button.x;
   double y = button.y;
   double w = button.width;
   double h = button.height;
   drawLine(x + 2, y + h - 2, x + 2, y + 2);
   drawLine(x + 2, y + h - 2, x + w - 2, y + h - 2);
}

void drawButtonText(Button & button) {
   setFont(BUTTON_FONT);
   drawString(button.name,
              button.x + (button.width - getStringWidth(button.name)) / 2,
              button.y + (button.height + BUTTON_LABEL_DY) / 2);
}

/*
 * Implementation notes: computeNextButtonX, computeButtonWidth
 * ------------------------------------------------------------
 * These helper functions help arrange the buttons in the control
 * strip.  Each button is given a size so that its entire text
 * appears, with a suitable margin on each end.  The buttons are
 * assigned positions from left to right in the control strip
 * with BUTTON_SEP pixels between each one.
 */

double computeNextButtonX() {
   double x = BUTTON_SEP;
   for (int i = 0; i < buttons.size(); i++) {
      x += buttons[i].width + BUTTON_SEP;
   }
   return x;
}

double computeButtonWidth(string name) {
   saveGraphicsState();
   setFont(BUTTON_FONT);
   double width = 2 * BUTTON_MARGIN + getStringWidth(name);
   restoreGraphicsState();
   if (width < MIN_BUTTON_WIDTH) width = MIN_BUTTON_WIDTH;
   return width;
}

/*
 * Implementation notes: findButtonIndex, isInsideButton
 * -----------------------------------------------------
 * These functions look through the vector of buttons to determine
 * whether the specified position is inside the area of some button.
 * If so, findButtonIndex returns the index of that button in the
 * vector; if not, it returns -1.
 */

int findButtonIndex(double x, double y) {
   for (int i = 0; i < buttons.size(); i++) {
      if (isInsideButton(buttons[i], x, y)) return i;
   }
   return -1;
}

bool isInsideButton(Button & button, double x, double y) {
   return x >= button.x && x <= button.x + button.width
       && y >= button.y && y <= button.y + button.height;
}

/*
 * Implementation notes: Implementation of the callback classes
 * ------------------------------------------------------------
 * The remaining functions in this file support the implementation
 * of the various callback classes, which are defined in the file
 * gpathfinderimpl.cpp.
 */

ButtonCallbackBase::ButtonCallbackBase() {
   /* Empty */
}

ButtonCallbackBase::ButtonCallbackBase(void (*actionFn)()) {
   this->actionFn = actionFn;
}

ButtonCallbackBase::~ButtonCallbackBase() {
   /* Empty */
}

void ButtonCallbackBase::apply() {
   actionFn();
}

ClickCallbackBase::ClickCallbackBase() {
   /* Empty */
}

ClickCallbackBase::ClickCallbackBase(void (*clickFn)(GPoint pt)) {
   this->clickFn = clickFn;
}

ClickCallbackBase::~ClickCallbackBase() {
   /* Empty */
}

void ClickCallbackBase::apply(GPoint pt) {
   clickFn(pt);
}
