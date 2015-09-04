//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// paddle constants
#define PADDLE_HEIGHT 10
#define PADDLE_WIDTH 80

// ball velocity factor
#define VELOCITY_FACTOR 3.0

// structures
typedef struct
{
    GRect paddle;
    char *direction;
    int x;
    int y;
} Paddle;

typedef struct
{
    double horizontalVelocity;
    double verticalVelocity;
} Velocity;

// prototypes
void ballHitsPaddle(Paddle *paddle, Velocity *velocity, GOval *ball);
void checkForEvent(Paddle *bat);
void ballHitsBrick(Velocity *velocity, GWindow *window, GObject *brick, 
        GLabel *label, int *score, int *bricksCount);
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
void invertHorizontalDirection(Velocity *velocity);
void invertVerticalDirection(Velocity *velocity);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of lives initially
    int lives = LIVES;

    // number of bricks initially
    int bricks = ROWS * COLS;

    // number of points initially
    int points = 0;

    // default ball direction is down
    Velocity *velocity = (Velocity *) malloc(sizeof(Velocity));
    velocity->horizontalVelocity = 0.0;
    velocity->verticalVelocity = 2.0;

    char *paddleDirection = malloc(sizeof(char) * 10);
  
    Paddle *bat = (Paddle *)malloc(sizeof(Paddle));
    bat->paddle = paddle;
    bat->direction = paddleDirection;
    bat->x = getX(paddle);
    bat->y = getY(paddle);

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        checkForEvent(bat); 

        GObject object = detectCollision(window, ball);
        if (object != NULL)
        {
            if (object == paddle)
            {
                ballHitsPaddle(bat, velocity, ball);
            }
            else if (strcmp(getType(object), "GRect") == 0)
            {
                ballHitsBrick(velocity, &window, &object, &label, &points, &bricks);
            }
        }
        else
        {
            if (getX(ball) <= 0 
                    || getX(ball) + getWidth(ball) >= getWidth(window)) 
            {
                invertHorizontalDirection(velocity);
            }
            else if (getY(ball) <= 0)
            {
                invertVerticalDirection(velocity);
            }
            else if (getY(ball) + getHeight(ball) >= getHeight(window))
            {
                waitForClick();
                lives--;
                velocity->horizontalVelocity = 0.0;
                removeGWindow(window, ball);
                removeGWindow(window, paddle);
                ball = initBall(window);
                paddle = initPaddle(window);
                setLabel(label, "0");
            }
        }

        move(ball, velocity->horizontalVelocity, velocity->verticalVelocity);
        pause(10);
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Detects the paddle based on the location of the mouse pointer
 */
void checkForEvent(Paddle *bat)
{
    GEvent event = getNextEvent(MOUSE_EVENT);
    if (event != NULL)
    {
        if (getEventType(event) == MOUSE_MOVED)
        {
            double xCoordinate = getX(event) - getWidth(bat->paddle) / 2;
            setLocation(bat->paddle, xCoordinate, HEIGHT - PADDLE_HEIGHT - 100);
            
            // mouse moving right
            if (xCoordinate > bat->x)
            {
                strcpy(bat->direction, "right\0");
            }
            else if(xCoordinate < bat->x)
            {
                strcpy(bat->direction, "left\0");
            }
            bat->x = xCoordinate;
        }
    }
}

/**
 * Changes the direction of the ball when it hits the paddle
 */
void ballHitsPaddle(Paddle *paddle, Velocity *velocity, GOval *ball)
{
    // determine where do we need to go
    if (strcmp(paddle->direction, "left") == 0)
    {
        velocity->horizontalVelocity = -drand48() * VELOCITY_FACTOR;
    }
    else
    {
        velocity->horizontalVelocity = drand48() * VELOCITY_FACTOR;
    }
    invertVerticalDirection(velocity);

    // ensure that the ball clears the paddle
    // when ball is hit by the paddle on the side
    // otherwise the ball gets stuck on the paddle
    move(ball, velocity->horizontalVelocity, velocity->verticalVelocity - 5);
}

/**
 * Changes the balls direction when it hits a brick.
 */
void ballHitsBrick(Velocity *velocity, 
        GWindow *window, 
        GObject *brick, 
        GLabel *label,
        int *score, 
        int *bricksCount)
{
    invertHorizontalDirection(velocity);
    invertVerticalDirection(velocity);
    removeGWindow(*window, *brick);
    freeGObject(*brick);
    (*score)++;
    (*bricksCount)--;

    char *newScore = malloc(sizeof(char) * 2);
    sprintf(newScore, "%d", *score);
    setLabel(*label, newScore);
}

/**
 * Changes the sign of the horizontal velocity, effectively 
 * changing the ball's direction to the opposite direction
 * along the x-axis
 */
void invertHorizontalDirection(Velocity *velocity)
{
    velocity->horizontalVelocity = -velocity->horizontalVelocity;
}

/**
 * Changes the sign of the vertical velocity, effectively 
 * changing the ball's direction to the opposite direction
 * along the y-axis
 */
void invertVerticalDirection(Velocity *velocity)
{
    velocity->verticalVelocity = -velocity->verticalVelocity;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    char *colors[] = {
        "RED",
        "ORANGE",
        "YELLOW",
        "GREEN",
        "0x00FFFF"
    };

    int brickPadding = 40;
    int brickWidth = (WIDTH - brickPadding) / 10;
    for(int i = 0, y = 30; i < ROWS; i++, y += 15)
    {
        for(int j = 0, x = 2; j < COLS; j++, x += brickWidth + 4)
        {
            GRect brick = newGRect(x, y, brickWidth, 10);
            setColor(brick, colors[i]);
            setFilled(brick, true);
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(WIDTH / 2 - RADIUS, HEIGHT / 2 - RADIUS, RADIUS * 2, RADIUS * 2);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect((WIDTH / 2) - (PADDLE_WIDTH / 2), 
            HEIGHT - PADDLE_HEIGHT - 100, 
            PADDLE_WIDTH, 
            PADDLE_HEIGHT);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel scoreboard = newGLabel("0");
    setFont(scoreboard, "SansSerif-48");
    double x = (getWidth(window) - getWidth(scoreboard)) / 2;
    double y = (getHeight(window) + getFontAscent(scoreboard)) / 2;
    setColor(scoreboard, "0xC0C0C0");
    setLocation(scoreboard, x, y);
    add(window, scoreboard);
    return scoreboard;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
